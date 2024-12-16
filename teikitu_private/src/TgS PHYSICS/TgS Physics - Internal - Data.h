/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Internal - Data.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_INTERNAL_DATA_H)
#if !defined (ENABLE_RELOAD_GUARD)


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Sychronization Model                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Most of the sychronziation model in this Module is implicit and not explicit. In Debug there are paranoid checks to make sure that changes have not violated these implicit
   synchronization assumptions. 

    1. There is an explicit ordering principle through the Fences on the update jobs. These fences are also used in the case that jobs were not able to be queued or that
       the jobs system was disabled. Thus, it has a guarantee of execution ordering regardless of the context.

    2. Each World Update call will explicitly wait for the previous update to be completed.

    3. If Simulation is enabled, then implicit access requirements are:
         write access to g_asPH_Update__Simulation.
          There can be multiple writers as we have implicit guarantee that each writer has a unique set of Body's to update.
         read access to World and World Data
         read access to g_aapsPH_Body_Used
      If Simulation is disabled and Collision is enabled
         write access to g_asPH_Update__Simulation.
          There is a single writer as a predicted motion is still calculated (used by Collision).
         read access to World and World Data
         read access to g_aapsPH_Body_Used

    4. If Collision is enabled, then implicit access requirements are:
         read access to g_asPH_Update__Simulation for the predicted body motion.
         read/write access to World and World Data (constraint linked list on Body)
         read access to g_aapsPH_Body_Used
       If Collision is disabled, then no collision contacts are generated.

    5. Contact Constraint addition to Body Constraint Link List, then implicit access requirements are:
         read/write access to World and World Data (constraint linked list on Body)

    6. If Simulation is Enabled then the Solution Step is next
        a) Build Sets
            read access to World and World Data (Body and Constraint lists)
            write access to Solver Set
        b) Define Problem
            read access to Update Simulation (Predicted Motion and RHS)
            read access to Solver Set (Constraint)
            write access to Solver Set (Problem_Coefficients - Jacobian, Min, Max, CFS, RHS)
        c) Solver
            read access to Solver Set (Problem_Coefficients, IIT, Index)
            write access to Solver Set (Problem_Coefficients, results)
        d) Update Bodies
            read/write to World Data (Body Update)
            read Solver Set (results)
            read/write access to Bodies in the Solver Set (removing contact constraints)
              - All of the Bodies associated with a constraint should be in the same Solver Set (i.e. no overlapping read/write from other jobs)
       If Simulation is Disabled, wait for Collision to complete and run Finish Update (including command buffer excecution)

    7. Command Buffer Execution, then implicit access requirements are:
         read/write access to World and World Data (new/delete operations)
*/




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Material - Object memory allocation is done by the generic code path. */
TgEXTN TgPH_MATERIAL_ID                     g_atiPH_Material_Default[ETgPH_MATERIAL__MAX];

/* Form - Object memory allocation is done by the generic code path. */

/* Body - Object memory allocation is done by the generic code path. */

/* Motor - Object memory allocation is done by the generic code path. */

/* Constraint - Object memory allocation is done by the generic code path. */
TgEXTN TgRSIZE_A                            g_aaxnuiPH_Constraint_Total__Used_By_Type[ETgPH_MAX_WORLD][ETgPH_CONSTRAINT__MAX];

/* Ragdoll - Object memory allocation is done by the generic code path. */

/* Scene */

/* World */

/* Contact */

/* Solver */

TgEXTN STg2_PH_Update__Simulation           g_asPH_Update__Simulation[KTgPH_MAX_WORLD];
TgEXTN STg2_PH_Form_PP                      g_aapsPH_Form_Used[KTgPH_MAX_WORLD]; /**< Array of pointers to all of the used objects. */
TgEXTN TgUINT_E64_P                         g_aauiPH_Form_Used_Category[KTgPH_MAX_WORLD]; /**< Array of pointers to category array for the forms. */
TgEXTN STg2_PH_Body_PP                      g_aapsPH_Body_Used[KTgPH_MAX_WORLD]; /**< Array of pointers to all of the used objects. */
TgEXTN TgUINT_E64_P                         g_aauiVisited_Body[KTgPH_MAX_WORLD]; /**< Bitfield to track when a body is visited during World Update. */
TgEXTN STg2_UT_LF_ISO__ST                   g_asPH_Update__Constraint_IMM[KTgPH_MAX_WORLD];
TgEXTN TgUINT_E64_P                         g_aauiVisited_Constraint[KTgPH_MAX_WORLD]; /**< Bitfield to track when a constraint is visited during World Update. */

/* Module */

TgEXTN STg2_UT_LF_ISO__RW                   g_sPH_Lock__Update_Module;

                                            /* Run time Configuration */

TgEXTN TgBOOL                               g_bPH_Module__Paused; /**< True if the module is in a pause state, and false otherwise */
TgEXTN TgUINT_E64                           g_uiPH_Module__Loop_Max; /**< Maximum number of iterations allowed per frame */

TgEXTN TgCN_VAR_ID                          g_tiPH_CN_Module__Paused;
TgEXTN TgCN_VAR_ID                          g_tiPH_CN_Module__Loop_Max;

                                            /* Synchronization Fences */ 
TgEXTN TgRSIZE_A                            g_axuiPH_FENCE__UPDATE_WORLD[ETgPH_MAX_WORLD];
TgEXTN TgRSIZE_A                            g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH[ETgPH_MAX_WORLD]; /**< Count of the total remaining bodies to be simulated in the world. */
TgEXTN TgRSIZE_A                            g_axuiPH_FENCE__UPDATE_WORLD__COLLISION[ETgPH_MAX_WORLD];
TgEXTN TgRSIZE_A                            g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS[ETgPH_MAX_WORLD];
TgEXTN TgRSIZE_A                            g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS[ETgPH_MAX_WORLD];
TgEXTN TgRSIZE_A                            g_axuiPH_FENCE__UPDATE_WORLD__FINISH[ETgPH_MAX_WORLD];

                                            /* Jobs */
TgEXTN STg2_Job                             g_asPH__Job__Update_World__Simulate_Batch[ETgPH_MAX_WORLD];
TgEXTN STg2_Job                             g_asPH__Job__Update_World__Collision[ETgPH_MAX_WORLD];
TgEXTN STg2_Job                             g_asPH__Job__Update_World__Build_Sets[ETgPH_MAX_WORLD];
TgEXTN STg2_Job                             g_asPH__Job__Update_World__Solve_Sets[ETgPH_MAX_WORLD];
TgEXTN STg2_Job                             g_asPH__Job__Update_World__Finish[ETgPH_MAX_WORLD];

TgEXTN STg2_UT__CMD_BUF                     g_asPH_Command_To_World[KTgPH_MAX_WORLD + 1];




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define __PARENT_FILE__ "TgS Physics - Internal - Data.h"
#define ENABLE_RELOAD_GUARD
#include "TgS PHYSICS/TgS Physics - Object [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_PHYSICS_INTERNAL_DATA_H


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  History Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgBUILD_FEATURE__PHYSICS__HISTORY)

TgEXTN TgVEC_F32_04_1                       g_vPH_History__Body_Pos_W[KTgPH_MAX_HISTORY_BODY];
TgEXTN TgVEC_F32_04_1                       g_vPH_History__Body_Rot_W[KTgPH_MAX_HISTORY_BODY];
TgEXTN TgPH_BODY_ID                         g_tiPH_History__Body_ID[KTgPH_MAX_HISTORY_BODY];
TgEXTN TgRSIZE_A                            g_xnuiPH_History; 

/*# defined(TgBUILD_FEATURE__PHYSICS__HISTORY) */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Debug Data                                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgBUILD_DEBUG__PHYSICS)

                                            /* Visualization */
TgEXTN TgVEC_F32_04_1                       g_vPH_Debug_Colour__Body_Enabled; /**< Debug Colour: Enabled Body */
TgEXTN TgVEC_F32_04_1                       g_vPH_Debug_Colour__Body_Sleep; /**< Debug Colour: Body is being considered for sleep (disabled)  */
TgEXTN TgVEC_F32_04_1                       g_vPH_Debug_Colour__Form_Disabled; /**< Debug Colour: Disabled Form */
TgEXTN TgVEC_F32_04_1                       g_vPH_Debug_Colour__Contact; /**< Debug Colour: Contact */
TgEXTN TgVEC_F32_04_1                       g_vPH_Debug_Colour__Ragdoll; /**< Debug Colour: Ragdoll */

TgEXTN TgCN_VAR_ID                          g_tiPH_Debug_Colour__Body_Enabled;
TgEXTN TgCN_VAR_ID                          g_tiPH_Debug_Colour__Body_Sleep;
TgEXTN TgCN_VAR_ID                          g_tiPH_Debug_Colour__Form_Disabled;
TgEXTN TgCN_VAR_ID                          g_tiPH_Debug_Colour__Contact;
TgEXTN TgCN_VAR_ID                          g_tiPH_Debug_Colour__Ragdoll;

#define KTgPH_DEBUG_MAX_CONTACT 1000
TgEXTN TgVEC_UN_F32_04_1                    g_auPH_Debug__Contact[KTgPH_DEBUG_MAX_CONTACT];
TgEXTN TgRSIZE                              g_nuiPH_Debug__Contact;

                                            /* User Functions */
TgEXTN TgPH_FCN_USER_CONTACT_COMPLETE       g_apfnPH_Debug__World__Contact_Complete[ETgPH_MAX_WORLD];

/*# defined(TgBUILD_DEBUG__PHYSICS) */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Stat Data                                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS

TgEXTN TgRSIZE_A                            g_xnuiFM_Callback;

/*# defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS */
#endif




/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Data Storage for Physics Objects in a combination of array of structure and structure of array approach. Data to be used by the solver is kept in a structure of array pattern.
   Data used for the individual object update is in an array of structure pattern.*/

#if !defined(T_STATIC)

TgEXTN TgRSIZE                              T_NAME_DECLARE(nuiPH_,_Increase_Commit); /**< The additional number of objects to commit to grow the total objects committed. */
TgEXTN TgRSIZE                              T_NAME_DECLARE(nuiPH_,_Total_Commit); /**< The total number of objects committed. */
TgEXTN TgRSIZE                              T_NAME_DECLARE(nuiPH_,_Total_Reserve); /**< The total number of objects reserved. */

TgEXTN STg2_UT_LF_ISO__ST                   T_NAME_DECLARE(sPH_,_Free_Stack); /**< Atomic stack of available objects. */
TgEXTN TgRSIZE_A                            T_NAME_DECLARE(xnuiPH_,); /**< Current count of the number of active objects. */
TgEXTN T_NAME(STg2_PH_,_P)                  T_NAME_DECLARE(asPH_,); /**< Array of all reserved objects. */

TgEXTN STg2_UT_LF_ISO__SN                   T_NAME_DECLARE(sPH_,_Commit_Lock); /**< Lock used to increase the number of committed objects in the array. */
TgEXTN TgRSIZE_A                            T_NAME_DECLARE(xnuiPH_,_Total__Used); /**< The total number of objects used. */

/*# !defined(T_STATIC) */
#else

TgEXTN T_NAME(STg2_PH_,)                    T_NAME_DECLARE(asPH_,)[T_ID(ETgPH_MAX_,)]; /**< Simple fixed array for this resource, one for each world. */

/*# !defined(T_STATIC) */
#endif

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* =============================================================================================================================================================================== */
/*# defined (TGS_PHYSICS_INTERNAL_DATA_H) */
#endif
