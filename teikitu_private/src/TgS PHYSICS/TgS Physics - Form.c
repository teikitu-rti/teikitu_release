/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Form.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Physics - Internal.inl"


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_PH_Form_Collision_Data,)
{
    ETgPM_SHORT                                 m_enPM;
    TgUINT_E32                                  m_auiPad[3];
    UTg2_CO_Primitive_F32_04                    m_uPM;
};





/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgVOID
tgPH_Form_Init_AABB(
     STg2_PH_Form_PC );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Forward Declare Local Command Functions                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgRESULT
tgPH_Form_Set_Collision_Primitive_Command(
     TgPH_FORM_ID_C, STg2_PH_Form_Collision_Data_CP );





/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic, Internal and File Local Command Functions                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Form_Init_Do_Command ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Form_Init_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    typedef struct {
        TgPH_FORM_ID tiID;
    } STg2_FCN_Command;
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };

    STg2_PH_Form_P                      psFM;

    TgPARAM_CHECK( sizeof( STg2_FCN_Command ) == nbyCommand_Buffer );
    TgPARAM_CHECK( uCMD.pCommand );
    (void)nbyCommand_Buffer;

    /* Acquire the form, assuming the identifier is still valid. */
    psFM = tgPH_Form_Get_Form_From_ID( uCMD.pCommand->tiID );

    if (nullptr == psFM) TgATTRIBUTE_UNLIKELY
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Form ID submitted for init." );
        return;
    };

    TgPARAM_CHECK(KTgID__INVALID_VALUE != psFM->m_tiForm.m_uiKI)

    /* Initialize to default values. */

    psFM->m_uiCategory = 0ULL;
    psFM->m_uiCollide = ~0ULL;

    psFM->m_vPos_O2B = KTgUNIT_W_F32_04_1;
    psFM->m_vRot_O2B = KTgUNIT_W_F32_04_1;
    psFM->m_vScale = tgMH_Init_ELEM_F32_04_1( 1.0F, 1.0F, 1.0F, 0.0F );
    tgMH_CLI_F32_04_3( &psFM->m_mLocal_O2B );

    psFM->m_vPos_Last_Valid_O2W = KTgUNIT_W_F32_04_1;
    psFM->m_vPos_O2W = KTgUNIT_W_F32_04_1;
    tgMH_CLI_F32_04_3( &psFM->m_mFinal_O2W );
    tgGM_BA_Reset_F32_04( &psFM->m_sBA_W );

    tgGM_BA_Reset_F32_04( &psFM->m_sBA_O );

    psFM->m_uiUsed_Index = TgSTD_ATOMIC(fetch_add_explicit)( g_axnuiPH_Form_Total__Used + psFM->m_tiForm.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) );
    g_aapsPH_Form_Used[psFM->m_tiForm.m_uiWorld][psFM->m_uiUsed_Index] = psFM;
    tgPH_Form_Update_Category_Cache( psFM );
}


/* ---- tgPH_Form_Reset_Do_Command ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* SYNC: READS/WRITES to Forms, Bodies and Constraints.                                                                                                                            */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Form_Reset_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    typedef struct {
        TgPH_FORM_ID tiID;
    } STg2_FCN_Command;
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };
    STg2_PH_Form_P                      psFM;

    TgPARAM_CHECK( sizeof( STg2_FCN_Command ) == nbyCommand_Buffer );
    TgPARAM_CHECK( uCMD.pCommand );
    (void)nbyCommand_Buffer;

    /* Acquire the form, assuming the identifier is still valid. */
    psFM = tgPH_Form_Get_Form_From_ID( uCMD.pCommand->tiID );

    if (nullptr == psFM) TgATTRIBUTE_UNLIKELY
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Form ID submitted for reset." );
        return;
    };

    if (KTgID__INVALID_VALUE != psFM->m_tiBY.m_uiKI)
    {
        tgPH_Body_Remove_Form_IMM( uCMD.pCommand->tiID );
    };

    tgPH_Form_Reset_IMM( uCMD.pCommand->tiID );
}


/* ---- tgPH_Form_Set_Collision_Primitive_Command -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
PHYSICS_FUNCTION_DEFER_DEFINITION__COPY(Form_Set_Collision_Primitive_Command, Form, FORM, STg2_PH_Form_Collision_Data,

    tgPH_Form_Set_Collision_Primitive_IMM( psForm, uCMD.pCommand->Val.m_enPM, &uCMD.pCommand->Val.m_uPM );
)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Form_Set_Collision_Primitive ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Form_Set_Collision_Primitive( TgPH_FORM_ID_C tiFM0, ETgPM_SHORT_C enPM, UTg2_CO_Primitive_F32_04_CPC uPM )
{
    STg2_PH_Form_Collision_Data         sData;

    /* Fail out any of the primitives we do not support. */
    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
    switch (enPM) {
    case ETgPM_PN: break;
    case ETgPM_RT: break;
    case ETgPM_SP: break;
    case ETgPM_BX: break;
    case ETgPM_CP: break;
    case ETgPM_CY: break;
    default: TgDIAG(false); return (KTgE_FAIL);
    }
    TgWARN_DISABLE_POP()

    sData.m_enPM = enPM;
    tgMM_Copy( &sData.m_uPM, sizeof(sData.m_uPM), uPM, sizeof(UTg2_CO_Primitive_F32_04) );

    tgPH_Form_Set_Collision_Primitive_Command( tiFM0, &sData );
    return KTgS_OK;
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Macro Functions                                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

PHYSICS_FUNCTION_QUERY_DEFINITION(Form_Query_World_Collision,Form,FORM,World_Collision,TgBOOL,*pVal = (psForm->m_uiCategory & (1ULL << KTgPH_CATEGORY_BIT__ENABLE_COLLSION));)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Form_Set_World_Collision,Form,FORM,TgBOOL,
    psForm->m_uiCategory |= uCMD.pCommand->Val ? (1ULL << KTgPH_CATEGORY_BIT__ENABLE_COLLSION) : 0;
    tgPH_Form_Update_Category_Cache( psForm );
)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Form,FORM,Category,TgUINT_E64,m_uiCategory)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Form_Set_Category,Form,FORM,TgUINT_E64,
    psForm->m_uiCategory = (uCMD.pCommand->Val & ~(KTgPH_CATEGORY_BIT_MASK__RESERVED)) | (psForm->m_uiCategory & (KTgPH_CATEGORY_BIT_MASK__RESERVED));
    tgPH_Form_Update_Category_Cache( psForm );
)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Form,FORM,Collide,TgUINT_E64,m_uiCollide)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Form_Set_Collide,Form,FORM,TgUINT_E64,
    psForm->m_uiCollide = (uCMD.pCommand->Val & ~(KTgPA_CATEGORY_BIT_MASK__RESERVED)) | (psForm->m_uiCollide & (KTgPA_CATEGORY_BIT_MASK__RESERVED));
)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Form,FORM,Material_ID,TgPH_MATERIAL_ID,m_tiMaterial)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Form,FORM,Primitive,ETgPM_SHORT,m_enPM)
PHYSICS_FUNCTION_QUERY_DEFINITION__COPY(Form,FORM,Primitive_Data,UTg2_CO_Primitive_F32_04,m_uPM)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Form,FORM,Body_ID,TgPH_BODY_ID,m_tiBY)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Form,FORM,Next_Form_ID,TgPH_FORM_ID,m_tiNext)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(Form,FORM,Sweep_ID,TgPARTITION_OBJECT_ID,m_tiPnS)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Form_Set_Position_B,Form,FORM,TgVEC_F32_04_1,
    psForm->m_vPos_O2B = tgMH_Init_Point_F32_04_1( uCMD.pCommand->Val );
    tgMH_Init_Reference_Frame_From_Scale_Quaternion_Position_F32_04_3( &psForm->m_mLocal_O2B, psForm->m_vScale, psForm->m_vRot_O2B, psForm->m_vPos_O2B );
    tgPH_Form_Update__WRITE( psForm, KTgID__INVALID_VALUE == psForm->m_tiBY.m_uiKI ? nullptr : tgPH_Body_Get_Body_From_ID( psForm->m_tiBY ), true );
)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Form,FORM,Position_B,TgVEC_F32_04_1,m_vPos_O2B)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Form_Set_Rotation_B,Form,FORM,TgVEC_F32_04_1,
    psForm->m_vRot_O2B = uCMD.pCommand->Val;
    tgMH_Init_Reference_Frame_From_Scale_Quaternion_Position_F32_04_3( &psForm->m_mLocal_O2B, psForm->m_vScale, psForm->m_vRot_O2B, psForm->m_vPos_O2B );
    tgPH_Form_Update__WRITE( psForm, KTgID__INVALID_VALUE == psForm->m_tiBY.m_uiKI ? nullptr : tgPH_Body_Get_Body_From_ID( psForm->m_tiBY ), true );
)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Form,FORM,Rotation_B,TgVEC_F32_04_1,m_vRot_O2B)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Form_Set_Scale,Form,FORM,TgVEC_F32_04_1,
    psForm->m_vScale = tgMH_Init_Vector_F32_04_1( uCMD.pCommand->Val );
    tgMH_Init_Reference_Frame_From_Scale_Quaternion_Position_F32_04_3( &psForm->m_mLocal_O2B, psForm->m_vScale, psForm->m_vRot_O2B, psForm->m_vPos_O2B );
    tgPH_Form_Update__WRITE( psForm, KTgID__INVALID_VALUE == psForm->m_tiBY.m_uiKI ? nullptr : tgPH_Body_Get_Body_From_ID( psForm->m_tiBY ), true );
)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Form,FORM,Scale,TgVEC_F32_04_1,m_vScale)
PHYSICS_FUNCTION_QUERY_DEFINITION__COPY(Form,FORM,Final_Transform_B,TgVEC_F32_04_3,m_mLocal_O2B)
PHYSICS_FUNCTION_QUERY_DEFINITION__COPY(Form,FORM,AABB_O,TgBOXAA_F32_04,m_sBA_O)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Form,FORM,Last_Position_W,TgVEC_F32_04_1,m_vPos_Last_Valid_O2W)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Form,FORM,Position_W,TgVEC_F32_04_1,m_vPos_O2W)
PHYSICS_FUNCTION_QUERY_DEFINITION__COPY(Form,FORM,Final_Transform_W,TgVEC_F32_04_3,m_mFinal_O2W)
PHYSICS_FUNCTION_QUERY_DEFINITION__COPY(Form,FORM,AABB_W,TgBOXAA_F32_04,m_sBA_W)

PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Form,FORM,Colour,TgVEC_F32_04_1,m_vDebug_Colour)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Form_Reset_IMM ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Form_Reset_IMM( TgPH_FORM_ID_C tiFM )
{
    STg2_PH_Form_P                      psFM;
    TgRSIZE                             uiIndex;

    /* Acquire the form, assuming the identifier is still valid. */
    psFM = tgPH_Form_Get_Form_From_ID( tiFM );

    if (nullptr == psFM) TgATTRIBUTE_UNLIKELY
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Form ID submitted for reset." );
        return;
    };

    if (KTgID__INVALID_VALUE != psFM->m_tiPnS.m_uiKI)
    {
        STg2_PH_World_CPC                   psWorld = g_asPH_World + psFM->m_tiForm.m_uiWorld;

        tgPA_Graph_Remove_Object( psWorld->m_tiPA_Graph, psFM->m_tiPnS );
        psFM->m_tiPnS.m_uiKI = KTgID__INVALID_VALUE;
    };

    /* Reset the data to zero or its equivalents and return it to the free stack. */

    uiIndex = TgSTD_ATOMIC(fetch_sub_explicit)( g_axnuiPH_Form_Total__Used + tiFM.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) );
    g_aapsPH_Form_Used[tiFM.m_uiWorld][uiIndex - 1]->m_uiUsed_Index = psFM->m_uiUsed_Index;
    g_aapsPH_Form_Used[tiFM.m_uiWorld][psFM->m_uiUsed_Index] = g_aapsPH_Form_Used[tiFM.m_uiWorld][uiIndex - 1];
    TgSTD_ATOMIC(fetch_sub_explicit)( g_axnuiPH_Form + tiFM.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) );
    tgPH_Form_Update_Category_Cache( g_aapsPH_Form_Used[tiFM.m_uiWorld][psFM->m_uiUsed_Index] );

    tgMM_Set_U08_0x00( psFM, sizeof(STg2_PH_Form) );
    tgCM_UT_LF__ST__Push( &g_asPH_Form_Free_Stack[tiFM.m_uiWorld].m_sStack, &psFM->m_sNode_Stack );
}


/* ---- tgPH_Form_Set_Collision_Primitive_IMM ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Form_Set_Collision_Primitive_IMM( STg2_PH_Form_PC psFM, ETgPM_SHORT_C enPM, UTg2_CO_Primitive_F32_04_CPC puPM )
{
    psFM->m_enPM = enPM;
    tgMM_Copy( &psFM->m_uPM, sizeof(psFM->m_uPM), puPM, sizeof(psFM->m_uPM) );
    tgPH_Form_Init_AABB( psFM );

    TgWARN_DISABLE_PUSH(,cast-function-type-strict)
    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
    switch (psFM->m_enPM) {
    case ETgPM_PN:
        psFM->m_pfnPM_Copy_TX = (TgVOID (*)( TgVOID_PCU, TgVOID_CPCU, TgVOID_CPCU ))tgGM_PN_Copy_TX_F32_04;
        psFM->m_pfnPM_Sweep_BA = nullptr;
        psFM->m_pfnPM_Support_Point = nullptr;
        break;
    case ETgPM_RT:
        psFM->m_pfnPM_Copy_TX = (TgVOID (*)( TgVOID_PCU, TgVOID_CPCU, TgVOID_CPCU ))tgGM_RT_Copy_TX_F32_04;
        psFM->m_pfnPM_Sweep_BA = (TgVOID (*)( TgVOID_PCU, TgVOID_CPCU, TgVEC_F32_04_1_C ))tgGM_RT_Sweep_BA_F32_04;
        psFM->m_pfnPM_Support_Point = (TgVEC_F32_04_1 (*)( TgVOID_CPCU, TgVEC_F32_04_1_C ))tgGM_RT_Support_Point_F32_04;
        break;
    case ETgPM_SP:
        psFM->m_pfnPM_Copy_TX = (TgVOID (*)( TgVOID_PCU, TgVOID_CPCU, TgVOID_CPCU ))tgGM_SP_Copy_TX_F32_04;
        psFM->m_pfnPM_Sweep_BA = (TgVOID (*)( TgVOID_PCU, TgVOID_CPCU, TgVEC_F32_04_1_C ))tgGM_SP_Sweep_BA_F32_04;
        psFM->m_pfnPM_Support_Point = (TgVEC_F32_04_1 (*)( TgVOID_CPCU, TgVEC_F32_04_1_C ))tgGM_SP_Support_Point_F32_04;
        break;
    case ETgPM_BX:
        psFM->m_pfnPM_Copy_TX = (TgVOID (*)( TgVOID_PCU, TgVOID_CPCU, TgVOID_CPCU ))tgGM_BX_Copy_TX_F32_04;
        psFM->m_pfnPM_Sweep_BA = (TgVOID (*)( TgVOID_PCU, TgVOID_CPCU, TgVEC_F32_04_1_C ))tgGM_BX_Sweep_BA_F32_04;
        psFM->m_pfnPM_Support_Point = (TgVEC_F32_04_1 (*)( TgVOID_CPCU, TgVEC_F32_04_1_C ))tgGM_BX_Support_Point_F32_04;
        break;
    case ETgPM_CP:
        psFM->m_pfnPM_Copy_TX = (TgVOID (*)( TgVOID_PCU, TgVOID_CPCU, TgVOID_CPCU ))tgGM_TB_Copy_TX_F32_04;
        psFM->m_pfnPM_Sweep_BA = (TgVOID (*)( TgVOID_PCU, TgVOID_CPCU, TgVEC_F32_04_1_C ))tgGM_CP_Sweep_BA_F32_04;
        psFM->m_pfnPM_Support_Point = (TgVEC_F32_04_1 (*)( TgVOID_CPCU, TgVEC_F32_04_1_C ))tgGM_CP_Support_Point_F32_04;
        break;
    case ETgPM_CY:
        psFM->m_pfnPM_Copy_TX = (TgVOID (*)( TgVOID_PCU, TgVOID_CPCU, TgVOID_CPCU ))tgGM_TB_Copy_TX_F32_04;
        psFM->m_pfnPM_Sweep_BA = (TgVOID (*)( TgVOID_PCU, TgVOID_CPCU, TgVEC_F32_04_1_C ))tgGM_CY_Sweep_BA_F32_04;
        psFM->m_pfnPM_Support_Point = (TgVEC_F32_04_1 (*)( TgVOID_CPCU, TgVEC_F32_04_1_C ))tgGM_CY_Support_Point_F32_04;
        break;
    default: break;
    }
    TgWARN_DISABLE_POP()
    TgWARN_DISABLE_POP()
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Module_Form_Init_Internal ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Module_Form_Init_Internal( TgVOID )
{
#if defined(TgBUILD_FEATURE__CLIENT)
    g_anuiPH_Form_Increase_Commit[ETgPH_WORLD__CLIENT_FX] = 10;
    g_anuiPH_Form_Total_Commit[ETgPH_WORLD__CLIENT_FX] = 0;
    g_anuiPH_Form_Total_Reserve[ETgPH_WORLD__CLIENT_FX] = 10000;

    g_anuiPH_Form_Increase_Commit[ETgPH_WORLD__CLIENT_UI] = 10;
    g_anuiPH_Form_Total_Commit[ETgPH_WORLD__CLIENT_UI] = 0;
    g_anuiPH_Form_Total_Reserve[ETgPH_WORLD__CLIENT_UI] = 10000;
/*# defined(TgBUILD_FEATURE__CLIENT) */
#endif

#if defined(TgBUILD_FEATURE__SERVER)
    g_anuiPH_Form_Increase_Commit[ETgPH_WORLD__SERVER_DEFAULT] = 10;
    g_anuiPH_Form_Total_Commit[ETgPH_WORLD__SERVER_DEFAULT] = 0;
    g_anuiPH_Form_Total_Reserve[ETgPH_WORLD__SERVER_DEFAULT] = 100000;
/*# defined(TgBUILD_FEATURE__SERVER) */
#endif
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Form_Init_AABB ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Form_Init_AABB( STg2_PH_Form_PC psFM )
{
    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
    switch (psFM->m_enPM) {
    case ETgPM_PN: {
        TgVEC_F32_04_1_C                    vMax = tgMH_Init_Vector_ELEM_F32_04_1(  KTgMAX_F32,  KTgMAX_F32,  KTgMAX_F32 );
        TgVEC_F32_04_1_C                    vMin = tgMH_Init_Vector_ELEM_F32_04_1( -KTgMAX_F32, -KTgMAX_F32, -KTgMAX_F32 );

        tgGM_BA_Init_F32_04( &psFM->m_sBA_O, vMin, vMax );
    }  break;
    case ETgPM_RT: tgGM_RT_BA_F32_04(&psFM->m_sBA_O,&psFM->m_uPM.m_sRT); break;
    case ETgPM_SP: tgGM_SP_BA_F32_04(&psFM->m_sBA_O,&psFM->m_uPM.m_sSP); break;
    case ETgPM_BX: tgGM_BX_BA_F32_04(&psFM->m_sBA_O,&psFM->m_uPM.m_sBX); break;
    case ETgPM_CP: tgGM_CP_BA_F32_04(&psFM->m_sBA_O,&psFM->m_uPM.m_sTB); break;
    case ETgPM_CY: tgGM_CY_BA_F32_04(&psFM->m_sBA_O,&psFM->m_uPM.m_sTB); break;
    default: TgDIAG(false); tgGM_BA_Reset_F32_04( &psFM->m_sBA_O ); break;
    }
    TgWARN_DISABLE_POP()

    tgGM_BA_Copy_F32_04( &psFM->m_sBA_W, &psFM->m_sBA_O );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Debug Functions                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS

/* ---- tgPH_Form_Validate ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Form_Validate( STg2_Output_PC psOUT, TgPH_FORM_ID_C tiWorld )
{
    (void)psOUT;
    (void)tiWorld;

}

/*# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS */
#endif


