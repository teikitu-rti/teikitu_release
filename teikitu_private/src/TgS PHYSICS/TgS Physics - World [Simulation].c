/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - World [Simulation].c
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
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Update_World__Simulate_Batch_IMM ------------------------------------------------------------------------------------------------------------------------------------ */
/* SYNC: READS World, WRITES to Bodies that are contained in this Batch (ONLY) - Each Batch is guaranteed to be unique and independent (No access by other jobs).                  */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Simulate_Batch_IMM( TgPH_WORLD_ID_C tiWorld, TgRSIZE_C uiBegin, TgRSIZE_C uiEnd )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );
    STg2_PH_Update__Simulation_CPC      psUpdate_Simulation = g_asPH_Update__Simulation + tiWorld.m_uiI;
    TgVEC_F32_04_1_C                    vStep_Size_RCP = tgMH_RCP_F32_04_1( psWorld->m_vStep_Size );
    TgVEC_F32_04_1_C                    vOne = tgMH_SET1_F32_04_1( 1.0F );
    TgRSIZE                             uiIndex;

    TgPARAM_CHECK(nullptr != psWorld);

    /* We need access to read the world, and update (write) access to world updates fields (not done through synchronization objects). */

    #pragma region Initialize all of the simulation frame values.
    for (uiIndex = uiBegin; uiIndex < uiEnd; ++uiIndex)
    {
        STg2_PH_Body_PC                     psBY = g_aapsPH_Body_Used[tiWorld.m_uiI][uiIndex];
        TgVEC_F32_04_1_C                    vForce_Field = tgMH_MUL_F32_04_1( psWorld->m_vForce_Field, psBY->m_vForce_Field_Factor );
        TgVEC_F32_04_3                      mK0, mK1, mIT;
        TgVEC_F32_04_1                      vAM, vAMxAV;
        TgVEC_F32_04_1                      vDisable_Test;

        TgDIAG(uiIndex == psBY->m_uiUsed_Index);

        #pragma region Check for the body being disabled
        if (!psBY->m_bUpdate)
        {
            psBY->m_vXT = psBY->m_vPT;
            psBY->m_vXF = tgMH_MAD_F32_04_1( vForce_Field, psBY->m_sMass.m_uMass.m_vF32_04_1, tgMH_ADD_F32_04_1( psBY->m_vPF, psBY->m_vXF ) );

            psUpdate_Simulation->m_avBY_Pos_O2W[uiIndex] = psBY->m_vPos_O2W;
            psUpdate_Simulation->m_avRHS_LA[uiIndex*2 + 0] = KTgZERO_F32_04_1;
            psUpdate_Simulation->m_avRHS_LA[uiIndex*2 + 1] = KTgZERO_F32_04_1;

            continue;
        };
        #pragma endregion

        #pragma region Calculate the Inertia Tensor and its Inverse.
        tgMH_CAT_F32_04_3( &mK0, &psBY->m_sMass.m_mMOI, &psBY->m_mRot_O2W );
        tgMH_CAT_F32_04_3( &mIT, &psBY->m_mRot_O2W, &mK0 );
        tgMH_CAT_F32_04_3( &mK1, &psBY->m_sMass.m_mInv_MOI, &psBY->m_mRot_O2W );
        tgMH_CAT_F32_04_3( &psBY->m_mInverse_Inertia_Tensor, &psBY->m_mRot_O2W, &mK1 );
        #pragma endregion

        #pragma region Calculate Rotational Force and Torque(て).
        vAM = tgMH_TX_F32_04_3( psBY->m_vAV, &mIT );
        vAMxAV = tgMH_CX_F32_04_1( vAM, psBY->m_vAV );
        psBY->m_vXT = tgMH_SUB_F32_04_1( psBY->m_vPT, vAMxAV );
        #pragma endregion

        #pragma region Test for auto-disable (sleep).
        vDisable_Test = tgMH_CMP_LT_F32_04_1( tgMH_LSQ_F32_04_1( psBY->m_vXF ), vOne );
        vDisable_Test = tgMH_AND_F32_04_1( tgMH_CMP_LT_F32_04_1( tgMH_LSQ_F32_04_1( psBY->m_vXT ), vOne ), vDisable_Test );
        vDisable_Test = tgMH_AND_F32_04_1( tgMH_CMP_LT_F32_04_1( tgMH_LSQ_F32_04_1( psBY->m_vLV ), vOne ), vDisable_Test );
        vDisable_Test = tgMH_AND_F32_04_1( tgMH_CMP_LT_F32_04_1( tgMH_LSQ_F32_04_1( psBY->m_vAV ), vOne ), vDisable_Test );
        if (!tgMH_CMP_ALL_TO_BOOL_F32_04_1( vDisable_Test ))
            psBY->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
        else
            psBY->m_fDisable_Timer -= psWorld->m_fStep_Size_Seconds;
        #pragma endregion

        #pragma region Add Force Field and External Force.
        #if defined(TgBUILD_DEBUG__PHYSICS__EXTENSIVE_DATA_CHECK) && TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__DIAG
        TgDIAG(((TgVEC_S_F32_04_1_CP)&vForce_Field)->w == 0.0F);
        TgDIAG(((TgVEC_S_F32_04_1_CP)&psBY->m_vPF)->w == 0.0F);
        TgDIAG(((TgVEC_S_F32_04_1_CP)&psBY->m_vXF)->w == 0.0F);
        /*# defined(TgBUILD_DEBUG__PHYSICS__EXTENSIVE_DATA_CHECK) && TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__DIAG */
        #endif
        psBY->m_vXF = tgMH_MAD_F32_04_1( vForce_Field, psBY->m_sMass.m_uMass.m_vF32_04_1, tgMH_ADD_F32_04_1( psBY->m_vPF, psBY->m_vXF ) );
        #pragma endregion

        #pragma region Check for a user defined function to determine force/moments.
        if (nullptr != psBY->m_pfnCalcFM)
        {
            TgVEC_F32_04_1                      vF, vT;

            psBY->m_pfnCalcFM( &vF, &vT, psBY->m_tiBody, psBY->m_uiContext, psWorld->m_vStep_Size );
            psBY->m_vXF = tgMH_ADD_F32_04_1( psBY->m_vXF, vF );
            psBY->m_vXT = tgMH_ADD_F32_04_1( psBY->m_vXT, vT );
        };
        #pragma endregion

        #pragma region Calculate the desired state.
        {
            TgVEC_F32_04_1_C                    vLA = tgMH_MUL_F32_04_1( psBY->m_sMass.m_uInv_Mass.m_vF32_04_1, psBY->m_vXF ); /* Predicted Linear Acceleration */
            TgVEC_F32_04_1_C                    vLV = tgMH_MAD_F32_04_1( psWorld->m_vStep_Size, vLA, psBY->m_vLV ); /* PredicteD:\development\ode\dcylinder.cppd Linear Velocity */
            TgVEC_F32_04_1_C                    vPos_O2W = tgMH_MAD_F32_04_1( psWorld->m_vStep_Size, vLV, psBY->m_vPos_O2W ); /* Predicted Position */

            TgVEC_F32_04_1_C                    vAA = tgMH_TX_F32_04_3( psBY->m_vXT, &psBY->m_mInverse_Inertia_Tensor ); /* Predicted Angular Acceleration */
            TgVEC_UN_F32_04_1_C                 uAV = { .m_vF32_04_1 = tgMH_MAD_F32_04_1( psWorld->m_vStep_Size, vAA, psBY->m_vAV ) }; /* Predicted Angular Velocity */
            TgVEC_UN_F32_04_1_C                 uQR = { .m_vF32_04_1 = psBY->m_vRot_O2W };
            TgVEC_S_F32_04_1_C                  vQR = uQR.m_vS_F32_04_1;
            TgVEC_UN_F32_04_1_C                 uΔQ = { .m_vS_F32_04_1 = {
                                                    .x = 0.5F*(-uAV.m_vS_F32_04_1.x * vQR.x - uAV.m_vS_F32_04_1.y * vQR.y - uAV.m_vS_F32_04_1.z * vQR.z),
                                                    .y = 0.5F*( uAV.m_vS_F32_04_1.x * vQR.w + uAV.m_vS_F32_04_1.y * vQR.z - uAV.m_vS_F32_04_1.z * vQR.y),
                                                    .z = 0.5F*(-uAV.m_vS_F32_04_1.x * vQR.z + uAV.m_vS_F32_04_1.y * vQR.w + uAV.m_vS_F32_04_1.z * vQR.x),
                                                    .w = 0.5F*( uAV.m_vS_F32_04_1.x * vQR.y - uAV.m_vS_F32_04_1.y * vQR.x + uAV.m_vS_F32_04_1.z * vQR.w)
                                                } };
            TgVEC_F32_04_1_C                    vQ = tgMH_MAD_F32_04_1( uΔQ.m_vF32_04_1, psWorld->m_vStep_Size, psBY->m_vRot_O2W );
            TgVEC_F32_04_1_C                    vRot_O2W = tgMH_NORM_F32_04_1( vQ );

            /* Copy the body position into Simulation storage for use in Constraints (calculating moment arms). */
            psUpdate_Simulation->m_avBY_Pos_O2W[uiIndex] = vPos_O2W;

            /* Calculate and store information needed for determining the RHS. */
            psUpdate_Simulation->m_avRHS_LA[uiIndex*2 + 0] = tgMH_MAD_F32_04_1( psBY->m_vLV, vStep_Size_RCP, vLA ); /* RHS - Linear Constraint */
            psUpdate_Simulation->m_avRHS_LA[uiIndex*2 + 1] = tgMH_MAD_F32_04_1( psBY->m_vAV, vStep_Size_RCP, vAA );  /* RHS - Angular Constraint */

            #pragma region Calculate all active Forms predicted Final Transform, Position, and Swept AABBs.
            if (KTgID__INVALID_VALUE != psBY->m_tiFM_Head.m_uiKI)
            {
                TgVEC_F32_04_3_PC                   amFM_Final_O2W = psUpdate_Simulation->m_amFM_Final_O2W;
                STg2_PH_Form_P                      psFM = tgPH_Form_Get_Form_From_ID( psBY->m_tiFM_Head );
                TgVEC_F32_04_3                      mFinal_O2W;

                /* Construct the Reference Frame for the Form based on the Body's Predicted motion from the Simulation Step. */
                tgMH_Init_Reference_Frame_From_Quaternion_Position_F32_04_3( &mFinal_O2W, vRot_O2W, vPos_O2W );

                for (;nullptr != psFM; psFM = tgPH_Form_Get_Form_From_ID( psFM->m_tiNext ))
                {
                    TgVEC_F32_04_3                      mFM_Final_O2W;
                    TgVEC_F32_04_1                      vFM_Pos_O2W, vΔPos_O2W;
                    UTg2_CO_Primitive_F32_04            uPM;
                    TgBOXAA_F32_04                      sBA;

                    /* Calculate the predicted transform and position, and translation from the current to the predicted positon. */
                    tgMH_CAT_F32_04_3( &mFM_Final_O2W, &psFM->m_mLocal_O2B, &mFinal_O2W );
                    vFM_Pos_O2W = tgMH_Query_Axis_3_F32_04_3( &mFM_Final_O2W );
                    vΔPos_O2W = tgMH_SUB_F32_04_1( vFM_Pos_O2W, psFM->m_vPos_O2W );

                    /* Copy the transform and position into Simulation storage for use in the Collision Pass. */
                    tgMM_Copy( amFM_Final_O2W + psFM->m_uiUsed_Index, sizeof(amFM_Final_O2W[0]), &mFM_Final_O2W, sizeof(mFM_Final_O2W) );
                    psUpdate_Simulation->m_avFM_Pos_O2W[psFM->m_uiUsed_Index] = vFM_Pos_O2W;

                    /* Primitive at its final predicted position and rotation, swept backwards towards its origination. */
                    psFM->m_pfnPM_Copy_TX( &uPM, &psFM->m_uPM, &mFM_Final_O2W );
                    psFM->m_pfnPM_Sweep_BA( &sBA, &uPM, tgMH_NEG_F32_04_1( vΔPos_O2W ) );

                    /* Primitive at its previous position and rotation, swept forward towards towards its new position. */
                    psFM->m_pfnPM_Copy_TX( &uPM, &psFM->m_uPM, &psFM->m_mFinal_O2W );
                    psFM->m_pfnPM_Sweep_BA( psUpdate_Simulation->m_asFM_BA_W + psFM->m_uiUsed_Index, &uPM, vΔPos_O2W );

                    /* Union of these two swept spaces. */
                    tgGM_BA_Union_BA_F32_04( psUpdate_Simulation->m_asFM_BA_W + psFM->m_uiUsed_Index, &sBA );
                };
            };
            #pragma endregion
        };
        #pragma endregion
    };
    #pragma endregion
}
