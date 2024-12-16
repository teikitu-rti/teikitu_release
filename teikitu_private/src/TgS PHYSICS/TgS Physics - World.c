/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - World.c
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
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Responsible for taking a set of Bodies and collecting forces, moments and torques that will be applied during the solution step. These are the primary inputs to the 
           prediction for the collision step that takes place next. This is also the primary way that actors outside of the Physics simulation can impact it. There are user
           functions that be registered per body to allow a user to calculate and set their own forces, moments and torques that will be used later by the simulation. Any
           complicated modelling should be done this way (for example: tire friction, simulation of an engine, etc.). @return Result Code.
    @param [in] ARG0 Pointer to a job data structure. */
static TgRESULT
tgPH_Update_World__Job__Simulate_Batch(
    STg2_Job_CPC ARG0 );

/** @brief Responsible for the setup and queuing of collide batch jobs. @return Result Code.
    @param [in] ARG0 Pointer to a job data structure. */
static TgRESULT
tgPH_Update_World__Job__Collision(
    STg2_Job_CPC ARG0 );

/** @brief Responsible for taking a set of Forms and determining any collisions that have taken place during the World step. This is done assuming that the Forms will continue
           moving along the same path as they are currently configured. Forms can be configured to engage or ignore classes of collision objects. The Forms will be tested against
           each other, and against the World collision representation. During this pass anti-tunneling measures are taken to mitigate tunneling issues.  @return Result Code.
    @param [in] ARG0 Pointer to a job data structure. */
static TgRESULT
tgPH_Update_World__Job__Collide_Simple_Batch(
    STg2_Job_CPC ARG0 );

/** @brief Master function that iterates through all active bodies (and constraints) to create sets that are self-contained. Once a set is completed, then a job is created
           to run the solver and updates for the entities in the set. @return Result Code.
    @note  Future thoughts: this is the primary bottle neck preventing the system. There may be an advantage to recording the sets that were created in Frame N as the order
           of the bodies that will be processed for Frame N+1. Likely to have some minor optimization benefit due to frame to frame consistency. In the same way as well, 
           the order could be further optimized based on an objective to maximize the number of sets (for CPUs with a large number of cores it would be more critical to
           maximize concurrency) or for duration of execution for a small number of jobs (efficiency).
           An interesting note is that with the assumption of frame to frame coherence, and if there is available CPU resources, then it would be possible to have multiple
           jobs executing through the body list at different points along the array. The issue would be when there is an overlap, one of the threads would have to throw
           away work (which with excess resources is viable).
    @param [in] ARG0 Pointer to a job data structure. */
static TgRESULT
tgPH_Update_World__Job__Build_Sets(
    STg2_Job_CPC ARG0 );

/** @brief Responsible for releasing the remaining dynamic memory allocations created during the update process. Executes the command buffer which contains all of the deferred
           commands (function calls) from other threads. @return Result Code.
    @param [in] ARG0 Pointer to a job data structure. */
static TgRESULT
tgPH_Update_World__Job__Finish(
    STg2_Job_CPC ARG0 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Scene_Enable -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgPH_WORLD_ID tgPH_World_Query_World_Id( ETgPH_WORLD_C enWorld )
{
    if ((ETgPH_WORLD__BEGIN <= enWorld) && (enWorld <= ETgPH_WORLD__END))
    {
        return g_asPH_World[enWorld].m_tiWorld;
    }
    else
    {
        return KTgPH_WORLD_ID__INVALID;
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Macro Functions                                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(World,WORLD,Simulation_Min_Batch_Size,TgRSIZE,m_uiSimulate_Min_Batch_Size)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(World,WORLD,Collision_Min_Batch_Size,TgRSIZE,m_uiCollide_Min_Batch_Size)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(World,WORLD,Minimum_Bodies_Per_Solver_Job,TgRSIZE,m_uiSolver_Min_Body_Per_Job)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(World,WORLD,Minimum_DoF_Per_Solver_Job,TgRSIZE,m_uiSolver_Min_DoF_Per_Job)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(World,WORLD,Solver_Iterations,TgRSIZE,m_nuiSolver_Iterations)

PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(World,WORLD,Fixed_Time_Step,TgVEC_F32_04_1,m_vStep_Size)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(World,WORLD,Force_Field,TgVEC_F32_04_1,m_vForce_Field)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(World,WORLD,Threshold_Depth,TgVEC_F32_04_1,m_vThreshold__Depth)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(World,WORLD,Threshold_LV,TgVEC_F32_04_1,m_vThreshold__LV_LSQ)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(World,WORLD,Threshold_AV,TgVEC_F32_04_1,m_vThreshold__AV_LSQ)

PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(World,WORLD,Pause_State,TgBOOL,m_uiPaused)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(World,WORLD,Single_Step,TgBOOL,m_uiSingle_Step)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(World,WORLD,Simulation_Enable,TgBOOL,m_uiSimulate)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(World,WORLD,Collision_Enable,TgBOOL,m_uiCollide)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(World,WORLD,Collision_Simple_Override,TgBOOL,m_uiCollision_Simple)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_World_Init_Internal ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_World_Init_Internal( STg2_PH_World_P psWorld )
{
    TgPARAM_CHECK(nullptr != psWorld)

    tgPH_WORLD_ID_Init( &psWorld->m_tiWorld, (TgUINT_E32)(psWorld - g_asPH_World), 0, 0 );

    /* Solver Configuration */
    psWorld->m_uiSimulate_Min_Batch_Size = 50; // PIOMA
    psWorld->m_uiCollide_Min_Batch_Size = 3; // PIOMA
    psWorld->m_uiSolver_Min_Body_Per_Job = 50; // PIOMA
    psWorld->m_uiSolver_Min_DoF_Per_Job = 150; // PIOMA
    psWorld->m_nuiSolver_Iterations = 10; // PIOMA

#if defined(TgBUILD_FEATURE__PHYSICS__CFM)
    psWorld->m_fCFM = 0.0001F; // PIOMA - TODO FILL THIS OUT
#endif
    psWorld->m_fStep_Size_Seconds = 1.0F / 240.0F;
    psWorld->m_pfnCollision_Update = tgPH_Update_World__Collide__Partition_Manager_IMM;
    psWorld->m_tiPA_Graph = tgPA_Graph_PNS_Init();

    psWorld->m_vThreshold__Depth = tgMH_SET1_F32_04_1( 0.001F ); // PIOMA
    psWorld->m_vThreshold__LV_LSQ = tgMH_Init_Vector_ELEM_F32_04_1( 0.001F, 0.001F, 0.001F ); // PIOMA
    psWorld->m_vThreshold__AV_LSQ = tgMH_Init_Vector_ELEM_F32_04_1( 0.001F, 0.001F, 0.001F ); // PIOMA
    psWorld->m_vConstraint_Error_Correction_Rate = tgMH_SET1_F32_04_1( 0.25F ); /* CECR */

    /* World Configuration */
    psWorld->m_vForce_Field = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, -9.81F, 0.0F );
    psWorld->m_vStep_Size = tgMH_SET1_F32_04_1( psWorld->m_fStep_Size_Seconds );

    /* Run Time Configuration */
    psWorld->m_uiPaused = 0;
    psWorld->m_uiSingle_Step = 0;
    psWorld->m_uiSimulate = 1;
    psWorld->m_uiCollide = 1;

    /* Serialization */
    psWorld->m_psScene = nullptr;

#if defined(TgBUILD_DEBUG__PHYSICS)
    tgPH_World_Set_User_FCN__Constraint_Contact_Init_Complete( nullptr, psWorld->m_tiWorld, tgPH_Constraint_Contact__CNPrintF_IMM );
/*# defined(TgBUILD_DEBUG__PHYSICS) */
#endif

    return KTgS_OK;
}


/* ---- tgPH_World_Reset_Internal ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_World_Reset_Internal( STg2_PH_World_P psWorld )
{
    tgPA_Graph_PNS_Free( psWorld->m_tiPA_Graph );
    return KTgE_FAIL;
}


/* ---- tgPH_Update_World__Init_Jobs --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Init_Jobs( TgVOID )
{
    TgRSIZE                             uiWorld_Index;

    tgMM_Set_U08_0x00( &g_asPH__Job__Update_World__Simulate_Batch, sizeof( g_asPH__Job__Update_World__Simulate_Batch ) );
    tgMM_Set_U08_0x00( &g_asPH__Job__Update_World__Collision, sizeof( g_asPH__Job__Update_World__Collision ) );
    tgMM_Set_U08_0x00( &g_asPH__Job__Update_World__Build_Sets, sizeof( g_asPH__Job__Update_World__Build_Sets ) );
    tgMM_Set_U08_0x00( &g_asPH__Job__Update_World__Solve_Sets, sizeof( g_asPH__Job__Update_World__Solve_Sets ) );
    tgMM_Set_U08_0x00( &g_asPH__Job__Update_World__Finish, sizeof( g_asPH__Job__Update_World__Finish ) );

    for (uiWorld_Index = 0; uiWorld_Index < ETgPH_MAX_WORLD; ++uiWorld_Index)
    {
        TgSTD_ATOMIC(store)( g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH + uiWorld_Index, 0u );
        TgSTD_ATOMIC(store)( g_axuiPH_FENCE__UPDATE_WORLD__COLLISION + uiWorld_Index, 0u );
        TgSTD_ATOMIC(store)( g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS + uiWorld_Index, 0u );
        TgSTD_ATOMIC(store)( g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS + uiWorld_Index, 0u );
        TgSTD_ATOMIC(store)( g_axuiPH_FENCE__UPDATE_WORLD__FINISH + uiWorld_Index, 0u );

        g_asPH__Job__Update_World__Simulate_Batch[uiWorld_Index].m_pfnExecute = tgPH_Update_World__Job__Simulate_Batch;
        g_asPH__Job__Update_World__Simulate_Batch[uiWorld_Index].m_pxuiTrigger = g_axuiPH_FENCE__UPDATE_WORLD__FINISH + uiWorld_Index;

        g_asPH__Job__Update_World__Collision[uiWorld_Index].m_pfnExecute = tgPH_Update_World__Job__Collision;
        g_asPH__Job__Update_World__Collision[uiWorld_Index].m_pxuiTrigger = g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH + uiWorld_Index;

        g_asPH__Job__Update_World__Build_Sets[uiWorld_Index].m_pfnExecute = tgPH_Update_World__Job__Build_Sets;
        g_asPH__Job__Update_World__Build_Sets[uiWorld_Index].m_pxuiTrigger = g_axuiPH_FENCE__UPDATE_WORLD__COLLISION + uiWorld_Index;

        g_asPH__Job__Update_World__Solve_Sets[uiWorld_Index].m_pfnExecute = tgPH_Update_World__Job__Solve_Sets;

        g_asPH__Job__Update_World__Finish[uiWorld_Index].m_pfnExecute = tgPH_Update_World__Job__Finish;
        g_asPH__Job__Update_World__Finish[uiWorld_Index].m_pxuiTrigger = g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS + uiWorld_Index;
    }
}


/* ---- tgPH_Update_World -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Pre-Conditions
    1. End of previous Simulation Frame (both server and client).
    2. Execute deferred commands from game thread (on the client).
   Execution
    1. Accumulate all known forces and moments (execute user specific force and moment generators) to create a predicted next step position and rotation.
    2. Run collision detection on all forms to prevent tunnelling and to create contact constraints.
        i. A collision scene graph should be used to optimize the O(n^2) performance.
        ii. Tunnelling corrections are modelled as an impulse on the body and added as an external force and moment.
    3. Construct all of the sets (self contained closed sets)
    4. Run the solver to determine the resulting final forces and moments.
    5. Construct the final next step position and rotation. */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Update_World( TgPH_WORLD_ID_C tiWorld )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );
    TgRSIZE                             uiFence;

    if ((nullptr == psWorld) || (0 == psWorld->m_uiSimulate_Min_Batch_Size))
    {
        return (KTgE_FAIL);
    };

    /* Last ditch attempt to prevent the system from overlapping iteself. */
    uiFence = 0;
    while (!TgSTD_ATOMIC(compare_exchange_strong_explicit)( g_axuiPH_FENCE__UPDATE_WORLD + tiWorld.m_uiI, &uiFence, 1, TgSTD_MEMORY_ORDER(acq_rel), TgSTD_MEMORY_ORDER(acquire) ))
    {
        tgTR_Pause();
        uiFence = 0;
    };

    {
        TgRSIZE_C                           nuiForm_World = TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Form_Total__Used + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) );
        TgRSIZE_C                           nuiBody_World = TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Body_Total__Used + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) );

        TgBOOL                              bIs_Paused;
        TgBOOL                              bRunSimulation;
        TgBOOL                              bRunCollision;

        /* Check the pause state for the world. */
        bIs_Paused  = 0 != psWorld->m_uiPaused;
        bIs_Paused &= 0 == psWorld->m_uiSingle_Step;
        bIs_Paused |= tgPH_Is_Module_Paused();

        /* Check for the conditions to run the simulation. */
        bRunSimulation = !bIs_Paused && (0 != psWorld->m_uiSimulate) && (psWorld->m_uiSimulate_Min_Batch_Size > 0) && (nuiBody_World > 0);

        /* Check for the conditions to run collision. */
        bRunCollision = !bIs_Paused && (0 != psWorld->m_uiCollide) && (psWorld->m_uiCollide_Min_Batch_Size > 0) && (nuiForm_World > 0);

        /* Allocate memory for Body Predicted Motion. */
        g_asPH_Update__Simulation[tiWorld.m_uiI].m_avBY_Pos_O2W = (TgVEC_F32_04_1_P)TgMALLOC_POOL( sizeof(TgVEC_F32_04_1) * nuiBody_World );
        g_asPH_Update__Simulation[tiWorld.m_uiI].m_avRHS_LA = (TgVEC_F32_04_1_P)TgMALLOC_POOL( sizeof(TgVEC_F32_04_1) * 2 * nuiBody_World );
        g_asPH_Update__Simulation[tiWorld.m_uiI].m_amFM_Final_O2W = (TgVEC_F32_04_3_P)TgMALLOC_POOL( sizeof(TgVEC_F32_04_3) * nuiForm_World );
        g_asPH_Update__Simulation[tiWorld.m_uiI].m_avFM_Pos_O2W = (TgVEC_F32_04_1_P)TgMALLOC_POOL( sizeof(TgVEC_F32_04_1) * nuiForm_World );
        g_asPH_Update__Simulation[tiWorld.m_uiI].m_asFM_BA_W = (TgBOXAA_F32_04_P)TgMALLOC_POOL( sizeof(TgBOXAA_F32_04) * nuiForm_World );

        /* Simulation Pass: Determine the forces and moments assuming no constraints */
        if (bRunSimulation || bRunCollision)
        {
            STg2_Job_PC                         psJob = g_asPH__Job__Update_World__Simulate_Batch + tiWorld.m_uiI;
            TgRSIZE                             uiSimulate_Min_Batch_Size;
            TgRSIZE                             uiBody_Index;

            /* Calculate the number of jobs (batches) to create, and the number of bodies per job (batch). */
            uiSimulate_Min_Batch_Size = psWorld->m_uiSimulate_Min_Batch_Size;
            if (((nuiBody_World + uiSimulate_Min_Batch_Size - 1) / uiSimulate_Min_Batch_Size) >= KTgPH_MAX_SIMULATION_JOB)
            {
                uiSimulate_Min_Batch_Size = (nuiBody_World + KTgPH_MAX_SIMULATION_JOB - 1) / KTgPH_MAX_SIMULATION_JOB;
            };

            /* Set the fence to be the total number of bodies in the world. */
            TgVERIFY(0 == TgSTD_ATOMIC(load_explicit)( g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) ));
            TgSTD_ATOMIC(store)( g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH + tiWorld.m_uiI, nuiBody_World );

            /* Create all of the jobs necessary to batch the simulation calls for all bodies. */
            for (uiBody_Index = 0; uiBody_Index < nuiBody_World; uiBody_Index += uiSimulate_Min_Batch_Size)
            {
                union { STg2_PH_Job__Update_World__Simulate_Data_P psSimulate_Data; TgUINT_E08_P pui; } const sJob_Data = { .pui  = psJob->m_auiData };
                TgERROR(sJob_Data.psSimulate_Data);

                sJob_Data.psSimulate_Data->m_tiWorld = tiWorld;
                sJob_Data.psSimulate_Data->m_uiBody_Index_Begin = uiBody_Index;
                sJob_Data.psSimulate_Data->m_uiBody_Index_End = tgCM_MIN_UMAX( uiBody_Index + uiSimulate_Min_Batch_Size, nuiBody_World );

                if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, psJob )))
                {
                    TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
                    tgPH_Update_World__Job__Simulate_Batch( psJob );
                };
            };
        };

        TgDIAG(tgCM_UT_LF__ST__Is_Empty( &g_asPH_Update__Constraint_IMM[tiWorld.m_uiI].m_sStack ));

        /* Collision Pass: Check for collisions, prevent tunnelling and create contact constraints. */
        if (bRunCollision)
        {
            STg2_Job_PC                         psJob = g_asPH__Job__Update_World__Collision + tiWorld.m_uiI;
            union { STg2_PH_Job__Update_World__Collide_Data_P psCollide_Data; TgUINT_E08_P pui; } const sJob_Data = { .pui  = psJob->m_auiData };

            TgDIAG(0 == TgSTD_ATOMIC(load)( g_aaxnuiPH_Constraint_Total__Used_By_Type[tiWorld.m_uiI] + ETgPH_CONSTRAINT__CONTACT));
            TgDIAG(sJob_Data.psCollide_Data);

            /* Set the fence to be the total number of forms in the world. */
            TgVERIFY(0 == TgSTD_ATOMIC(load_explicit)( g_axuiPH_FENCE__UPDATE_WORLD__COLLISION + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) ));
            TgSTD_ATOMIC(store)( g_axuiPH_FENCE__UPDATE_WORLD__COLLISION + tiWorld.m_uiI, 1 );

        #if defined(TgBUILD_DEBUG__PHYSICS)
            g_nuiPH_Debug__Contact = 0;
        /*# defined(TgBUILD_DEBUG__PHYSICS) */
        #endif

            /* Create all of the jobs necessary to batch the collide calls for all forms. */

            psJob->m_pfnExecute = tgPH_Update_World__Job__Collision;
            sJob_Data.psCollide_Data->m_tiWorld = tiWorld;
            sJob_Data.psCollide_Data->m_uiForm_Index_Begin = 0;
            sJob_Data.psCollide_Data->m_uiForm_Index_End = nuiForm_World;

            if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, psJob )))
            {
                TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
                while (0 != TgSTD_ATOMIC(load_explicit)( psJob->m_pxuiTrigger, TgSTD_MEMORY_ORDER(relaxed) ))
                {
                    tgTR_Pause();
                };
                psJob->m_pfnExecute( psJob );
            };
        };

        /* Build the Sets, Solve, and then Update the Bodies. */
        if (bRunSimulation)
        {
            STg2_Job_PC                         psJob = g_asPH__Job__Update_World__Build_Sets + tiWorld.m_uiI;

            union { STg2_PH_Job__Update_World__Build_Set_Data_P psBuild_Set_Data; TgUINT_E08_P pui; } const sJob_Data = { .pui  = psJob->m_auiData };

            /* Set the fence to be equivalent to job count. */
            TgVERIFY(0 == TgSTD_ATOMIC(load_explicit)( g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) ));
            TgSTD_ATOMIC(store)( g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS + tiWorld.m_uiI, 1 );

            sJob_Data.psBuild_Set_Data->m_tiWorld = tiWorld;
            psJob->m_pxuiTrigger = (bRunCollision ? g_axuiPH_FENCE__UPDATE_WORLD__COLLISION : g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH) + tiWorld.m_uiI;
            if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, psJob )))
            {
                TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
                while (0 != TgSTD_ATOMIC(load_explicit)( psJob->m_pxuiTrigger, TgSTD_MEMORY_ORDER(relaxed) ))
                {
                    tgTR_Pause();
                };
                tgPH_Update_World__Job__Build_Sets( psJob );
            };
        }
        else
        {
            STg2_Job_PC psFinish_Job = g_asPH__Job__Update_World__Finish + tiWorld.m_uiI;
            union { STg2_PH_Job__Update_World__Build_Set_Data_P psBuild_Sets_Data; TgUINT_E08_P pui; } const psJob_Finish_Data = { .pui  = psFinish_Job->m_auiData };
            TgERROR(psJob_Finish_Data.psBuild_Sets_Data);

            psJob_Finish_Data.psBuild_Sets_Data->m_tiWorld = tiWorld;
            psJob_Finish_Data.psBuild_Sets_Data->m_bCollision = bRunCollision;
            psJob_Finish_Data.psBuild_Sets_Data->m_bSimulation = bRunSimulation;

            while (0 != TgSTD_ATOMIC(load_explicit)( g_axuiPH_FENCE__UPDATE_WORLD__COLLISION + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) ))
            {
                tgTR_Pause();
            };

            tgPH_Update_World__Job__Finish( psFinish_Job );
        };
    };

    return (KTgS_OK);
}


/* ---- tgPH_Update_World__Job__Solve_Sets --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Update_World__Job__Solve_Sets( STg2_Job_CPC psJob )
{
    union { STg2_PH_Job__Update_World__Solve_Set_Data_CP psSolve_Sets_Data; TgUINT_E08_CP pui; } const sJob_Data = { .pui  = psJob->m_auiData };
    STg2_PH_Solver__Set                 sSolver_Set = sJob_Data.psSolve_Sets_Data->m_sSolver_Set;

    TgPARAM_CHECK(sJob_Data.psSolve_Sets_Data);
    TgPARAM_CHECK (nullptr != tgPH_World_Get_World_From_ID( sJob_Data.psSolve_Sets_Data->m_tiWorld ));

    PROFILE_ARRAY_START( sJob_Data.psSolve_Sets_Data->m_tiWorld.m_uiI, PH_SOLVE_SETS, tgPH_Update_World__Job__Solve_Sets ); /* Profile Tag for this particular world. */
    PROFILE_START( PH_SOLVE_SETS_TOTAL, tgPH_Update_World__Job__Solve_Sets ); /* Profile Tag for all of the batches. */

    if (0 != sSolver_Set.m_nuiDoF)
    {
        tgPH_Update_World__Define_Problem_And_Solve( sJob_Data.psSolve_Sets_Data->m_tiWorld, &sSolver_Set );
    };
    tgPH_Update_World__Update_Bodies_IMM( sJob_Data.psSolve_Sets_Data->m_tiWorld, &sSolver_Set );
    tgPH_Constraint_Contact__Free_All_IMM( &sSolver_Set ); /* Free all the constraints there were created this step in this World. */
    tgPH_Update_World__Free_Solver_Set( &sSolver_Set ); /* Need to free the memory allocated for the solver set. */

    PROFILE_STOP( PH_SOLVE_SETS_TOTAL, tgPH_Update_World__Job__Solve_Sets );
    PROFILE_ARRAY_STOP( sJob_Data.psSolve_Sets_Data->m_tiWorld.m_uiI, PH_SOLVE_SETS, tgPH_Update_World__Job__Solve_Sets );

    TgSTD_ATOMIC(fetch_sub_explicit)( g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS + sJob_Data.psSolve_Sets_Data->m_tiWorld.m_uiI, 1, TgSTD_MEMORY_ORDER(seq_cst) );

    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Update_World__Job__Simulate_Batch ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgPH_Update_World__Job__Simulate_Batch( STg2_Job_CPC psJob )
{
    union { STg2_PH_Job__Update_World__Simulate_Data_CP psSimulate_Data; TgUINT_E08_CP pui; } const sJob_Data = { .pui  = psJob->m_auiData };
    STg2_PH_Job__Update_World__Simulate_Data_CPC psSimulate_Data = sJob_Data.psSimulate_Data;

    TgRSIZE                             nuiObject_Complete;

    TgPARAM_CHECK(sJob_Data.psSimulate_Data);
    TgPARAM_CHECK(nullptr != tgPH_World_Get_World_From_ID( sJob_Data.psSimulate_Data->m_tiWorld ));

    PROFILE_ARRAY_START( sJob_Data.psSimulate_Data->m_tiWorld.m_uiI, PH_SIMULATE_BATCH, tgPH_Update_World__Job__Simulate_Batch ); /* Profile Tag for this particular world. */
    PROFILE_START( PH_SIMULATE_BATCH_TOTAL, tgPH_Update_World__Job__Simulate_Batch ); /* Profile Tag for all of the batches. */

    tgPH_Update_World__Simulate_Batch_IMM( psSimulate_Data->m_tiWorld, psSimulate_Data->m_uiBody_Index_Begin, psSimulate_Data->m_uiBody_Index_End );

    PROFILE_STOP( PH_SIMULATE_BATCH_TOTAL, tgPH_Update_World__Job__Simulate_Batch );
    PROFILE_ARRAY_STOP( sJob_Data.psSimulate_Data->m_tiWorld.m_uiI, PH_SIMULATE_BATCH, tgPH_Update_World__Job__Simulate_Batch );

    nuiObject_Complete = sJob_Data.psSimulate_Data->m_uiBody_Index_End - sJob_Data.psSimulate_Data->m_uiBody_Index_Begin;
    TgSTD_ATOMIC(fetch_sub_explicit)( g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH + sJob_Data.psSimulate_Data->m_tiWorld.m_uiI, nuiObject_Complete, TgSTD_MEMORY_ORDER(seq_cst) );

    return (KTgS_OK);
}


/* ---- tgPH_Update_World__Job__Collision ---------------------------------------------------------------------------------------------------------------------------------------- */
/* SYNC: READS Forms, Bodies, Constraints (in Child Functions)                                                                                                                     */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgPH_Update_World__Job__Collision( STg2_Job_CPC psJob )
{
    union { STg2_PH_Job__Update_World__Collide_Data_CP psCollide_Data; TgUINT_E08_CP pui; } const sJob = { .pui  = psJob->m_auiData };
    TgRSIZE_C                           nuiForm_World = sJob.psCollide_Data->m_uiForm_Index_End;
    TgPH_WORLD_ID_C                     tiWorld = sJob.psCollide_Data->m_tiWorld;
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    TgPARAM_CHECK(sJob.psCollide_Data);
    TgDIAG(sJob.psCollide_Data);
    TgPARAM_CHECK (nullptr != tgPH_World_Get_World_From_ID( tiWorld ));

    PROFILE_ARRAY_START( tiWorld.m_uiI, PH_COLLISION_WORLD, tgPH_Update_World__Job__Collision );
    PROFILE_START( PH_COLLISION_WORLD_TOTAL, tgPH_Update_World__Job__Collision );

    TgDIAG(0 == TgSTD_ATOMIC(load)( g_aaxnuiPH_Constraint_Total__Used_By_Type[tiWorld.m_uiI] + ETgPH_CONSTRAINT__CONTACT));

#if defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS
    TgSTD_ATOMIC(store_explicit)( &g_xnuiFM_Callback, 0, TgSTD_MEMORY_ORDER(relaxed) );
/*# defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS */
#endif

    /* Check to see if we are using the Simple Collision processor. */
    if (nullptr == psWorld->m_pfnCollision_Update || KTgID__INVALID_VALUE == psWorld->m_tiPA_Graph.m_uiKI || psWorld->m_uiCollision_Simple)
    {
        STg2_Job_PC                         psJob_Batch = g_asPH__Job__Update_World__Collision + tiWorld.m_uiI;
        union { STg2_PH_Job__Update_World__Collide_Data_P psCollide_Data; TgUINT_E08_P pui; } const sJob_Batch = { .pui  = psJob_Batch->m_auiData };

        TgRSIZE                             uiCollide_Min_Batch_Size;
        TgRSIZE                             uiForm_Index;

        /* Calculate the number of jobs (batches) to create, and the number of bodies per job (batch). */
        uiCollide_Min_Batch_Size = psWorld->m_uiCollide_Min_Batch_Size;
        if (((nuiForm_World + uiCollide_Min_Batch_Size - 1) / uiCollide_Min_Batch_Size) >= KTgPH_MAX_COLLIDE_JOB)
        {
            uiCollide_Min_Batch_Size = (nuiForm_World + KTgPH_MAX_COLLIDE_JOB - 1) / KTgPH_MAX_COLLIDE_JOB;
        };

        /* Set the fence to be the total number of forms in the world. */
        TgVERIFY(1 == TgSTD_ATOMIC(load_explicit)( g_axuiPH_FENCE__UPDATE_WORLD__COLLISION + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) ));
        TgSTD_ATOMIC(fetch_add)( g_axuiPH_FENCE__UPDATE_WORLD__COLLISION + tiWorld.m_uiI, nuiForm_World );

        /* Create all of the jobs necessary to batch the collide calls for all forms. */
        for (uiForm_Index = 0; uiForm_Index < nuiForm_World; uiForm_Index += uiCollide_Min_Batch_Size)
        {
            psJob_Batch->m_pfnExecute = tgPH_Update_World__Job__Collide_Simple_Batch;
            sJob_Batch.psCollide_Data->m_tiWorld = tiWorld;
            sJob_Batch.psCollide_Data->m_uiForm_Index_Begin = uiForm_Index;
            sJob_Batch.psCollide_Data->m_uiForm_Index_End = tgCM_MIN_UMAX( uiForm_Index + uiCollide_Min_Batch_Size, nuiForm_World );

            if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, psJob_Batch )))
            {
                TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
                while (0 != TgSTD_ATOMIC(load_explicit)( psJob_Batch->m_pxuiTrigger, TgSTD_MEMORY_ORDER(relaxed) ))
                {
                    tgTR_Pause();
                };
                psJob_Batch->m_pfnExecute( psJob_Batch );
            };
        };

        PROFILE_STOP( PH_COLLISION_WORLD_TOTAL, tgPH_Update_World__Job__Collision );
        PROFILE_ARRAY_STOP( tiWorld.m_uiI, PH_COLLISION_WORLD, tgPH_Update_World__Job__Collision );
    }
    else
    {
        PROFILE_STOP( PH_COLLISION_WORLD_TOTAL, tgPH_Update_World__Job__Collision );
        PROFILE_ARRAY_STOP( tiWorld.m_uiI, PH_COLLISION_WORLD, tgPH_Update_World__Job__Collision );

        /* We are using a Partition Manager Graph to contain the Collision Space. */
        psWorld->m_pfnCollision_Update( tiWorld );
    };

    TgSTD_ATOMIC(fetch_sub_explicit)( g_axuiPH_FENCE__UPDATE_WORLD__COLLISION + tiWorld.m_uiI, 1, TgSTD_MEMORY_ORDER(seq_cst) );

    return (KTgS_OK);
}


/* ---- tgPH_Update_World__Job__Collide_Simple_Batch ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgPH_Update_World__Job__Collide_Simple_Batch( STg2_Job_CPC psJob )
{
    union { STg2_PH_Job__Update_World__Collide_Data_CP psCollide_Data; TgUINT_E08_CP pui; } const sJob_Data = { .pui  = psJob->m_auiData };
    TgPH_WORLD_ID_C                     tiWorld = sJob_Data.psCollide_Data->m_tiWorld;
    TgRSIZE                             nuiObject_Complete;

    TgPARAM_CHECK(sJob_Data.psCollide_Data);
    TgPARAM_CHECK (nullptr != tgPH_World_Get_World_From_ID( tiWorld ));

    PROFILE_ARRAY_START( tiWorld.m_uiI, PH_COLLISION_CONTACT_PAIR_GENEARTION, tgPH_Update_World__Job__Collide_Simple_Batch );
    PROFILE_START( PH_COLLISION_CONTACT_PAIR_GENEARTION_TOTAL, tgPH_Update_World__Job__Collide_Simple_Batch );

    tgPH_Update_World__Collide__Simple_IMM( tiWorld, sJob_Data.psCollide_Data->m_uiForm_Index_Begin, sJob_Data.psCollide_Data->m_uiForm_Index_End );

    PROFILE_STOP( PH_COLLISION_CONTACT_PAIR_GENEARTION_TOTAL, tgPH_Update_World__Job__Collide_Simple_Batch );
    PROFILE_ARRAY_STOP( tiWorld.m_uiI, PH_COLLISION_CONTACT_PAIR_GENEARTION, tgPH_Update_World__Job__Collide_Simple_Batch );

    nuiObject_Complete = sJob_Data.psCollide_Data->m_uiForm_Index_End - sJob_Data.psCollide_Data->m_uiForm_Index_Begin;
    TgSTD_ATOMIC(fetch_sub_explicit)( g_axuiPH_FENCE__UPDATE_WORLD__COLLISION + tiWorld.m_uiI, nuiObject_Complete, TgSTD_MEMORY_ORDER(seq_cst) );

    return (KTgS_OK);
}


/* ---- tgPH_Update_World__Job__Build_Sets --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgPH_Update_World__Job__Build_Sets( STg2_Job_CPC psJob )
{
    union { STg2_PH_Job__Update_World__Build_Set_Data_CP psBuild_Sets_Data; TgUINT_E08_CP pui; } const sJob_Data = { .pui  = psJob->m_auiData };
    TgPH_WORLD_ID_C                     tiWorld = sJob_Data.psBuild_Sets_Data->m_tiWorld;
    STg2_Job_PC                         psFinish_Job = g_asPH__Job__Update_World__Finish + tiWorld.m_uiI;
    union { STg2_PH_Job__Update_World__Build_Set_Data_P psBuild_Sets_Data; TgUINT_E08_P pui; } const psJob_Finish_Data = { .pui  = psFinish_Job->m_auiData };

    TgPARAM_CHECK(sJob_Data.psBuild_Sets_Data);
    TgPARAM_CHECK(psJob_Finish_Data.psBuild_Sets_Data);
    TgPARAM_CHECK (nullptr != tgPH_World_Get_World_From_ID( tiWorld ));
    TgPARAM_CHECK (TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Body_Total__Used + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) ) > 0);

    PROFILE_ARRAY_START( tiWorld.m_uiI, PH_BUILD_SETS, tgPH_Update_World__Job__Build_Sets );
    PROFILE_START( PH_BUILD_SETS_TOTAL, tgPH_Update_World__Job__Build_Sets );

    tgPH_Constraint__Bind_IMM( tiWorld );
    tgPH_Update_World__Build_Sets( tiWorld );

    PROFILE_STOP( PH_BUILD_SETS_TOTAL, tgPH_Update_World__Job__Build_Sets );
    PROFILE_ARRAY_STOP( tiWorld.m_uiI, PH_BUILD_SETS, tgPH_Update_World__Job__Build_Sets );

    TgSTD_ATOMIC(fetch_sub_explicit)( g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS + tiWorld.m_uiI, 1, TgSTD_MEMORY_ORDER(seq_cst) );

    /* Set the fence to be equivalent to job count. */
    TgVERIFY(1 == TgSTD_ATOMIC(load_explicit)( g_axuiPH_FENCE__UPDATE_WORLD + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) ));

    psJob_Finish_Data.psBuild_Sets_Data->m_tiWorld = tiWorld;
    psJob_Finish_Data.psBuild_Sets_Data->m_bCollision = true;
    psJob_Finish_Data.psBuild_Sets_Data->m_bSimulation = true;

    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, psFinish_Job )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        while (0 != TgSTD_ATOMIC(load_explicit)( psFinish_Job->m_pxuiTrigger, TgSTD_MEMORY_ORDER(relaxed) ))
        {
            tgTR_Pause();
        };
        tgPH_Update_World__Job__Finish( psFinish_Job );
    };

    return (KTgS_OK);
}

/* ---- tgPH_Update_World__Job__Finish ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgPH_Update_World__Job__Finish( STg2_Job_CPC psJob )
{
    union { STg2_PH_Job__Update_World__Build_Set_Data_CP psJob; TgUINT_E08_CP pui; } const sData = { .pui  = psJob->m_auiData };
    TgPH_WORLD_ID_C                     tiWorld = sData.psJob->m_tiWorld;
    STg2_PH_World_PC                    psWorld = tgPH_World_Get_World_From_ID( tiWorld );
    union
    {
        STg2_PH_Constraint_P                psCT;
        STg2_UT_ST__ST_Node_P               psNode;
        
    }                                   uCT;

    TgPARAM_CHECK(sData.psJob);
    TgPARAM_CHECK(nullptr != g_asPH_Update__Simulation[tiWorld.m_uiI].m_avBY_Pos_O2W);
    TgPARAM_CHECK(nullptr != g_asPH_Update__Simulation[tiWorld.m_uiI].m_avRHS_LA);
    TgPARAM_CHECK(nullptr != g_asPH_Update__Simulation[tiWorld.m_uiI].m_amFM_Final_O2W);
    TgPARAM_CHECK(nullptr != g_asPH_Update__Simulation[tiWorld.m_uiI].m_avFM_Pos_O2W);
    TgPARAM_CHECK(nullptr != g_asPH_Update__Simulation[tiWorld.m_uiI].m_asFM_BA_W);

    if (nullptr != g_asPH_Update__Simulation[tiWorld.m_uiI].m_avBY_Pos_O2W)
    {
        TgFREE_POOL( g_asPH_Update__Simulation[tiWorld.m_uiI].m_avBY_Pos_O2W );
        g_asPH_Update__Simulation[tiWorld.m_uiI].m_avBY_Pos_O2W = nullptr;
    }
    if (nullptr != g_asPH_Update__Simulation[tiWorld.m_uiI].m_avRHS_LA)
    {
        TgFREE_POOL( g_asPH_Update__Simulation[tiWorld.m_uiI].m_avRHS_LA );
        g_asPH_Update__Simulation[tiWorld.m_uiI].m_avRHS_LA = nullptr;
    }
    if (nullptr != g_asPH_Update__Simulation[tiWorld.m_uiI].m_amFM_Final_O2W)
    {
        TgFREE_POOL( g_asPH_Update__Simulation[tiWorld.m_uiI].m_amFM_Final_O2W );
        g_asPH_Update__Simulation[tiWorld.m_uiI].m_amFM_Final_O2W = nullptr;
    }
    if (nullptr != g_asPH_Update__Simulation[tiWorld.m_uiI].m_avFM_Pos_O2W)
    {
        TgFREE_POOL( g_asPH_Update__Simulation[tiWorld.m_uiI].m_avFM_Pos_O2W );
        g_asPH_Update__Simulation[tiWorld.m_uiI].m_avFM_Pos_O2W = nullptr;
    }
    if (nullptr != g_asPH_Update__Simulation[tiWorld.m_uiI].m_asFM_BA_W)
    {
        TgFREE_POOL( g_asPH_Update__Simulation[tiWorld.m_uiI].m_asFM_BA_W );
        g_asPH_Update__Simulation[tiWorld.m_uiI].m_asFM_BA_W = nullptr;
    }

    /* In the case where we have run Collision but not Simulation then all Contacts are in the deferred state (on the stack) and need to be cleared. */
    uCT.psNode = tgCM_UT_LF__ST__Pop( &g_asPH_Update__Constraint_IMM[tiWorld.m_uiI].m_sStack );
    while (uCT.psNode)
    {
    #if defined(TgBUILD_DEBUG__PHYSICS)
        if (g_nuiPH_Debug__Contact < KTgPH_DEBUG_MAX_CONTACT)
        {
            g_auPH_Debug__Contact[g_nuiPH_Debug__Contact].m_vF32_04_1 = uCT.psCT->m_sContact.m_sContact.m_vS0;
            ++g_nuiPH_Debug__Contact;
        };
    /*# defined(TgBUILD_DEBUG__PHYSICS) */
    #endif
        tgMM_Set_U08_0x00( uCT.psCT, sizeof(STg2_PH_Constraint) );
        tgCM_UT_LF__ST__Push( &g_asPH_Constraint_Free_Stack[tiWorld.m_uiI].m_sStack, uCT.psNode );
        uCT.psNode = tgCM_UT_LF__ST__Pop( &g_asPH_Update__Constraint_IMM[tiWorld.m_uiI].m_sStack );
    };

    if (sData.psJob->m_bCollision && !sData.psJob->m_bSimulation)
    {
        TgRSIZE_C                           nuiBody_World = TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Body_Total__Used + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) );
        TgRSIZE                             uiIndex;

        for (uiIndex = 0; uiIndex < nuiBody_World; ++uiIndex)
        {
            g_aapsPH_Body_Used[tiWorld.m_uiI][uiIndex]->m_vXF = tgMH_SET1_F32_04_1( 0.0F );
            g_aapsPH_Body_Used[tiWorld.m_uiI][uiIndex]->m_vXT = tgMH_SET1_F32_04_1( 0.0F );
        };
    };

    TgDIAG(0 == TgSTD_ATOMIC(load)( g_aaxnuiPH_Constraint_Total__Used_By_Type[tiWorld.m_uiI] + ETgPH_CONSTRAINT__CONTACT));

    tgMM_Set_U08_0x00( g_asPH_Update__Simulation + tiWorld.m_uiI, sizeof(STg2_PH_Update__Simulation) );

    PROFILE_ARRAY_START( tiWorld.m_uiI, PH_CMD_BUFFER_EXECEUTE, tgPH_Update_World__Job__Finish );
    PROFILE_START( PH_CMD_BUFFER_EXECEUTE_TOTAL, tgPH_Update_World__Job__Finish );

    tgCM_UT__CMD_BUF__Execute( g_asPH_Command_To_World + tiWorld.m_uiI );

    PROFILE_STOP( PH_CMD_BUFFER_EXECEUTE_TOTAL, tgPH_Update_World__Job__Finish );
    PROFILE_ARRAY_STOP( tiWorld.m_uiI, PH_CMD_BUFFER_EXECEUTE, tgPH_Update_World__Job__Finish );

    psWorld->m_uiSingle_Step = 0;

    TgSTD_ATOMIC(fetch_sub_explicit)( g_axuiPH_FENCE__UPDATE_WORLD + tiWorld.m_uiI, 1, TgSTD_MEMORY_ORDER(seq_cst) );

    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Debug Functions                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_World_Validate ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_DEBUG__PHYSICS)
TgVOID tgPH_World_Validate( STg2_Output_PC psOUT, TgPH_WORLD_ID_C tiWorld )
{
//# TODO: tgPH_World_Validate
    (void)psOUT;
    (void)tiWorld;

}
/*# defined(TgBUILD_DEBUG__PHYSICS) */
#endif
