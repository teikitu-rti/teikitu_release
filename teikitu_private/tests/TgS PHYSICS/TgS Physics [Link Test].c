/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics [Link Test].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE)                                                                                     \
    tgPH_##OBJ_NAME##_Set_##ATTRIBUTE( ti##OBJ_NAME, ATTRIBUTE_TYPE##_VAR );                                                                      \
    tgPH_##OBJ_NAME##_Query_##ATTRIBUTE( & ATTRIBUTE_TYPE##_VAR, ti##OBJ_NAME );                                                           \

#define PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE)                                                                                       \
    tgPH_##OBJ_NAME##_Set_##ATTRIBUTE( ti##OBJ_NAME, & ATTRIBUTE_TYPE##_VAR );                                                                    \
    tgPH_##OBJ_NAME##_Query_##ATTRIBUTE( & ATTRIBUTE_TYPE##_VAR, ti##OBJ_NAME );                                                           \

TEST_METHOD_DEFINE( LINK_TEST__TEST__PH )
{
    TgPH_MATERIAL_ID tiMaterial = { .m_uiKI=0 };
    TgPH_FORM_ID tiForm = { .m_uiKI=0 };
    TgPH_BODY_ID tiBody = { .m_uiKI=0 };
    TgPH_CONSTRAINT_ID tiConstraint = { .m_uiKI=0 };
    TgPH_MOTOR_ID tiMotor = { .m_uiKI=0 };
    TgPH_RAGDOLL_ID tiRagdoll = { .m_uiKI=0 };
    TgPH_SCENE_ID tiScene = { .m_uiKI=0 };
    TgPH_WORLD_ID tiWorld = { .m_uiKI=0 };

    TgPARTITION_OBJECT_ID TgPARTITION_OBJECT_ID_VAR = { .m_uiKI=0 };

    TgVEC_F32_04_1 TgVEC_F32_04_1_VAR = {0};
    TgFLOAT32 TgFLOAT32_VAR = 0.0F;
    TgUINT_E64 TgUINT_E64_VAR = 0;
    TgBOOL TgBOOL_VAR = 0;
    TgPH_FCN_CALCFM TgCALCFM_FCN_VAR = 0;
    TgPH_FCN_CONTACT TgCONTACT_FCN_VAR = 0;
    TgPH_FCN_MOVED TgMOVED_FCN_VAR = 0;
    TgUINT_PTR TgUINT_PTR_VAR = 0;

    TgVEC_F32_04_3 TgVEC_F32_04_3_VAR;
    TgVEC_F32_04_3_VAR.m_vC0 = KTgZERO_F32_04_1;
    TgVEC_F32_04_3_VAR.m_vC1 = KTgZERO_F32_04_1;
    TgVEC_F32_04_3_VAR.m_vC2 = KTgZERO_F32_04_1;

    tgPH_Module_Init();
    tgPH_Module_Boot();
    tgPH_Module_Stop();
    tgPH_Module_Free();
    tgPH_Module_Update( 1.0F );
    tgPH_Load_Config();
    tgPH_Save_Config();
    tgPH_Query_Init();
    tgPH_Query_Boot();
    tgPH_Query_Fixed_Memory();

    #if TgS_STAT__PHYSICS
    tgPH_Stats( nullptr );
    #endif

    tgPH__Server__Update( 1.0F );
    tgPH__Client__Update_PreInput( 1.0F );
    tgPH__Client__Update_PostInput( 1.0F );

    tgPH_Set_Pause_Module( true );
    tgPH_Is_Module_Paused();
    tgPH_Set_Iteration_Limit( 1 );
    tgPH_Query_Iteration_Limit();

    /* Material                                                                                                                                                                    */
    tgPH_Material_Init();
    tgPH_Material_Reset( tiMaterial );
    tgPH_Material_Query_Count();
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Density,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Hardness_Brinell,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Tensile_Strength_Ultimate,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Tensile_Strength_Yield,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Elongation_At_Break,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Modulus_Elasticity,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Poisson_Ratio,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Shear_Modulus,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Thermal_Expansion,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Thermal_Conductivity,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Melting_Temperature,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Boiling_Temperature,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Vapour_Pressure,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Surface_Tension,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Dynamic_Viscosity,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Kinematic_Viscosity,TgFLOAT32)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Material,MATERIAL,Speed_of_Sound,TgFLOAT32)

    /* Form/Shape                                                                                                                                                                  */
    tgPH_Form_Init( tiWorld );
    tgPH_Form_Reset( tiForm );
    tgPH_Form_Query_Count( tiWorld );
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Form,FORM,Category,TgUINT_E64)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Form,FORM,Collide,TgUINT_E64)
    tgPH_Form_Query_Next_Form_ID( &tiForm, tiForm );
    tgPH_Form_Query_Body_ID( &tiBody, tiForm );
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Form,FORM,Sweep_ID,TgPARTITION_OBJECT_ID)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Form,FORM,Scale,TgVEC_F32_04_1) // Scale to be applied to the base geometry
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Form,FORM,Colour,TgVEC_F32_04_1) // Debug Colour

    /* Body                                                                                                                                                                        */
    tgPH_Body_Init( tiWorld );
    tgPH_Body_Reset( tiBody );
    tgPH_Body_Query_Count( tiWorld );
    tgPH_Body_Add_Force_At_Location( tiBody, TgVEC_F32_04_1_VAR, TgVEC_F32_04_1_VAR );
    tgPH_Body_Apply_Drag( tiBody, 1.0F ); /**< Apply a constant drag to both velocities. */
    tgPH_Body_Query_First_Form_ID( &tiForm, tiBody );
    tgPH_Body_Query_First_Constraint_ID( &tiConstraint, tiBody );
    tgPH_Body_Query_Moment_Of_Inertia( &TgVEC_F32_04_3_VAR, tiBody );
    tgPH_Body_Query_Centre_Of_Gravity( &TgVEC_F32_04_1_VAR, tiBody );
    tgPH_Body_Query_Mass( &TgVEC_F32_04_1_VAR, tiBody );
    tgPH_Body_Query_Inverse_Moment_Of_Inertia( &TgVEC_F32_04_3_VAR, tiBody );
    tgPH_Body_Query_Inverse_Mass( &TgVEC_F32_04_1_VAR, tiBody );
    tgPH_Body_Add_Linear_Velocity( tiBody, TgVEC_F32_04_1_VAR ); /**< Linear Velocity */
    tgPH_Body_Add_Force( tiBody, TgVEC_F32_04_1_VAR );
    tgPH_Body_Add_Persistent_Force( tiBody, TgVEC_F32_04_1_VAR ); /**< Persistent Force */
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Body,BODY,Linear_Velocity,TgVEC_F32_04_1)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Body,BODY,Persistent_Force,TgVEC_F32_04_1)
    tgPH_Body_Add_Angular_Velocity( tiBody, TgVEC_F32_04_1_VAR ); /**< Angular Velocity */
    tgPH_Body_Add_Torque( tiBody, TgVEC_F32_04_1_VAR );
    tgPH_Body_Add_Persistent_Torque( tiBody, TgVEC_F32_04_1_VAR ); /**< Persistent Torque */
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Body,BODY,Angular_Velocity,TgVEC_F32_04_1)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Body,BODY,Persistent_Torque,TgVEC_F32_04_1)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Body,BODY,Force_Field_Factor,TgVEC_F32_04_1)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Body,BODY,Time_Factor,TgVEC_F32_04_1)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Body,BODY,Disable_Timer,TgFLOAT32)
    tgPH_Body_Query_Ragdoll( &TgBOOL_VAR, tiBody );
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Body,BODY,CalcFM_FCN,TgCALCFM_FCN)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Body,BODY,Contact_FCN,TgCONTACT_FCN)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Body,BODY,Moved_FCN,TgMOVED_FCN)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(Body,BODY,Context,TgUINT_PTR)
    tgPH_Body_Query_Update( &TgBOOL_VAR, tiBody );

    /* Constraint                                                                                                                                                                  */
    tgPH_Constraint_Init( tiWorld );
    tgPH_Constraint_Reset( tiConstraint );
    tgPH_Constraint_Query_Count( tiWorld );
    tgPH_Constraint_Set_Breakable( tiConstraint, true );
    tgPH_Constraint_Query_Connected( tiBody, tiBody );
    tgPH_Constraint_Query_Next_Constraint_ID_For_Body_0( &tiConstraint, tiConstraint );
    tgPH_Constraint_Query_Next_Constraint_ID_For_Body_1( &tiConstraint, tiConstraint );

    /* Motor                                                                                                                                                                       */
    tgPH_Motor_Init( tiWorld );
    tgPH_Motor_Reset( tiMotor );
    tgPH_Motor_Query_Count( tiWorld );

    /* Ragdoll                                                                                                                                                                     */
    tgPH_Ragdoll_Init( tiWorld );
    tgPH_Ragdoll_Reset( tiRagdoll );
    tgPH_Ragdoll_Query_Count( tiWorld );

    /* Scene                                                                                                                                                                       */
    tgPH_Scene_Init();  /* #IMPLEMENT */
    tgPH_Scene_Reset( tiScene );  /* #IMPLEMENT */
    tgPH_Scene_Query_Count();  /* #IMPLEMENT */

    /* World                                                                                                                                                                       */
    tgPH_World_Reset( tiWorld );
    tgPH_World_Query_Count();
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(World,WORLD,Pause_State,TgBOOL)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(World,WORLD,Single_Step,TgBOOL)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(World,WORLD,Simulation_Enable,TgBOOL)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(World,WORLD,Collision_Enable,TgBOOL)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(World,WORLD,Force_Field,TgVEC_F32_04_1)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(World,WORLD,Threshold_Depth,TgVEC_F32_04_1)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(World,WORLD,Threshold_LV,TgVEC_F32_04_1)
    PHYSICS_FUNCTION_ACCESSOR__LINK_TEST_ASSIGN(World,WORLD,Threshold_AV,TgVEC_F32_04_1)


    //TgEXTN TgVEC_F32_04_1
    //tgPH_Impulse_To_Force(
    //    1.0F, TgVEC_F32_04_1_VAR );  /* #IMPLEMENT */

    tgPH_Body_Query_LV_Point( tiBody, TgVEC_F32_04_1_VAR );  /* #IMPLEMENT */
    return KTgS_OK;
}
