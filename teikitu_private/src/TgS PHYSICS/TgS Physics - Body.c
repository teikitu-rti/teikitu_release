/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Body.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Physics - Internal.inl"


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_PH_Force_Command_Data,)
{
    TgVEC_F32_04_1                              m_vF0;
    TgVEC_F32_04_1                              m_vS0;
};

TgTYPE_STRUCT(STg2_PH_Form_Command_Data,)
{
    TgPH_FORM_ID                                m_tiFM0;
    TgUINT_E64                                  m_uiPad;
    STg2_PH_Mass                                m_sMass;
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Forward Declare Local Command Functions                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgRESULT
tgPH_Body_Add_Form_Command(
     TgPH_BODY_ID_C, STg2_PH_Form_Command_Data_CP );

TgEXTN TgRESULT
tgPH_Body_Remove_Form_Command(
     TgPH_BODY_ID_C, STg2_PH_Form_Command_Data_CP );

TgEXTN TgRESULT
tgPH_Body_Add_Force_At_Location_Command(
     TgPH_BODY_ID_C, STg2_PH_Force_Command_Data_CP );

TgEXTN TgRESULT
tgPH_Body_Apply_Drag_Command(
     TgPH_BODY_ID_C, TgFLOAT32_C );





/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic, Internal and File Local Command Functions                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Body_Init_Do_Command ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Init_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    typedef struct {
        TgPH_BODY_ID tiID;
    } STg2_FCN_Command;
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };

    STg2_PH_Body_P                      psBY;

    TgPARAM_CHECK( sizeof( STg2_FCN_Command ) == nbyCommand_Buffer );
    TgPARAM_CHECK( uCMD.pCommand );
    (void)nbyCommand_Buffer;

    /* Acquire the body, assuming the identifier is still valid. */
    psBY = tgPH_Body_Get_Body_From_ID( uCMD.pCommand->tiID );
    if (nullptr == psBY) TgATTRIBUTE_UNLIKELY
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Body ID submitted for init." );
        return;
    };

    TgPARAM_CHECK(KTgID__INVALID_VALUE != psBY->m_tiBody.m_uiKI )

    tgPH_Mass_Reset( &psBY->m_sMass );

    psBY->m_vPos_Last_Valid_O2W = KTgUNIT_W_F32_04_1;
    psBY->m_vPos_O2W = KTgUNIT_W_F32_04_1;
    psBY->m_vRot_O2W = KTgUNIT_W_F32_04_1;
    tgMH_CLI_F32_04_3( &psBY->m_mRot_O2W );
    tgMH_CLI_F32_04_3( &psBY->m_mFinal_O2W );

    psBY->m_vForce_Field_Factor = KTgONE_F32_04_1;
    psBY->m_vTime_Factor = KTgONE_F32_04_1;
    psBY->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;

    psBY->m_bUpdate = false;

    psBY->m_uiUsed_Index = TgSTD_ATOMIC(fetch_add_explicit)( g_axnuiPH_Body_Total__Used + psBY->m_tiBody.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) );
    g_aapsPH_Body_Used[psBY->m_tiBody.m_uiWorld][psBY->m_uiUsed_Index] = psBY;
}


/* ---- tgPH_Body_Reset_Do_Command ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* SYNC: Requires WRITE access                                                                                                                                                     */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Reset_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    typedef struct {
        TgPH_BODY_ID tiID;
    } STg2_FCN_Command;
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };

    STg2_PH_Body_P                      psBY;
    TgPH_FORM_ID                        tiFM0;
    TgPH_CONSTRAINT_ID                  tiCT0;
    TgRSIZE                             uiIndex;

    TgPARAM_CHECK( sizeof( STg2_FCN_Command ) == nbyCommand_Buffer );
    TgPARAM_CHECK( uCMD.pCommand );
    (void)nbyCommand_Buffer;

    /* Acquire the body, assuming the identifier is still valid. */
    psBY = tgPH_Body_Get_Body_From_ID( uCMD.pCommand->tiID );
    if (nullptr == psBY) TgATTRIBUTE_UNLIKELY
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Body ID submitted for reset." );
        return;
    };

    /* Remove itself from other dependencies (form, constraints). */
    if (TgSUCCEEDED(tgPH_Body_Query_First_Constraint_ID( &tiCT0, uCMD.pCommand->tiID )))
    {
        TgPH_CONSTRAINT_ID                  tiCT1;
        STg2_PH_Constraint_P                psConstraint;

        do {
            psConstraint = tgPH_Constraint_Get_Constraint_From_ID( tiCT0 );
            if (nullptr == psConstraint)
                break;

            tiCT1.m_uiKI = KTgID__INVALID_VALUE;

            if (psConstraint->m_tiBY0.m_uiKI == uCMD.pCommand->tiID.m_uiKI)
            {
                tgPH_Constraint_Query_Next_Constraint_ID_For_Body_0( &tiCT1, tiCT0 );
                tgPH_Constraint_Reset( tiCT0 );
                tiCT0.m_uiKI = tiCT1.m_uiKI;
            }

            if (psConstraint->m_tiBY1.m_uiKI == uCMD.pCommand->tiID.m_uiKI)
            {
                tgPH_Constraint_Query_Next_Constraint_ID_For_Body_1( &tiCT1, tiCT0 );
                tgPH_Constraint_Reset( tiCT0 );
                tiCT0.m_uiKI = tiCT1.m_uiKI;
            }

        } while (tiCT0.m_uiKI != KTgID__INVALID_VALUE);
    };

    if (TgSUCCEEDED(tgPH_Body_Query_First_Form_ID( &tiFM0, uCMD.pCommand->tiID )))
    {
        TgPH_FORM_ID                        tiFM1;

        do {
            tgPH_Form_Query_Next_Form_ID( &tiFM1, tiFM0 );
            tgPH_Form_Reset_IMM( tiFM0 );
            tiFM0.m_uiKI = tiFM1.m_uiKI;
        } while (tiFM0.m_uiKI != KTgID__INVALID_VALUE);
    };

    /* Reset the data to zero or its equivalents and return it to the free stack. Currently have a write lock to the World. */

    uiIndex = TgSTD_ATOMIC(fetch_sub_explicit)( g_axnuiPH_Body_Total__Used + psBY->m_tiBody.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) );
    g_aapsPH_Body_Used[psBY->m_tiBody.m_uiWorld][uiIndex - 1]->m_uiUsed_Index = psBY->m_uiUsed_Index;
    g_aapsPH_Body_Used[psBY->m_tiBody.m_uiWorld][psBY->m_uiUsed_Index] = g_aapsPH_Body_Used[psBY->m_tiBody.m_uiWorld][uiIndex - 1];
    TgSTD_ATOMIC(fetch_sub_explicit)( g_axnuiPH_Body + uCMD.pCommand->tiID.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) );

    tgMM_Set_U08_0x00( psBY, sizeof(STg2_PH_Body) );
    tgCM_UT_LF__ST__Push( &g_asPH_Body_Free_Stack[uCMD.pCommand->tiID.m_uiWorld].m_sStack, &psBY->m_sStack_Node );
}


/* ---- tgPH_Body_Add_Force_At_Location ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
PHYSICS_FUNCTION_DEFER_DEFINITION__COPY(Body_Add_Force_At_Location_Command, Body, BODY, STg2_PH_Force_Command_Data,
    {
        TgVEC_F32_04_1_C                    v00 = tgMH_SUB_F32_04_1( uCMD.pCommand->Val.m_vS0, psBody->m_sMass.m_vCG );
        TgVEC_F32_04_1_C                    v01 = tgMH_CX_F32_04_1( v00, uCMD.pCommand->Val.m_vF0 );

        psBody->m_vPF = tgMH_ADD_F32_04_1( psBody->m_vPF, uCMD.pCommand->Val.m_vF0 );
        psBody->m_vPT = tgMH_ADD_F32_04_1( psBody->m_vPT, v01 );
        psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    }
)


/* ---- tgPH_Body_Apply_Drag ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Apply_Drag_Command, Body, BODY, TgFLOAT32,

    if (!(uCMD.pCommand->Val >= 0.0F) || !(uCMD.pCommand->Val <= 1.0F))
    {
        return;
    }
    else
    {
        TgVEC_F32_04_1_C                    vDrag = tgMH_SET1_F32_04_1( uCMD.pCommand->Val );

        psBody->m_vLV = tgMH_MUL_F32_04_1( vDrag, psBody->m_vLV );
        psBody->m_vAV = tgMH_MUL_F32_04_1( vDrag, psBody->m_vAV );
        psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    };
)


/* ---- tgPH_Body_Add_Form_Command ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
PHYSICS_FUNCTION_DEFER_DEFINITION__COPY(Body_Add_Form_Command, Body, BODY, STg2_PH_Form_Command_Data,

    tgPH_Body_Add_Form_IMM( uCMD.pCommand->tiID, uCMD.pCommand->Val.m_tiFM0, &uCMD.pCommand->Val.m_sMass );

)


/* ---- tgPH_Body_Remove_Form_Command -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
PHYSICS_FUNCTION_DEFER_DEFINITION__COPY(Body_Remove_Form_Command, Body, BODY, STg2_PH_Form_Command_Data,

    tgPH_Body_Remove_Form_IMM( uCMD.pCommand->Val.m_tiFM0 );

)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Body_Add_Form ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Add_Form( TgPH_BODY_ID_C tiBY0, TgPH_FORM_ID_C tiFM0, STg2_PH_Mass_CPC psMass )
{
    STg2_PH_Form_Command_Data           sData;

    sData.m_tiFM0.m_uiKI = tiFM0.m_uiKI;
    tgMM_Copy( &sData.m_sMass, sizeof(STg2_PH_Mass), psMass, sizeof(STg2_PH_Mass) );

    tgPH_Body_Add_Form_Command( tiBY0, &sData );
}


/* ---- tgPH_Body_Remove_Form ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Remove_Form( TgPH_BODY_ID_C tiBY0, TgPH_FORM_ID_C tiFM0, STg2_PH_Mass_CPC psMass )
{
    STg2_PH_Form_Command_Data           sData;

    sData.m_tiFM0.m_uiKI = tiFM0.m_uiKI;
    tgMM_Copy( &sData.m_sMass, sizeof(STg2_PH_Mass), psMass, sizeof(STg2_PH_Mass) );

    tgPH_Body_Remove_Form_Command( tiBY0, &sData );
}


/* ---- tgPH_Body_Add_Force_At_Location ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Add_Force_At_Location( TgPH_BODY_ID_C tiBY0, TgVEC_F32_04_1_C vF0, TgVEC_F32_04_1_C vS0 )
{
    STg2_PH_Force_Command_Data          sData;

    sData.m_vF0 = vF0;
    sData.m_vS0 = vS0;

    tgPH_Body_Add_Force_At_Location_Command( tiBY0, &sData );
}


/* ---- tgPH_Body_Apply_Drag ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Apply_Drag( TgPH_BODY_ID_C tiBY0, TgFLOAT32_C fDrag )
{
    tgPH_Body_Apply_Drag_Command( tiBY0, fDrag );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Macro Functions                                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,First_Form_ID,TgPH_FORM_ID,m_tiFM_Head)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,First_Constraint_ID,TgPH_CONSTRAINT_ID,m_tiCT_Head)

PHYSICS_FUNCTION_QUERY_DEFINITION__COPY(Body,BODY,Moment_Of_Inertia,TgVEC_F32_04_3,m_sMass.m_mMOI)
PHYSICS_FUNCTION_QUERY_DEFINITION__COPY(Body,BODY,Inverse_Moment_Of_Inertia,TgVEC_F32_04_3,m_sMass.m_mInv_MOI) 
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Centre_Of_Gravity,TgVEC_F32_04_1,m_sMass.m_vCG)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Mass,TgVEC_F32_04_1,m_sMass.m_uMass.m_vF32_04_1)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Inverse_Mass,TgVEC_F32_04_1,m_sMass.m_uInv_Mass.m_vF32_04_1)

PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Last_Position_W,TgVEC_F32_04_1,m_vPos_Last_Valid_O2W)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Set_Position_W,Body,BODY,TgVEC_F32_04_1,
    psBody->m_vPos_O2W = tgMH_Init_Point_F32_04_1( uCMD.pCommand->Val );
    psBody->m_vPos_Last_Valid_O2W = psBody->m_vPos_O2W;
    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    tgPH_Body_Set_Update_IMM(psBody,true);
    tgPH_Body_Update__WRITE( psBody, true ); )
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Position_W,TgVEC_F32_04_1,m_vPos_O2W)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Set_Rotation_W,Body,BODY,TgVEC_F32_04_1,
    psBody->m_vRot_O2W = uCMD.pCommand->Val;
    tgMH_Init_Quat_F32_04_3(&psBody->m_mRot_O2W, psBody->m_vRot_O2W);
    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    tgPH_Body_Set_Update_IMM(psBody,true);
    tgPH_Body_Update__WRITE( psBody, true ); )
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Rotation_W,TgVEC_F32_04_1,m_vRot_O2W)
PHYSICS_FUNCTION_QUERY_DEFINITION__COPY(Body,BODY,Final_Transform_W,TgVEC_F32_04_3,m_mFinal_O2W)

PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Add_Linear_Velocity,Body,BODY,TgVEC_F32_04_1,
    psBody->m_vLV = tgMH_ADD_F32_04_1( psBody->m_vLV, tgMH_Init_Vector_F32_04_1( uCMD.pCommand->Val ) );
    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    tgPH_Body_Set_Update_IMM(psBody,true);)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Set_Linear_Velocity,Body,BODY,TgVEC_F32_04_1,
    psBody->m_vLV = tgMH_Init_Vector_F32_04_1( uCMD.pCommand->Val );
    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    tgPH_Body_Set_Update_IMM(psBody,true);)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Linear_Velocity,TgVEC_F32_04_1,m_vLV)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Add_Force,Body,BODY,TgVEC_F32_04_1,
    psBody->m_vXF = tgMH_ADD_F32_04_1( psBody->m_vXF, tgMH_Init_Vector_F32_04_1( uCMD.pCommand->Val ) );
    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    tgPH_Body_Set_Update_IMM(psBody,true);)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Force,TgVEC_F32_04_1,m_vXF)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Add_Persistent_Force,Body,BODY,TgVEC_F32_04_1,
    psBody->m_vPF = tgMH_ADD_F32_04_1( psBody->m_vPF, tgMH_Init_Vector_F32_04_1( uCMD.pCommand->Val ) );
    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    tgPH_Body_Set_Update_IMM(psBody,true);)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Set_Persistent_Force,Body,BODY,TgVEC_F32_04_1,
    psBody->m_vPF = tgMH_Init_Vector_F32_04_1( uCMD.pCommand->Val );
    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    tgPH_Body_Set_Update_IMM(psBody,true);)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Persistent_Force,TgVEC_F32_04_1,m_vPF)

PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Add_Angular_Velocity,Body,BODY,TgVEC_F32_04_1,
    psBody->m_vAV = tgMH_ADD_F32_04_1( psBody->m_vAV, tgMH_Init_Vector_F32_04_1( uCMD.pCommand->Val ) );
    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    tgPH_Body_Set_Update_IMM(psBody,true);)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Set_Angular_Velocity,Body,BODY,TgVEC_F32_04_1,
    psBody->m_vAV = tgMH_Init_Vector_F32_04_1( uCMD.pCommand->Val );
    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    tgPH_Body_Set_Update_IMM(psBody,true);)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Angular_Velocity,TgVEC_F32_04_1,m_vAV)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Add_Torque,Body,BODY,TgVEC_F32_04_1,
    psBody->m_vXT = tgMH_ADD_F32_04_1( psBody->m_vXT, tgMH_Init_Vector_F32_04_1( uCMD.pCommand->Val ) );
    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    tgPH_Body_Set_Update_IMM(psBody,true);)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Torque,TgVEC_F32_04_1,m_vXT)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Add_Persistent_Torque,Body,BODY,TgVEC_F32_04_1,
    psBody->m_vPT = tgMH_ADD_F32_04_1( psBody->m_vPT, tgMH_Init_Vector_F32_04_1( uCMD.pCommand->Val ) );
    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    tgPH_Body_Set_Update_IMM(psBody,true);)
PHYSICS_FUNCTION_DEFER_DEFINITION__ASSIGN(Body_Set_Persistent_Torque,Body,BODY,TgVEC_F32_04_1,
    psBody->m_vPT = tgMH_Init_Vector_F32_04_1( uCMD.pCommand->Val );
    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
    tgPH_Body_Set_Update_IMM(psBody,true);)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Persistent_Torque,TgVEC_F32_04_1,m_vPT)

PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(Body,BODY,Force_Field_Factor,TgVEC_F32_04_1,m_vForce_Field_Factor)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(Body,BODY,Time_Factor,TgVEC_F32_04_1,m_vTime_Factor)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Body,BODY,Disable_Timer,TgFLOAT32,m_fDisable_Timer)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Update,TgBOOL,m_bUpdate)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Body,BODY,Ragdoll,TgBOOL,m_bRagdoll)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(Body,BODY,CalcFM_FCN,TgPH_FCN_CALCFM,m_pfnCalcFM)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(Body,BODY,Contact_FCN,TgPH_FCN_CONTACT,m_pfnContact)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(Body,BODY,Moved_FCN,TgPH_FCN_MOVED,m_pfnMoved)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(Body,BODY,Context,TgUINT_PTR,m_uiContext)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Body_Contact_Default ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Contact_Default( TgATTRIBUTE_UNUSED TgPH_BODY_ID_C tiBY0, TgATTRIBUTE_UNUSED TgFLOAT32_C fΔt )
{
}


/* ---- tgPH_Body_Add_Form_IMM --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Add_Form_IMM( TgPH_BODY_ID_C tiBY, TgPH_FORM_ID_C tiFM, STg2_PH_Mass_CPC pMass )
{
    STg2_PH_Form_P                      psFM;
    STg2_PH_Body_P                      psBY;
    STg2_PH_Mass                        sMass;

    psFM = tgPH_Form_Get_Form_From_ID( tiFM );
    if (nullptr == psFM) TgATTRIBUTE_UNLIKELY
    {
        return;
    };

    psBY = tgPH_Body_Get_Body_From_ID( tiBY );
    if (nullptr == psBY) TgATTRIBUTE_UNLIKELY
    {
        return;
    };

    #pragma region Add the form into the form list of the Body.
    psFM->m_tiBY = tiBY;
    psFM->m_tiNext = psBY->m_tiFM_Head;
    psBY->m_tiFM_Head = tiFM;
    psFM->m_uiCategory |= (1ULL << KTgPH_CATEGORY_BIT__ENABLE_COLLSION);
    psFM->m_uiCategory |= psBY->m_bUpdate ? (1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING) : 0;
    tgPH_Form_Update_Category_Cache( psFM );
    #pragma endregion

    #pragma region Have the form update its World transforms.
    tgPH_Form_Update__WRITE( psFM, psBY, true );
    #pragma endregion

    #pragma region Move and rotate the Mass.
    tgMM_Copy( &sMass, sizeof(sMass), pMass, sizeof(STg2_PH_Mass) );
    tgPH_Mass_Rotate_Eul( &sMass, psFM->m_vRot_O2B );
    tgPH_Mass_Move( &sMass, tgMH_Init_Vector_F32_04_1( psFM->m_vPos_O2B ) );
    #pragma endregion

    #pragma region Integrate the Mass characteristics into the body.
    tgPH_Mass_Union_Mat( &psBY->m_sMass, &sMass );
    #pragma endregion
}


/* ---- tgPH_Body_Remove_Form_IMM ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Remove_Form_IMM( TgPH_FORM_ID_C tiFM )
{
    STg2_PH_Form_PC                     psFM = tgPH_Form_Get_Form_From_ID( tiFM );
    STg2_PH_Body_P                      psBY;
    TgPH_FORM_ID_P                      ptiFM;

    /* Make sure we have a valid form. */
    if (nullptr == psFM) TgATTRIBUTE_UNLIKELY
    {
        return;
    };

    psFM->m_uiCategory &= ~(1ULL << KTgPH_CATEGORY_BIT__ENABLE_COLLSION);
    psFM->m_uiCategory &= ~(1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING);
    tgPH_Form_Update_Category_Cache( psFM );

    /* Make sure we have a valid body. */
    psBY = tgPH_Body_Get_Body_From_ID( psFM->m_tiBY );
    if (nullptr == psFM) TgATTRIBUTE_UNLIKELY
    {
        return;
    };

    /* Get the head of the linked list of forms attached to the body. */
    ptiFM = &psBY->m_tiFM_Head;
    while (KTgID__INVALID_VALUE != ptiFM->m_uiKI)
    {
        if (tiFM.m_uiKI == ptiFM->m_uiKI)
        {
            ptiFM->m_uiKI =  psFM->m_tiNext.m_uiKI;
            return;
        }
        else
        {
            STg2_PH_Form_PC                     psFM1 = tgPH_Form_Get_Form_From_ID( *ptiFM );

            if (nullptr == psFM1) TgATTRIBUTE_UNLIKELY
            {
                return;
            };

            ptiFM = &psFM->m_tiNext;
        };
    };
}


/* ---- tgPH_Body_Set_Update_IMM ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Set_Update_IMM( STg2_PH_Body_PC psBY, TgBOOL_C bUpdate )
{
    if (bUpdate == (TgBOOL)psBY->m_bUpdate)
    {
        return;
    };

    psBY->m_bUpdate = bUpdate;

    if (KTgID__INVALID_VALUE != psBY->m_tiFM_Head.m_uiKI)
    {
        TgRSIZE_C                           uiCacheStride = KTgPH_CACHE_BIT__TOTAL_RESERVED;
        TgRSIZE_C                           nuiCacheItem = 64 / uiCacheStride;
        STg2_PH_Form_P                      psFM = tgPH_Form_Get_Form_From_ID( psBY->m_tiFM_Head );
        TgUINT_E64_PC                       puiFM_Category_Cache = g_aauiPH_Form_Used_Category[psBY->m_tiBody.m_uiWorld];

        if (bUpdate)
        {
            for (;nullptr != psFM; psFM = tgPH_Form_Get_Form_From_ID( psFM->m_tiNext ))
            {
                psFM->m_uiCategory |= 1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING;
                puiFM_Category_Cache[psFM->m_uiUsed_Index/nuiCacheItem] |= 1ULL << (uiCacheStride*(psFM->m_uiUsed_Index % nuiCacheItem) + KTgPH_CACHE_BIT__FORM_IS_UPDATING);
            };
        }
        else
        {
            for (;nullptr != psFM; psFM = tgPH_Form_Get_Form_From_ID( psFM->m_tiNext ))
            {
                psFM->m_uiCategory &= ~(1ULL << KTgPH_CATEGORY_BIT__FORM_IS_UPDATING);
                puiFM_Category_Cache[psFM->m_uiUsed_Index/nuiCacheItem] &= ~(1ULL << (uiCacheStride*(psFM->m_uiUsed_Index % nuiCacheItem) + KTgPH_CACHE_BIT__FORM_IS_UPDATING));
            };
        };
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Module_Body_Init_Internal ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Module_Body_Init_Internal( TgVOID )
{
#if defined(TgBUILD_FEATURE__CLIENT)
    g_anuiPH_Body_Increase_Commit[ETgPH_WORLD__CLIENT_FX] = 10;
    g_anuiPH_Body_Total_Commit[ETgPH_WORLD__CLIENT_FX] = 0;
    g_anuiPH_Body_Total_Reserve[ETgPH_WORLD__CLIENT_FX] = 1000;

    g_anuiPH_Body_Increase_Commit[ETgPH_WORLD__CLIENT_UI] = 10;
    g_anuiPH_Body_Total_Commit[ETgPH_WORLD__CLIENT_UI] = 0;
    g_anuiPH_Body_Total_Reserve[ETgPH_WORLD__CLIENT_UI] = 1000;
/*# defined(TgBUILD_FEATURE__CLIENT) */
#endif

#if defined(TgBUILD_FEATURE__SERVER)
    g_anuiPH_Body_Increase_Commit[ETgPH_WORLD__SERVER_DEFAULT] = 10;
    g_anuiPH_Body_Total_Commit[ETgPH_WORLD__SERVER_DEFAULT] = 0;
    g_anuiPH_Body_Total_Reserve[ETgPH_WORLD__SERVER_DEFAULT] = 10000;
/*# defined(TgBUILD_FEATURE__SERVER) */
#endif


}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Debug Functions                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Body_Validate ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_DEBUG__PHYSICS)
TgVOID tgPH_Body_Validate( STg2_Output_PC psOUT, TgPH_BODY_ID_C tiBY )
{
    (void)psOUT;
    (void)tiBY;

}
/*# defined(TgBUILD_DEBUG__PHYSICS) */
#endif
