/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - World [Problem Set].c
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
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgPH_Update_World__Init_Solver_Set(
    STg2_PH_Solver__Set_PC TgANALYSIS_NO_NULL ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, TgRSIZE_AP TgANALYSIS_NO_NULL ARG3 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Update_World__Build_Sets -------------------------------------------------------------------------------------------------------------------------------------------- */
/* SYNC: READS Constraints - Responsible for creating the self-contained (independent) Solver Sets | WRITES Bodies                                                                 */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Update_World__Build_Sets( TgPH_WORLD_ID_C tiWorld )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );
    STg2_Job_PC                         psJob = g_asPH__Job__Update_World__Solve_Sets + tiWorld.m_uiI;
    union { STg2_PH_Job__Update_World__Solve_Set_Data_P psSolve_Set_Data; TgUINT_E08_P pui; } const sJob_Data = { .pui  = psJob->m_auiData };

    STg2_PH_Solver__Set_PC              psSolver_Set = &sJob_Data.psSolve_Set_Data->m_sSolver_Set;

    TgRSIZE_C                           nuiBody_World = TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Body_Total__Used + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) );
    TgRSIZE_C                           nuiConstraint_World_Used = TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Constraint_Total__Used + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) );

    STg2_PH_Body_PP                     apsBody_Stack;

    TgRSIZE                             nuiBody_Stack;
    TgRSIZE                             uiIndex_Body;
    TgPH_BODY_ID                        tiBody;
    STg2_PH_Body_P                      psBY;
    TgPH_CONSTRAINT_ID                  tiConstraint;
    STg2_PH_Constraint_P                psCT;
    TgBOOL                              bFinish_Batch;
    TgFLOAT32                           fMax_Disable_Timer;
    TgRSIZE                             uiSet_Start;

    tgMM_Set_U08_0x00( psSolver_Set, sizeof( STg2_PH_Solver__Set ) );
    sJob_Data.psSolve_Set_Data->m_tiWorld = tiWorld;

    TgDIAG(0 == TgSTD_ATOMIC(load_explicit)( g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) ));

    /* The collision system is responsible for preventing bodies from generating overly large penetrations or tunnelling. Since collision is executed on the list of forms, it
        is necessary to aggregate the corrections on a per body basis once all of the corrections are known. For accuracy (if desired) any bodies marked as tunneling can then
        be retested for contacts after previous contact constraints are removed. */

    /* Left Blank on Purpose - Contact Points from Sweep Tests appear to be working sufficiently. */

    /* The goal of set generation is to create a sequence of closed sets (all bodies, constraints and contacts in a set only involve other entities in the set) that result in
        an even amount of computation. In the case where it is not possible to have even work loads, then the heavier jobs should come first as they will have more time to
        complete. The heuristic to determine an even amount of computation is to use the number of bodies and the total number of degrees of freedom to be determined. A set is
        a component of the graph constructed using bodies as the nodes, and constraints as the edges. */

    #pragma region Memory Allocation and Memory Clears
    tgMM_Set_U08_0x00( g_aauiVisited_Body[tiWorld.m_uiI], ((nuiBody_World+ 63) >> 6) * sizeof(STg2_PH_Body_P) );
    nuiBody_Stack = 0;
    if (nuiConstraint_World_Used > 0)
    {
        apsBody_Stack = (STg2_PH_Body_PP)TgMALLOC_TEMP( sizeof( STg2_PH_Body_P ) * tgCM_MIN_UMAX( nuiBody_World, nuiConstraint_World_Used ) );
        TgCRITICAL_MSGF( nullptr != apsBody_Stack, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

        tgMM_Set_U08_0x00( g_aauiVisited_Constraint[tiWorld.m_uiI], ((g_anuiPH_Constraint_Total_Reserve[tiWorld.m_uiI] + 63) >> 6) * sizeof(STg2_PH_Constraint_P) );
    }
    else
    {
        apsBody_Stack = nullptr;
    }
    #pragma endregion

    #pragma region Memory Allocation - Solver Set
    tgPH_Update_World__Init_Solver_Set( psSolver_Set, nuiBody_World, nuiConstraint_World_Used, g_aaxnuiPH_Constraint_Total__Used_By_Type[tiWorld.m_uiI] );
    #pragma endregion

    PROFILE_ARRAY_START( tiWorld.m_uiI, PH_BUILD_SETS_INNER, tgPH_Update_World__Build_Sets );
    PROFILE_START( PH_BUILD_SETS_INNER_TOTAL, tgPH_Update_World__Build_Sets );

    #pragma region Create the Closed Sets to be Solved
    for (uiIndex_Body = 0; uiIndex_Body < nuiBody_World; ++uiIndex_Body)
    {
        /* Test the visited bit for this body. */
        if (0 != (g_aauiVisited_Body[tiWorld.m_uiI][uiIndex_Body >> 6] & (1ULL << (uiIndex_Body & 63ULL))))
            continue;

        /* Test the disabled bit for this body. */
        psBY = g_aapsPH_Body_Used[tiWorld.m_uiI][uiIndex_Body];
        TgDIAG_MSGF( psBY->m_uiUsed_Index == uiIndex_Body, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Logic Failure: used index does not match used array index." );
        if (true != psBY->m_bUpdate)
            continue;

        /* Mark the body as visited. */
        g_aauiVisited_Body[tiWorld.m_uiI][uiIndex_Body >> 6] |= 1ULL << (uiIndex_Body & 63ULL);
        nuiBody_Stack = 0;
        fMax_Disable_Timer = 0.0F;
        uiSet_Start = psSolver_Set->m_nuiBody;
        while(1)
        {
            #pragma region Add a body to the Set
            /* Assign the body into the set. */
            psSolver_Set->m_apsBody[psSolver_Set->m_nuiBody] = psBY;
            ++psSolver_Set->m_nuiBody;
            if (!psBY->m_bUpdate)
            {
                tgPH_Body_Set_Update_IMM( psBY, true );
            };
            #pragma endregion

            #pragma region Auto-Disable
            fMax_Disable_Timer = tgCM_MAX_F32( fMax_Disable_Timer, psBY->m_fDisable_Timer );
            #pragma endregion

            /* Process the joints attached to this body. Avoid the use of a recursive function call by adding other bodies into an array which is processed inside the loop. */
            tiConstraint.m_uiKI = psBY->m_tiCT_Head.m_uiKI;
            while (KTgID__INVALID_VALUE != tiConstraint.m_uiKI)
            {
                TgDIAG_MSGF( nuiConstraint_World_Used > 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Logic Failure: a valid constraint id in a world with no constraints." );
                psCT = g_aasPH_Constraint[tiWorld.m_uiI] + tiConstraint.m_uiI;

                TgDIAG(psCT->m_tiConstraint.m_uiKI == tiConstraint.m_uiKI);

                /* Test the visited bit for this constraint. */
                while (0 == (g_aauiVisited_Constraint[tiWorld.m_uiI][psCT->m_tiConstraint.m_uiI >> 6] & (1ULL << (psCT->m_tiConstraint.m_uiI & 63ULL))))
                {
                    #pragma region Add a constraint to the set

                    /* Mark the constraint as visited. */
                    g_aauiVisited_Constraint[tiWorld.m_uiI][psCT->m_tiConstraint.m_uiI >> 6] |= (1ULL << (psCT->m_tiConstraint.m_uiI & 63ULL));

                    /* Assign the constraint into the set for the constraint type. */
                    psSolver_Set->m_apsConstraint[psCT->m_enConstraint][psSolver_Set->m_nuiConstraint[psCT->m_enConstraint]] = psCT;
                    psSolver_Set->m_apuiDoF[psCT->m_enConstraint][psSolver_Set->m_nuiConstraint[psCT->m_enConstraint]] = psSolver_Set->m_nuiDoF;
                    ++psSolver_Set->m_nuiConstraint[psCT->m_enConstraint];

                    #pragma region Process the first body attached to this constraint
                    tiBody.m_uiKI = psCT->m_tiBY0.m_uiKI;
                    if (KTgID__INVALID_VALUE != tiBody.m_uiKI)
                    {
                        STg2_PH_Body_P                      psBYX = g_aasPH_Body[tiWorld.m_uiI] + tiBody.m_uiI;

                        #pragma region Add body to the processing stack if it is has not already been visited.
                        if (0 == (g_aauiVisited_Body[tiWorld.m_uiI][psBYX->m_uiUsed_Index >> 6] & (1ULL << (psBYX->m_uiUsed_Index & 63ULL))))
                        {
                            TgPARAM_CHECK(g_aapsPH_Body_Used[tiWorld.m_uiI][psBYX->m_uiUsed_Index] == psBYX);
                            g_aauiVisited_Body[tiWorld.m_uiI][psBYX->m_uiUsed_Index >> 6] |= (1ULL << (psBYX->m_uiUsed_Index & 63ULL));
                            apsBody_Stack[nuiBody_Stack] = psBYX;
                            ++nuiBody_Stack;
                        };
                        #pragma endregion

                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 0] = psBYX->m_sMass.m_uInv_Mass.m_vF32_04_1;
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 1] = tgMH_Query_Col_0_F32_04_3(&psBYX->m_mInverse_Inertia_Tensor);
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 2] = tgMH_Query_Col_1_F32_04_3(&psBYX->m_mInverse_Inertia_Tensor);
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 3] = tgMH_Query_Col_2_F32_04_3(&psBYX->m_mInverse_Inertia_Tensor);

                        psSolver_Set->m_auiJacobian_Index[psSolver_Set->m_nuiConstraint_Total*2 + 0] = psBYX->m_uiUsed_Index;
                    }
                    else
                    {
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 0] = tgMH_SET1_F32_04_1( 0.0F );
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 1] = tgMH_SET1_F32_04_1( 0.0F );
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 2] = tgMH_SET1_F32_04_1( 0.0F );
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 3] = tgMH_SET1_F32_04_1( 0.0F ); 

                        psSolver_Set->m_auiJacobian_Index[psSolver_Set->m_nuiConstraint_Total*2 + 0] = KTgMAX_RSIZE;
                    };
                    #pragma endregion

                    #pragma region Process the second body attached to this constraint
                    tiBody.m_uiKI = psCT->m_tiBY1.m_uiKI;
                    if (KTgID__INVALID_VALUE != tiBody.m_uiKI)
                    {
                        STg2_PH_Body_P                      psBYX = g_aasPH_Body[tiWorld.m_uiI] + tiBody.m_uiI;

                        #pragma region Add body to the processing stack if it is has not already been visited.
                        if (0 == (g_aauiVisited_Body[tiWorld.m_uiI][psBYX->m_uiUsed_Index >> 6] & (1ULL << (psBYX->m_uiUsed_Index & 63ULL))))
                        {
                            TgPARAM_CHECK(g_aapsPH_Body_Used[tiWorld.m_uiI][psBYX->m_uiUsed_Index] == psBYX);
                            g_aauiVisited_Body[tiWorld.m_uiI][psBYX->m_uiUsed_Index >> 6] |= (1ULL << (psBYX->m_uiUsed_Index & 63ULL));
                            apsBody_Stack[nuiBody_Stack] = psBYX;
                            ++nuiBody_Stack;
                        };
                        #pragma endregion

                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 4] = psBYX->m_sMass.m_uInv_Mass.m_vF32_04_1;
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 5] = tgMH_Query_Col_0_F32_04_3(&psBYX->m_mInverse_Inertia_Tensor);
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 6] = tgMH_Query_Col_1_F32_04_3(&psBYX->m_mInverse_Inertia_Tensor);
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 7] = tgMH_Query_Col_2_F32_04_3(&psBYX->m_mInverse_Inertia_Tensor);

                        psSolver_Set->m_auiJacobian_Index[psSolver_Set->m_nuiConstraint_Total*2 + 1] = psBYX->m_uiUsed_Index;
                    }
                    else
                    {
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 4] = tgMH_SET1_F32_04_1( 0.0F );
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 5] = tgMH_SET1_F32_04_1( 0.0F );
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 6] = tgMH_SET1_F32_04_1( 0.0F );
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 7] = tgMH_SET1_F32_04_1( 0.0F ); 

                        psSolver_Set->m_auiJacobian_Index[psSolver_Set->m_nuiConstraint_Total*2 + 1] = KTgMAX_RSIZE;
                    };
                    #pragma endregion

                    /* Aggregate the number of degrees of freedom that will need to be solved. */
                    psSolver_Set->m_nuiDoF += psCT->m_nuiDoF;
                    psSolver_Set->m_anuiDoF[psSolver_Set->m_nuiConstraint_Total] = psSolver_Set->m_nuiDoF;
                    ++psSolver_Set->m_nuiConstraint_Total;
                    #pragma endregion
                };

                /* Continue down the linked list of constraints that match the original body id. */

                #pragma region Continue walking through the list of contraints attached to the body from the start of the loop.
                if (psCT->m_tiBY0.m_uiKI == psBY->m_tiBody.m_uiKI)
                {
                    tiConstraint.m_uiKI = psCT->m_tiNext_0.m_uiKI;
                    continue;
                };

                if (psCT->m_tiBY1.m_uiKI == psBY->m_tiBody.m_uiKI)
                {
                    tiConstraint.m_uiKI = psCT->m_tiNext_1.m_uiKI;
                    continue;
                };
                #pragma endregion

                tiConstraint.m_uiKI = KTgID__INVALID_VALUE;
            }

            if (0 == nuiBody_Stack)
                break;

            psBY = apsBody_Stack[nuiBody_Stack - 1];
            --nuiBody_Stack;
        };

        /* Handle auto disable (sleeping) of the entire problem set - Facilitates sleeping a group of touching bodies. It is important that both the velocity and the acceleration
           are used to determine if a body is capable of being auto-disabled (1st and 2nd derivatives). It is possible that a body will be near zero at the epigee of motion but
           the acceleration would then be non-zero. */

        if (fMax_Disable_Timer < psWorld->m_fStep_Size_Seconds)
        {
            do
            {
                --psSolver_Set->m_nuiBody;
                tgPH_Body_Set_Update_IMM( psSolver_Set->m_apsBody[psSolver_Set->m_nuiBody], false );
            }
            while (psSolver_Set->m_nuiBody > uiSet_Start);
            continue;
        };

        /* If there are no more bodies left in the world to process, or if we exceed the minimum computer limits then queue the job. */

        bFinish_Batch  = uiIndex_Body + 1 >= nuiBody_World;
        bFinish_Batch |= psSolver_Set->m_nuiBody >= psWorld->m_uiSolver_Min_Body_Per_Job;
        bFinish_Batch |= psSolver_Set->m_nuiDoF >= psWorld->m_uiSolver_Min_DoF_Per_Job;

        #pragma region Queue this Set to be solved once it has exceeded the minimal compute limits.
        if (bFinish_Batch)
        {
            TgSTD_ATOMIC(fetch_add)( g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS + tiWorld.m_uiI, 1 );
            if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, psJob )))
            {
                /* On failure, execute the job directly. */
                TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
                tgPH_Update_World__Job__Solve_Sets( psJob );
            };

            /* Initialize a new solver set. */
            tgPH_Update_World__Init_Solver_Set( psSolver_Set, nuiBody_World, nuiConstraint_World_Used, g_aaxnuiPH_Constraint_Total__Used_By_Type[tiWorld.m_uiI] );
        };
        #pragma endregion
    };
    #pragma endregion

    if (psSolver_Set->m_nuiBody || psSolver_Set->m_nuiDoF)
    {
        TgSTD_ATOMIC(fetch_add)( g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS + tiWorld.m_uiI, 1 );
        if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, psJob )))
        {
            /* On failure, execute the job directly. */
            TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
            tgPH_Update_World__Job__Solve_Sets( psJob );
        };

        /* Initialize a the body and constraint data structure used in this loop. */
        tgMM_Set_U08_0x00( psSolver_Set, sizeof( STg2_PH_Solver__Set ) );
    };

    PROFILE_STOP( PH_BUILD_SETS_INNER_TOTAL, tgPH_Update_World__Build_Sets );
    PROFILE_ARRAY_STOP( tiWorld.m_uiI, PH_BUILD_SETS_INNER, tgPH_Update_World__Build_Sets );

    /* Free the memory that was used to create the batch jobs. */
    tgPH_Update_World__Free_Solver_Set( psSolver_Set );

    if (nullptr != apsBody_Stack)
        TgFREE_TEMP( apsBody_Stack );

    return (KTgS_OK);
}


/* ---- tgPH_Update_World__Define_Problem_And_Solve ------------------------------------------------------------------------------------------------------------------------------ */
/* SYNC: READS Bodies, Constraints that are contained in this Solver Set (ONLY) - Each Solver Set is guaranteed to be unique and independent (No access by other jobs).            */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Define_Problem_And_Solve( TgPH_WORLD_ID_C tiWorld, STg2_PH_Solver__Set_PC psSolver_Set )
{
    TgPARAM_CHECK(nullptr != psSolver_Set);

    #pragma region Allocate memory for the storage of the problem (LCP) coefficients and solution.
    psSolver_Set->m_avProblem_Coefficients = (TgVEC_F32_04_1_P)TgMALLOC_TEMP( sizeof( TgVEC_F32_04_1 )*ETgPH_PCI__VEC_PER_DOF*psSolver_Set->m_nuiDoF );
    TgCRITICAL_MSGF( nullptr != psSolver_Set->m_avProblem_Coefficients, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
    #pragma endregion

    #pragma region Call each of the constraint solver functions. [Read data from Bodies, Constraints, and global data created for this World Step Update.]
    tgPH_Constraint_Contact__Problem_Definition( tiWorld, psSolver_Set );
    tgPH_Constraint_Fixed__Problem_Definition( tiWorld, psSolver_Set );

    #pragma endregion

    #pragma region Solve the LCP. [Read/Write to data in the Solver Set (only).]
    tgPH_SV_SOR_LCP( tiWorld, psSolver_Set );
    #pragma endregion

    #pragma region Release the problem coefficients
    TgFREE_TEMP( psSolver_Set->m_avProblem_Coefficients );
    psSolver_Set->m_avProblem_Coefficients = nullptr;
    #pragma endregion
}


/* ---- tgPH_Update_World__Update_Bodies_IMM ------------------------------------------------------------------------------------------------------------------------------------- */
/* SYNC: WRITES to Bodies that are contained in this Solver Set (ONLY) - Each Solver Set is guaranteed to be unique and independent (No access by other jobs).                     */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Update_Bodies_IMM( TgPH_WORLD_ID_C tiWorld, STg2_PH_Solver__Set_PC psSolver_Set )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );
    TgRSIZE                             uiIndex;

    TgPARAM_CHECK(nullptr != psSolver_Set);
    TgPARAM_CHECK(nullptr != psWorld);

    /* Update all of the bodies given the calculated solution. */

    if (nullptr != psSolver_Set->m_avResult)
    {
        /* Apply the constraint forces and torques over the full time step (i.e. disregarding the body's time factor). This prevents issues with the simulation when time is
        manipulated (e.g. bullet time). Non-constraint forces and torques are time scaled, as is the integration into the position and rotation update. */

        for (uiIndex = 0; uiIndex < psSolver_Set->m_nuiBody; ++uiIndex)
        {
            STg2_PH_Body_PC                     psBY = psSolver_Set->m_apsBody[uiIndex];

            TgVEC_F32_04_1_C                    vCF = psSolver_Set->m_avResult[psBY->m_uiUsed_Index*2 + 0]; /* Constraint Force */
            TgVEC_F32_04_1_C                    vLA = tgMH_MUL_F32_04_1( psBY->m_sMass.m_uInv_Mass.m_vF32_04_1, vCF ); /* Linear Acceleration due to Constraint Force*/
            TgVEC_F32_04_1_C                    vLV = tgMH_MAD_F32_04_1( psWorld->m_vStep_Size, vLA, psBY->m_vLV ); /* Uncapped Linear Velocity */

            TgVEC_F32_04_1_C                    vCτ = psSolver_Set->m_avResult[psBY->m_uiUsed_Index*2 + 1]; /* Constraint Torque */
            TgVEC_F32_04_1_C                    vAA = tgMH_TX_F32_04_3( vCτ, &psBY->m_mInverse_Inertia_Tensor ); /* Angular Acceleration due to Constraint Torque */
            TgVEC_F32_04_1_C                    vAV = tgMH_MAD_F32_04_1( psWorld->m_vStep_Size, vAA, psBY->m_vAV ); /* Uncapped Angular Velocity */

            psBY->m_vLV = vLV; // tgMH_MAD_F32_04_1( psWorld->m_vStep_Size, vCF, psBY->m_vLV );
            psBY->m_vAV = vAV; // tgMH_MAD_F32_04_1( psWorld->m_vStep_Size, vCτ, psBY->m_vAV );

            TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( psBY->m_vLV )));
            TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( psBY->m_vAV )));

            /*{
                TgCHAR_U8                           uszBuffer[1024];

                tgUSZ_PrintF( uszBuffer, sizeof( uszBuffer ), u8"Body (%d)  |  LV [%+12.7f,%+12.7f,%+12.7f]  |  AV [%+12.7f,%+12.7f,%+12.7f]",
                    psBY->m_uiUsed_Index,

                    psSolver_Set->m_avResult[psBY->m_uiUsed_Index*2 + 0].m_aData[0],
                    psSolver_Set->m_avResult[psBY->m_uiUsed_Index*2 + 0].m_aData[1],
                    psSolver_Set->m_avResult[psBY->m_uiUsed_Index*2 + 0].m_aData[2],

                    psSolver_Set->m_avResult[psBY->m_uiUsed_Index*2 + 1].m_aData[0],
                    psSolver_Set->m_avResult[psBY->m_uiUsed_Index*2 + 1].m_aData[1],
                    psSolver_Set->m_avResult[psBY->m_uiUsed_Index*2 + 1].m_aData[2]
                );
            
                TgLOGF(KTgCN_CHANEL_LOG|KTgCN_SEVERITY_A, STD_MSG_LITERAL_1X, STD_MSG_POST, uszBuffer );
            }*/
        };
    };

    for (uiIndex = 0; uiIndex < psSolver_Set->m_nuiBody; ++uiIndex)
    {
        STg2_PH_Body_PC                     psBY = psSolver_Set->m_apsBody[uiIndex];

        if (!psBY->m_bUpdate)
        {
            psBY->m_vXF = tgMH_SET1_F32_04_1( 0.0F );
            psBY->m_vXT = tgMH_SET1_F32_04_1( 0.0F );
            continue;
        }
        else if (nullptr != psBY->m_pfnMoved) TgATTRIBUTE_UNLIKELY
        {
            psBY->m_pfnMoved( psBY->m_tiBody, psBY->m_uiContext );
        }
        else 
        {
            TgVEC_F32_04_1_C                    vScaled_Step_Size = tgMH_MUL_F32_04_1( psBY->m_vTime_Factor, psWorld->m_vStep_Size );

            #pragma region Calculate the linear velocity of the body (and apply limits).

            TgVEC_F32_04_1_C                    vLA = tgMH_MUL_F32_04_1( psBY->m_sMass.m_uInv_Mass.m_vF32_04_1, psBY->m_vXF ); /* Linear Acceleration */
            TgVEC_F32_04_1_C                    vLV_Unscaled = tgMH_MAD_F32_04_1( vScaled_Step_Size, vLA, psBY->m_vLV ); /* Uncapped Linear Velocity */
            TgVEC_F32_04_1                      vLV_LEN;
            TgVEC_F32_04_1_C                    vLV_NRM = tgMH_NORM_LEN_F32_04_1( &vLV_LEN, vLV_Unscaled ); /* NOTE: This may result in an invalid vector (near-zero). */
            TgVEC_F32_04_1_C                    vLV_LEN_CMP = tgMH_CMP_GT_F32_04_1( vLV_LEN, KTgPH_MAX_LIN_SPEED ); /* Determine if we have exceeded the maximum velocity. */
            TgVEC_F32_04_1_C                    vLV_LEN_MAX = tgMH_MIN_F32_04_1( vLV_LEN, KTgPH_MAX_LIN_SPEED ); /* Limit the maximum linear velocity. */
            TgVEC_F32_04_1_C                    vLV_Rescaled = tgMH_MUL_F32_04_1( vLV_LEN_MAX, vLV_NRM ); /* NOTE: This may be an invalid vector. */
            TgVEC_F32_04_1_C                    vLV = tgMH_SEL_F32_04_1( vLV_Unscaled, vLV_Rescaled, vLV_LEN_CMP ); /* Select the original vector (could be zero) or rescaled. */

            #pragma endregion

            #pragma region  Calculate the angular velocity of the body (and apply limits).

            TgVEC_F32_04_1_C                    vAA = tgMH_TX_F32_04_3( psBY->m_vXT, &psBY->m_mInverse_Inertia_Tensor ); /* Angular Acceleration */
            TgVEC_F32_04_1_C                    vAV_Unscaled = tgMH_MAD_F32_04_1( vScaled_Step_Size, vAA, psBY->m_vAV ); /* Uncapped Angular Velocity */
            TgVEC_F32_04_1                      vAV_LEN;
            TgVEC_F32_04_1_C                    vAV_NRM = tgMH_NORM_LEN_F32_04_1( &vAV_LEN, vAV_Unscaled ); /* NOTE: This may result in an invalid vector (near-zero). */
            TgVEC_F32_04_1_C                    vAV_LEN_CMP = tgMH_CMP_GT_F32_04_1( vAV_LEN, KTgPH_MAX_ANG_SPEED ); /* Determine if we have exceeded the maximum velocity. */
            TgVEC_F32_04_1_C                    vAV_LEN_MAX = tgMH_MIN_F32_04_1( vAV_LEN, KTgPH_MAX_ANG_SPEED ); /* Limit the maximum angular velocity. */
            TgVEC_F32_04_1_C                    vAV_Rescaled = tgMH_MUL_F32_04_1( vAV_LEN_MAX, vAV_NRM ); /* NOTE: This may be an invalid vector. */
            TgVEC_F32_04_1_C                    vAV = tgMH_SEL_F32_04_1( vAV_Unscaled, vAV_Rescaled, vAV_LEN_CMP ); /* Select the original vector (could be zero) or rescaled. */

            TgVEC_UN_F32_04_1_C                 uAV = { .m_vF32_04_1 = vAV };
            TgVEC_UN_F32_04_1_C                 uQR = { .m_vF32_04_1 = psBY->m_vRot_O2W };
            TgVEC_S_F32_04_1_C                  vQR = uQR.m_vS_F32_04_1;
            TgVEC_UN_F32_04_1_C                 uΔQ = { .m_vS_F32_04_1 = {
                                                    .x = 0.5F*(-uAV.m_vS_F32_04_1.x * vQR.x - uAV.m_vS_F32_04_1.y * vQR.y - uAV.m_vS_F32_04_1.z * vQR.z),
                                                    .y = 0.5F*( uAV.m_vS_F32_04_1.x * vQR.w + uAV.m_vS_F32_04_1.y * vQR.z - uAV.m_vS_F32_04_1.z * vQR.y),
                                                    .z = 0.5F*(-uAV.m_vS_F32_04_1.x * vQR.z + uAV.m_vS_F32_04_1.y * vQR.w + uAV.m_vS_F32_04_1.z * vQR.x),
                                                    .w = 0.5F*( uAV.m_vS_F32_04_1.x * vQR.y - uAV.m_vS_F32_04_1.y * vQR.x + uAV.m_vS_F32_04_1.z * vQR.w)
                                                } };
            TgVEC_F32_04_1_C                    vQ = tgMH_MAD_F32_04_1( uΔQ.m_vF32_04_1, vScaled_Step_Size, psBY->m_vRot_O2W );
            TgVEC_F32_04_1_C                    vQ_Normalized = tgMH_NORM_F32_04_1( vQ );


            #pragma endregion

        #if defined(TgBUILD_FEATURE__PHYSICS__HISTORY) // Used by the visualization system and debug output
            TgRSIZE                             uiHist_Index = TgSTD_ATOMIC(fetch_add)( &g_xnuiPH_History, 1 ) % KTgPH_MAX_HISTORY_BODY;

            g_vPH_History__Body_Pos_W[uiHist_Index] = psBY->m_vPos_O2W;
            g_vPH_History__Body_Rot_W[uiHist_Index] = psBY->m_vRot_O2W;
            g_tiPH_History__Body_ID[uiHist_Index] = psBY->m_tiBody;
        #endif

            /* Update the linear velocity and position of the body. */
            TgDIAG(vLV.m_aData[3] == 0.0F);
            psBY->m_vLV = vLV;
            psBY->m_vPos_Last_Valid_O2W = psBY->m_vPos_O2W;
            psBY->m_vPos_O2W = tgMH_MAD_F32_04_1( vScaled_Step_Size, vLV, psBY->m_vPos_O2W );
            psBY->m_vXF = tgMH_SET1_F32_04_1( 0.0F );

            /* Update the angular velocity and rotation of the body. */
            psBY->m_vAV = vAV;
            psBY->m_vRot_O2W = vQ_Normalized;
            psBY->m_vXT = tgMH_SET1_F32_04_1( 0.0F );

        #if defined(TgBUILD_DEBUG__PHYSICS__EXTENSIVE_DATA_CHECK) && TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__DIAG
            TgDIAG(((TgVEC_S_F32_04_1_CP)&psBY->m_vPos_O2W)->w == 1.0F);
            TgDIAG(((TgVEC_S_F32_04_1_CP)&psBY->m_vAV)->w == 0.0F);
            TgDIAG(((TgVEC_S_F32_04_1_CP)&psBY->m_vLV)->w == 0.0F);
            TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( psBY->m_vLV )));
            TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( psBY->m_vPos_O2W )));
            TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( psBY->m_vAV )));
            TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( psBY->m_vRot_O2W )));
        /*# defined(TgBUILD_DEBUG__PHYSICS__EXTENSIVE_DATA_CHECK) && TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__DIAG */
        #endif

            /* Update the final transforms, matrix rotation, and all connected Forms. */
            tgPH_Body_Update__WRITE( psBY, false );
        };
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Update_World__Init_Solver_Set --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPH_Update_World__Init_Solver_Set( STg2_PH_Solver__Set_PC psSolver_Set, TgRSIZE_C nuiBody_World, TgRSIZE_C nuiConstraint_World, TgRSIZE_AP pnuiConstraint )
{
    TgDIAG(nullptr != psSolver_Set);
    TgDIAG(nullptr != pnuiConstraint);

    tgMM_Set_U08_0x00( psSolver_Set, sizeof( STg2_PH_Solver__Set ) );

    psSolver_Set->m_apsBody = (STg2_PH_Body_PP)TgMALLOC_TEMP( sizeof( STg2_PH_Body_P ) * nuiBody_World );
    TgCRITICAL_MSGF( nullptr != psSolver_Set->m_apsBody, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

    if (nuiConstraint_World > 0)
    {
        ETgPH_CONSTRAINT                    enConstraint;

        for (enConstraint = ETgPH_CONSTRAINT__UNKNOWN; enConstraint < ETgPH_CONSTRAINT__MAX; enConstraint = (ETgPH_CONSTRAINT)((TgSINT_E32)enConstraint + 1))
        {
            TgRSIZE_C                           nuiConstraint = TgSTD_ATOMIC(load_explicit)( pnuiConstraint + enConstraint, TgSTD_MEMORY_ORDER(relaxed) );

            if (0 == nuiConstraint)
                continue;

            psSolver_Set->m_apsConstraint[enConstraint] = (STg2_PH_Constraint_PP)TgMALLOC_TEMP( sizeof( STg2_PH_Constraint_P ) * nuiConstraint );
            TgCRITICAL_MSGF( nullptr != psSolver_Set->m_apsConstraint[enConstraint], STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
            tgMM_Set_U08_0x00( psSolver_Set->m_apsConstraint[enConstraint], sizeof( STg2_PH_Constraint_P ) * nuiConstraint );

            psSolver_Set->m_apuiDoF[enConstraint] = (TgRSIZE_P)TgMALLOC_TEMP( sizeof( TgRSIZE ) * nuiConstraint );
            TgCRITICAL_MSGF( nullptr != psSolver_Set->m_apuiDoF[enConstraint], STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

            if ((ETgPH_CONSTRAINT__CONTACT == enConstraint) && nuiConstraint)
            {
                psSolver_Set->m_apsInvalid_Contact_Constraint = (STg2_PH_Constraint_PP)TgMALLOC_TEMP( sizeof( STg2_PH_Constraint_P ) * nuiConstraint );
                TgCRITICAL_MSGF( nullptr != psSolver_Set->m_apsInvalid_Contact_Constraint, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
                tgMM_Set_U08_0x00( psSolver_Set->m_apsInvalid_Contact_Constraint, sizeof( STg2_PH_Constraint_P ) * nuiConstraint );
            };
        };

        psSolver_Set->m_avInverse_Mass_Inertia_Tensor = (TgVEC_F32_04_1_P)TgMALLOC_TEMP( sizeof( TgVEC_F32_04_1 ) * 8 * nuiConstraint_World );
        TgCRITICAL_MSGF( nullptr != psSolver_Set->m_avInverse_Mass_Inertia_Tensor, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

        psSolver_Set->m_auiJacobian_Index = (TgRSIZE_P)TgMALLOC_TEMP( sizeof( TgRSIZE ) * 2 * nuiConstraint_World );
        TgCRITICAL_MSGF( nullptr != psSolver_Set->m_auiJacobian_Index, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

        psSolver_Set->m_anuiDoF = (TgRSIZE_P)TgMALLOC_TEMP( sizeof( TgRSIZE ) * nuiConstraint_World );
        TgCRITICAL_MSGF( nullptr != psSolver_Set->m_anuiDoF, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

        psSolver_Set->m_avResult = (TgVEC_F32_04_1_P)TgMALLOC_TEMP( sizeof( TgVEC_F32_04_1 ) * 2 * nuiBody_World );
        TgCRITICAL_MSGF( nullptr != psSolver_Set->m_avResult, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
        tgMM_Set_U08_0x00( psSolver_Set->m_avResult, sizeof( TgVEC_F32_04_1 ) * 2 * nuiBody_World );
    };
}
