/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Internal - Type.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_INTERNAL_TYPE_H)
#define TGS_PHYSICS_INTERNAL_TYPE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* -- Form ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* #TODO #OPT Do we want to cache the transformed collision primitive? */

TgTYPE_UNION( STg2_PH_Form, )
{
    STg2_UT_ST__ST_Node                         m_sNode_Stack;
    struct
    {
        TgRSIZE                                     m_uiUsed_Index;
        TgPH_FORM_ID                                m_tiForm; /**< Unique identifier for this Form. */

        TgUINT_E64                                  m_uiCategory;  /**< Bitfield representing the fields this form is categorized. */
        TgUINT_E64                                  m_uiCollide; /**< Bitfield representing those fields this form collides. */
        TgPH_MATERIAL_ID                            m_tiMaterial; /**< Physical material properties. */
        TgUINT_E32                                  m_uiPad0;

        ETgPM_SHORT                                 m_enPM; /**< Collision primitive used by a Form. */
        UTg2_CO_Primitive_F32_04                    m_uPM; /**< Union of available collision primitives. */
        TgVOID                                      (*m_pfnPM_Copy_TX)( TgVOID_PCU, TgVOID_CPCU, TgVOID_CPCU ); /* Function used to transform the primitive for collision test. */
        TgVOID                                      (*m_pfnPM_Sweep_BA)( TgVOID_PCU, TgVOID_CPCU, TgVEC_F32_04_1_C ); /* Function used to transform the primitive for collision test. */
        TgVEC_F32_04_1                              (*m_pfnPM_Support_Point)( TgVOID_CPCU, TgVEC_F32_04_1_C ); /* Function used to transform the primitive for collision test. */

        TgPH_BODY_ID                                m_tiBY; /**< Parent Body. */
        TgPH_FORM_ID                                m_tiNext; /**< Next form that is linked to the same parent body. */
        TgPARTITION_OBJECT_ID                       m_tiPnS; /**< Prune and Sweep ID. */

        TgVEC_F32_04_1                              m_vPos_O2B; /**< Position of the Form in Parent Reference Frame. */
        TgVEC_F32_04_1                              m_vRot_O2B; /**< Quaternion rotation of the Form in Parent Reference Frame. */
        TgVEC_F32_04_1                              m_vScale; /**< Scale that is applied in Body space prior to other transforms. */
        TgVEC_F32_04_3                              m_mLocal_O2B; /**< Transform for the Form in the owning Body space. */
        TgBOXAA_F32_04                              m_sBA_O; /**< Axis-Aligned Bounding Box of the Form. */

        TgVEC_F32_04_1                              m_vPos_Last_Valid_O2W; /**< Previous Position of the Form in World Space. */
        TgVEC_F32_04_1                              m_vPos_O2W; /**< Position of the Form in World Space. */
        TgVEC_F32_04_3                              m_mFinal_O2W; /**< Transform into world space. */
        TgBOXAA_F32_04                              m_sBA_W; /**< Axis-Aligned Bounding Box of the Form. */

        TgVEC_F32_04_1                              m_vDebug_Colour;

        TgFLOAT32                                   m_fDisable_Timer; /**< A measure of the time the form has experienced movement under the sleep threshold. */
        TgUINT_E08                                  m_uiUpdate : 1;
        TgUINT_E08                                  m_uiFlags : 7;
    #if 0 != (139 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad1[139 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
};


/* -- Body ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_UNION( STg2_PH_Body, )
{
    STg2_UT_ST__ST_Node                         m_sNode_Stack;
    struct
    {
        TgRSIZE                                     m_uiUsed_Index;
        TgPH_BODY_ID                                m_tiBody;
        TgPH_FORM_ID                                m_tiFM_Head; /**< The first form associated with this body.  */
        TgPH_CONSTRAINT_ID                          m_tiCT_Head; /**< The first constraint associated with this body.  */

        STg2_PH_Mass                                m_sMass; /**< Mass representation in body space  */

        TgVEC_F32_04_1                              m_vPos_Last_Valid_O2W; /**< Last Position  */
        TgVEC_F32_04_1                              m_vPos_O2W; /**< Position  */
        TgVEC_F32_04_1                              m_vRot_O2W; /**< Rotation in quaternion form. */
        TgVEC_F32_04_3                              m_mRot_O2W; /**< Rotation in matrix form. */
        TgVEC_F32_04_3                              m_mFinal_O2W; /**< Full Transform, used primarily for rotation  */

        TgVEC_F32_04_1                              m_vLV; /**< Linear Velocity  */
        TgVEC_F32_04_1                              m_vPF; /**< Persistent Force  */

        TgVEC_F32_04_1                              m_vAV; /**< Angular Velocity  */
        TgVEC_F32_04_1                              m_vPT; /**< Persistent Torque  */

        TgVEC_F32_04_1                              m_vForce_Field_Factor; /**< Floating Point Flag - 1.0 if influenced by the force field.  */
        TgVEC_F32_04_1                              m_vTime_Factor; /**< Used to manipulate time on a per-body basis (Matrix Effect).  */

        TgPH_FCN_CALCFM                             m_pfnCalcFM; /**< User defined function to generate force and moments.  */
        TgPH_FCN_CONTACT                            m_pfnContact; /**< Function called when a contact occurs involving this body.  */
        TgPH_FCN_MOVED                              m_pfnMoved; /**< Function called when a contact occurs involving this body.  */
        TgUINT_PTR                                  m_uiContext; /**< Void pointed passed into one of the user defined call backs.  */
        TgUINT_PTR                                  m_uiPad0;

        TgUINT_E32                                  m_bUpdate : 1; /**< Set indicates that the body is enabled (but may not be active). */
        TgUINT_E32                                  m_bRagdoll : 1; /**< Set indicates that the body is part of a ragdoll. */
        TgUINT_E32                                  m_bPad_1 : 30;

                                                    /* Calculated and used during world update. */
        TgFLOAT32                                   m_fDisable_Timer; /**< Timer for auto-disabling the body  */
        TgVEC_F32_04_3                              m_mInverse_Inertia_Tensor; /**< Inverse Inertia Tensor: Used to transform torque into rotation updates, and in the solver. */
        TgVEC_F32_04_1                              m_vXF; /**< Force Accumulation: Used for predicted and final position. */
        TgVEC_F32_04_1                              m_vXT; /**< Torque Accumulation: Used for predicted and final rotation. */
    #if 0 != (224 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad1[224 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
};


/* -- Motor ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_UNION(STg2_PH_Motor,)
{
    STg2_UT_ST__ST_Node                         m_sNode_Stack;
    struct
    {
        TgRSIZE                                     m_uiUsed_Index;
        TgPH_MOTOR_ID                               m_tiMotor;
        TgUINT_E64                                  m_uiCategory;  /**< Bitfield representing the fields this form is categorized  */
    };
};


/* -- Constraints ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */


TgTYPE_STRUCT(STg2_PH_Constraint_Ball_Socket,)
{
    TgVEC_F32_04_1                              m_vPad;
};

TgTYPE_STRUCT(STg2_PH_Constraint_Contact,)
{
    STg2_CO_Contact_F32_04                      m_sContact;
    STg2_PH_Form_CP                             m_psFM0;
    STg2_PH_Form_CP                             m_psFM1;
    TgVEC_F32_04_1                              m_vRestitution_Factor;
};

TgTYPE_UNION(STg2_PH_Constraint,)
{
    STg2_UT_ST__ST_Node                         m_sNode_Stack;
    struct
    {
        TgRSIZE                                     m_uiUsed_Index;
        TgPH_CONSTRAINT_ID                          m_tiConstraint;
        TgPH_BODY_ID                                m_tiBY0; /**< Identifier for the first body in the constraint. */
        TgPH_CONSTRAINT_ID                          m_tiNext_0; /**< Identifier for the next constraint that is associated with Body 0. */
        TgPH_BODY_ID                                m_tiBY1; /**< Identifier for the second body in the constraint. */
        TgPH_CONSTRAINT_ID                          m_tiNext_1; /**< Identifier for the next constraint that is associated with Body 1. */

        ETgPH_CONSTRAINT                            m_enConstraint;

        TgFLOAT32                                   m_fMin; /**< Lower Limit, Point of compression failure. */
        TgFLOAT32                                   m_fMax; /**< Upper Limit, Point of fracture. */
        TgFLOAT32                                   m_fMax_Moment;
        TgFLOAT32                                   m_fμs, m_fμd; /**< Static and Dynamic coefficients of friction. */

        TgUINT_E32                                  m_bBreakable : 1;
        TgUINT_E32                                  m_bEnabled : 1;
        TgUINT_E32                                  m_uiPad0 : 30;

        TgUINT_E32                                  m_nuiDoF; /**< Number of degrees of freedom for the joint. */
        TgVEC_F32_04_1                              m_vOffset;
        TgVEC_F32_04_1                              m_VFoR_Rot; /**< Frame of Reference of the constraint, Quaternion */
        TgVEC_F32_04_1                              m_VFoR_Pos; /**< Frame of Reference of the constraint, Position */

        union {
            STg2_PH_Constraint_Ball_Socket          m_sBall_Socket;
            STg2_PH_Constraint_Contact              m_sContact;
        };

    #if defined(TGS_PS_JOINT_FEEDBACK)
        TgVEC_F32_04_1                              m_tvF0, m_tvT0;
        TgVEC_F32_04_1                              m_tvF1, m_tvT1;
    #endif

    #if 0 != (32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad[32 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
};

typedef TgVOID(*TgPH_FCN_USER_CONTACT_COMPLETE)( STg2_PH_Constraint_CPC );
TgTYPE_MODIFIER_DEFAULT(TgPH_FCN_USER_CONTACT_COMPLETE);


/* -- Ragdoll -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_PH_Ragdoll_Bone,)
{
    TgVEC_F32_04_1                              m_vPos_O2R; /**< Position of the bone in the Ragdoll reference frame. */
    TgVEC_F32_04_3                              m_mLocal_O2R; /**< Final transform from Origin Space to the Ragdoll reference frame. */
    TgUINT_E32                                  m_idxParent;
    TgUINT_E32                                  m_idxBone;
    TgPH_FORM_ID                                m_tiFM; /**< UID for the Form associated with this bone. */
    TgPH_BODY_ID                                m_tiBY; /**< UID for the Body associated with this bone. */
    TgPH_CONSTRAINT_ID                          m_tiCT; /**< UID for the Constraint binding this bone to the rag doll tree. */
    TgPH_MOTOR_ID                               m_tiMR; /**< UID for the Motor used to drive the simulation toward an animation result. */
    TgUINT_E64                                  m_uiPad;
};


TgTYPE_UNION(STg2_PH_Ragdoll,)
{
    STg2_UT_ST__ST_Node                         m_sNode_Stack;
    struct
    {
        TgRSIZE                                     m_uiUsed_Index;
        TgPH_RAGDOLL_ID                             m_tiRagdoll;
        STg2_PH_Ragdoll_Bone_P                      m_asBone[KTgPH_MAX_BONES]; /**< List of rag doll bones. */
        TgRSIZE                                     m_nuiBone; /**< Number of rag doll bones. */
        TgUINT_PTR                                  m_uiContext; /**< The owning object - most often an actor. */
        TgUINT_E64                                  m_bConstraint_Init : 1;
        TgUINT_E64                                  m_bConstraint_Locked : 1;
        TgUINT_E64                                  m_uiPad : 62;
    #if 0 != (216 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad1[216 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
};


/* ---- Scene -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_UNION(STg2_PH_Scene,)
{
    STg2_UT_ST__ST_Node                         m_sNode_Stack;
    struct
    {
        TgRSIZE                                     m_uiUsed_Index;
        TgPH_SCENE_ID                               m_tiScene;
    };
};


/* ---- World ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_PH_World,)
{
    TgPH_WORLD_ID                               m_tiWorld;

                                                /* Solver Configuration */
    TgRSIZE                                     m_uiSimulate_Min_Batch_Size; /**< Minimum number of bodies per job call. */
    TgRSIZE                                     m_uiCollide_Min_Batch_Size; /**< Minimum number of forms per job call. */
    TgRSIZE                                     m_uiSolver_Min_Body_Per_Job; /**< Minimum number of bodies per job call. */
    TgRSIZE                                     m_uiSolver_Min_DoF_Per_Job; /**< Minimum number of degrees of freedom per job call. */
    TgRSIZE                                     m_nuiSolver_Iterations; /**< Number of iterations of the solver loop to execute. */

#if defined(TgBUILD_FEATURE__PHYSICS__CFM)
    TgFLOAT32                                   m_fCFM;
#else
    TgFLOAT32                                   m_fPad;
#endif
    TgFLOAT32                                   m_fStep_Size_Seconds; /**< Floating point time step in seconds used for each simulation step. */
    TgUINT_E64                                  m_uiPad;

    TgVEC_F32_04_1                              m_vThreshold__Depth; /**< The penetration depth sleep threshold. */
    TgVEC_F32_04_1                              m_vThreshold__LV_LSQ; /**< The linear velocity sleep threshold. */
    TgVEC_F32_04_1                              m_vThreshold__AV_LSQ; /**< The angular velocity sleep threshold. */
    TgVEC_F32_04_1                              m_vConstraint_Error_Correction_Rate; /**< 1st Order Controller: Percentage of Constraint error that is corrected per iteration. */

                                                /* World Configuration */
    TgVEC_F32_04_1                              m_vForce_Field; /**< The acceleration field applied to all bodies during simulation. */
    TgVEC_F32_04_1                              m_vStep_Size; /**< The size of the fixed time step used during update. */
    TgPH_FCN_UPDATE_COLLISION_SCENE             m_pfnCollision_Update; /**< Function to use as the entry point to the Collision pass during World Update. */
    TgPARTITION_GRAPH_ID                        m_tiPA_Graph; /**< UID for the Partition Manager Graph used in the Collision pass. */

                                                /* Run Time Configuration */
    TgUINT_E64                                  m_uiPaused : 1; /**< True if the world is in a pause state, and false otherwise. */
    TgUINT_E64                                  m_uiSingle_Step : 1; /**< True if the module should execute a single step, and false otherwise. */
    TgUINT_E64                                  m_uiSimulate : 1; /**< True if the simulation pass is active, and false otherwise. */
    TgUINT_E64                                  m_uiCollide : 1; /**< True if the collision pass is active, and false otherwise. */
    TgUINT_E64                                  m_uiCollision_Simple : 1; /**< True if the simple (N^2) collision pair generator is used, and false otherwise. */
    TgUINT_E64                                  m_uiPad1 : 59;

                                                /* Serialization */
    STg2_PH_Scene_P                             m_psScene; /**< List of all the scenes associated with this world. */
};


/* ---- Solver ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT( STg2_PH_Update__Simulation, )
{
                                                /* These lists are 1:1 with g_aapsBody_Used. */
    TgVEC_F32_04_1_P                            m_avBY_Pos_O2W; /**< Predicted Position: Used in Constraints. */
    TgVEC_F32_04_1_P                            m_avRHS_LA; /**< Linear, Angular Right Hand Side component, used in Constraint Coefficient generation to finalize RHS. */

                                                /* These lists are 1:1 with g_aapsForm_Used. */
    TgVEC_F32_04_3_P                            m_amFM_Final_O2W; /**< Predicted Final Transform: Used in Collsion Pass */
    TgVEC_F32_04_1_P                            m_avFM_Pos_O2W; /**< Predicted Final Position: Used in Collsion Pass */
    TgBOXAA_F32_04_P                            m_asFM_BA_W; /**< Axis Aligned Bounding Box covering current position and rotation swept to the predicted position and rotation. */
};

TgTYPE_STRUCT( STg2_PH_Update__Contact, )
{
    TgVEC_F32_04_1                              m_vS0_W; /**< Position of Contact */
    TgVEC_F32_04_1                              m_vN0_W; /**< Normal of impact */
    TgFLOAT32                                   m_fT0; /**< Sweep time value */
    TgFLOAT32                                   m_fDepth; /**< Penetration depth */
    TgPH_FORM_ID                                m_tiFM0;
    TgPH_FORM_ID                                m_tiFM1; /**< The two forms involved in the contact */
    TgPH_MATERIAL_ID                            m_tiMaterial; /**< The material used to describe the contact */
};

TgTYPE_STRUCT( STg2_PH_Solver__Set, )
{
                                                /* Generated when creating the closed sets for the solver jobs. */
    STg2_PH_Body_PP                             m_apsBody; /**< List of all the bodies in this world. */
    TgRSIZE                                     m_nuiBody; /**< Number of bodies in the set. */

    STg2_PH_Constraint_PP                       m_apsConstraint[ETgPH_CONSTRAINT__MAX]; /**< Lists of all the constraints in this world. */
    TgRSIZE                                     m_nuiConstraint[ETgPH_CONSTRAINT__MAX]; /**< Count of constraints by constraint type. */
    TgRSIZE_P                                   m_apuiDoF[ETgPH_CONSTRAINT__MAX]; /**< The DoF count when this constraint was added to the set. */
    TgRSIZE                                     m_nuiDoF; /**< Total sum of the number of degrees of freedom. Total rows in the Jacobian. */
    TgRSIZE                                     m_nuiConstraint_Total; /**< Total sum of the number of degrees of freedom. Total rows in the Jacobian. */
    STg2_PH_Constraint_PP                       m_apsInvalid_Contact_Constraint; /**< List of the Contact Constraints that were not added to the solution */
    TgRSIZE                                     m_nuiInvalid_Contact_Constraint; /**< Count of Invalid Contact Constraints.  */

                                                /* Generated data (per Constraint). */
    TgVEC_F32_04_1_P                            m_avInverse_Mass_Inertia_Tensor; /**< Inverse Mass, Inverse Inertia Tensor for each constraint and each body in the constraint. */
    TgRSIZE_P                                   m_auiJacobian_Index; /**< The two bodies associated with each Constraint; */
    TgRSIZE_P                                   m_anuiDoF; /**< The number of DoF AFTER the addition of the Constraint; */

                                                /* Generated data (per DoF) representing the requirements (constraints) of the solution. */
    TgVEC_F32_04_1_P                            m_avProblem_Coefficients;

                                                /* Generated data (per Body). */
    TgVEC_F32_04_1_P                            m_avResult; /**< Resulting Force and Torque per body from the solver. */
};


/* ---- Job Data ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_PH_Job__Update_World__Simulate_Data, )
{
    TgALIGN(16) TgPH_WORLD_ID                   m_tiWorld;
    TgRSIZE                                     m_uiBody_Index_Begin;
    TgRSIZE                                     m_uiBody_Index_End;
    TgUINT_E08                                  m_uiPad[8];
};
TgCOMPILER_ASSERT( sizeof( STg2_PH_Job__Update_World__Simulate_Data ) <= KTgJOB_DATA_SIZE, 0 );

TgTYPE_STRUCT(STg2_PH_Job__Update_World__Collide_Data, )
{
    TgALIGN(16) TgPH_WORLD_ID                   m_tiWorld;
    TgRSIZE                                     m_uiForm_Index_Begin;
    TgRSIZE                                     m_uiForm_Index_End;
    TgUINT_E08                                  m_uiPad[8];
};
TgCOMPILER_ASSERT( sizeof( STg2_PH_Job__Update_World__Collide_Data ) <= KTgJOB_DATA_SIZE, 0 );

TgTYPE_STRUCT(STg2_PH_Job__Update_World__Build_Set_Data, )
{
    TgALIGN(16) TgPH_WORLD_ID                   m_tiWorld;
    TgUINT_E08                                  m_bSimulation : 1;
    TgUINT_E08                                  m_bCollision : 1;
    TgUINT_E08                                  m_uiFlags : 6;
    TgUINT_E08                                  m_uiPad[7];
};
TgCOMPILER_ASSERT( sizeof( STg2_PH_Job__Update_World__Build_Set_Data ) <= KTgJOB_DATA_SIZE, 0 );

TgTYPE_STRUCT(STg2_PH_Job__Update_World__Solve_Set_Data, )
{
    TgALIGN(16) TgPH_WORLD_ID                   m_tiWorld;
    TgUINT_E08                                  m_uiPad0[8];
    STg2_PH_Solver__Set                         m_sSolver_Set;
    TgUINT_E08                                  m_uiPad1[8];
};
TgCOMPILER_ASSERT( sizeof( STg2_PH_Job__Update_World__Solve_Set_Data ) <= KTgJOB_DATA_SIZE, 0 );


/* =============================================================================================================================================================================== */
#endif

