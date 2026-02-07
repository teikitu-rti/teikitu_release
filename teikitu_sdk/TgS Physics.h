/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_H)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS PHYSICS/TgS Physics - Constants.h"
#include "TgS PHYSICS/TgS Physics - Type.h"
#include "TgS PHYSICS/TgS Physics - Data.h"
#include "TgS PHYSICS/TgS Physics - Macro.h"


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Module Preamble, Nomenclature, and other Notes                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Reference Frames:
      1. Origin: The raw (untransformed) reference frame.
      2. Form/Body: The reference frame of a Form/Body.
      3. Inertial: A world reference frame without translation. Used in certain cases due to floating point accuracy closer to zero.
      4. World: The reference frame of the World.

    Module Public Objects/Resources/Entities:
      1. Material: Holds most of the defining characteristics of a real life material. A few of these values are used for simulation, the remainder can be used by other modules.
      2. Form: Container for a primitive and material pair used during collision. Attached to a body, the body acts dynamically. Unattached it will act kinematically.
      3. Body: Container object for a set of forms, and a mass. Used in simulation and the solver.
      4. Constraint: A limitation that is placed on one or more bodies that limits their motion.
      5. Motor: A constraint that is capable of applying a force or moment.
      6. Ragdoll: Set of bodies and constraints that is applied to a skeleton (see animation module).
      7. Scene: A packaged set of content that is loaded as a cohesive unit (and unloaded as a set). Example: a portion of a level.
      8. World: A set of content that can interact. Worlds can not interact with other worlds. Worlds may run at different simulation rates and have different configurations.

    Module Private Objects/Resources/Entities:
      1. Mass: Set of representative values to describe the mass of an object (mass, location of the centre of gravity, inertia tensor).

    Bullet Time:
      One of my earliest jobs was working on Blood Rayne 2 where I had to duplicate bullet time like effects. Scaling a physics simulation step size is a "bad" idea. The method
      that I used was to keep the time step constant, and to scale the applied forces and torques. This worked well and needed one exception. All forces and torques generated
      by contact constraints needed to be honoured completely. This kept the simulation consistent and credible. Since this can be done on a per body basis as well, the 
      character was able to walk through a "slo-mo" room filled with objects, interact with them, and I would restore the regular full application scalar to these interacted
      objects and scale them back down over a period of time. The result worked out well.
*/




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @addtogroup TGS_PHYSICS_MODULE */
/** @{ */

/** @brief Standard Module function: First part of initialization process. Set the state of the module. @return Result Code. */
TgEXTN TgRESULT
tgPH_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module. @return Result Code. */
TgEXTN TgRESULT
tgPH_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgPH_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgPH_Module_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount. @return Result Code.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds. */
TgEXTN TgRESULT
tgPH_Module_Update(
    TgFLOAT32_C ARG0 );


/** @brief Standard Module functions: Set the current configuration of the module. */
TgEXTN TgVOID
tgPH_Load_Config( TgVOID );

/** @brief Standard Module function: Save the current configuration of the module. */
TgEXTN TgVOID
tgPH_Save_Config( TgVOID );


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state.
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgPH_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state.
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgPH_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module.
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgPH_Query_Fixed_Memory( TgVOID );


#if TgS_STAT__PHYSICS
/** @brief Standard Module function: Output relevant stats for the module.
    @param [in,out] OUT0 Pointer to an output object. */
TgEXTN TgVOID
tgPH_Stats(
    STg2_Output_P OUT0 );
#endif

/** @} TGS_PHYSICS_MODULE */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Physics Functions                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* -- System Functions ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_SYSTEM */
/** @{ */

#if defined(TgBUILD_FEATURE__SERVER)
/** @brief Server Update
    @param[in] ARG0 Amount of time to step forward the module in milliseconds. */
TgEXTN TgVOID
tgPH__Server__Update(
    TgFLOAT32_C ARG0 );

/** @brief Wait for the Server Physics Update to finish. */
TgEXTN TgVOID
tgPH__Server__Wait_For_Update_Finish( TgVOID );

/*# defined(TgBUILD_FEATURE__SERVER) */
#endif

#if defined(TgBUILD_FEATURE__CLIENT)
/** @brief Client Update for sets not impacted by the player controlled updates.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds. */
TgEXTN TgVOID
tgPH__Client__Update_PreInput(
    TgFLOAT32_C ARG0 );

/** @brief Update for sets impacted by player controlled updates.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds. */
TgEXTN TgVOID
tgPH__Client__Update_PostInput(
    TgFLOAT32_C ARG0 );

/** @brief Wait for the Client Physics Update to finish. */
TgEXTN TgVOID
tgPH__Client__Wait_For_Update_Finish( TgVOID );

/*# defined(TgBUILD_FEATURE__CLIENT) */
#endif

/** @} TGS_PHYSICS_SYSTEM */


/* -- System Configuration ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_SYSTEM_CONFIGURATION */
/** @{ */

/** @brief Places the module into a pause state. */
TgEXTN TgVOID
tgPH_Set_Pause_Module(
    TgBOOL_C ARG0 );

TgEXTN TgBOOL
tgPH_Is_Module_Paused( TgVOID );

/** @brief Set the maximum number of iterations used during a world update. */
TgEXTN TgVOID
tgPH_Set_Iteration_Limit(
    TgUINT_E64_C ARG0 );

TgEXTN TgUINT_E64
tgPH_Query_Iteration_Limit( TgVOID );

/** @} TGS_PHYSICS_SYSTEM_CONFIGURATION */


/* -- Utilities ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */

//TgEXTN TgVEC_F32_04_1
//tgPH_Impulse_To_Force(
//    TgFLOAT32_C ARG0, TgVEC_F32_04_1_C ARG1 );  /* #IMPLEMENT */

TgEXTN TgVEC_F32_04_1
tgPH_Body_Query_LV_Point(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );  /* #IMPLEMENT */




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Physics Objects                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* -- Material ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_MATERIAL */
/** @{ */

/** Many material characteristics vary with the temperature of the material. Since we are not attempting to simulate physical correctness to that level of detail, the material
    data structure does not allow for a time series. Different materials can be created for distinct temperate values as a way to emulate the time series, assuming that the
    material tempature can be known apriori. */


/** @brief Return the material id associated with the given enumerated default material value.
    @return The material id associated with the enumeration value or the invalid material id otherwise.
    @param [in] ARG0 Enumeration value selecting the default material. */
TgEXTN TgPH_MATERIAL_ID
tgPH_Material_Query_Default(
    ETgPH_MATERIAL_DEFAULT_C ARG0 );

/*                                                                                                                                                  Material -- Material Component */

/** @brief Setter for material density. Default materials assumed that it is measured in grams / cubic centimeter. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Density(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the material density. Default materials assumed that it is measured in grams / cubic centimeter. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Density(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for the density of the material. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Hardness_Brinell(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the the density of the material. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Hardness_Brinell(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for yield strength. Default materials assumed that it is measured in Pascals. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Tensile_Strength_Ultimate(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the yield strength. Default materials assumed that it is measured in Pascals. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Tensile_Strength_Ultimate(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for tensile strength. Default materials assumed that it is measured in Pascals. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Tensile_Strength_Yield(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the tensile strength. Default materials assumed that it is measured in Pascals. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Tensile_Strength_Yield(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for tensile strength. Default materials assumed that it is measured in percentage. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Elongation_At_Break(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the tensile strength. Default materials assumed that it is measured in percentage. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Elongation_At_Break(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for the Modulus of Elasticity. Default materials assumed that it is measured in Pascals. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Modulus_Elasticity(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the the Modulus of Elasticity. Default materials assumed that it is measured in Pascals. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Modulus_Elasticity(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for poisson ratio. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Poisson_Ratio(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the poisson ratio. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Poisson_Ratio(
     TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for shear modulus. Default materials assumed that it is measured in Pascals. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Shear_Modulus(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the shear modulus. Default materials assumed that it is measured in Pascals. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Shear_Modulus(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );


/*                                                                                                                                                   Material -- Thermal Component */

/** @brief Setter for thermal expansion. Default materials assumed that it is measured in µm/m°C. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Thermal_Expansion(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the thermal expansion. Default materials assumed that it is measured in µm/m°C. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Thermal_Expansion(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for thermal conductivity. Default materials assumed that it is measured in W/mK. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Thermal_Conductivity(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the thermal conductivity. Default materials assumed that it is measured in W/mK. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Thermal_Conductivity(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for melting temperature. Default materials assumed that it is measured in Celsius. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Melting_Temperature(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the melting temperature. Default materials assumed that it is measured in Celsius. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Melting_Temperature(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for melting temperature. Default materials assumed that it is measured in Celsius. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Boiling_Temperature(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the melting temperature. Default materials assumed that it is measured in Celsius. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Boiling_Temperature(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );


/*                                                                                                                                                     Material -- Fluid Component */

/** @brief Setter for vapour pressure. Default materials assumed that it is measured in Bar. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Vapour_Pressure(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the vapour pressure. Default materials assumed that it is measured in Bar. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Vapour_Pressure(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for surface tension. Default materials assumed that it is measured in dynes / cm. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Surface_Tension(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the surface tension. Default materials assumed that it is measured in dynes / cm. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Surface_Tension(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for dynamic viscosity. Default materials assumed that it is measured in Pascal Seconds. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Dynamic_Viscosity(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the dynamic viscosity. Default materials assumed that it is measured in Pascal Seconds. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Dynamic_Viscosity(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for kinematic viscosity. Default materials assumed that it is measured in Stokes. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Kinematic_Viscosity(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the kinematic viscosity. Default materials assumed that it is measured in Stokes. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Kinematic_Viscosity(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Setter for the gas constant. Default materials assumed that it is measured in metre / second. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Material_Set_Speed_of_Sound(
    TgPH_MATERIAL_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the gas constant. Default materials assumed that it is measured in metre / second. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Material_Query_Speed_of_Sound(
    TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_MATERIAL_ID_C ARG1 );

/** @} TGS_PHYSICS_MATERIAL */




/* -- Mass ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_MASS */
/** @{ */

/** @brief Clear the mass structure.
    @param [out] OUT0 Pointer to a mass data structure that is cleared. */
TgEXTN TgVOID 
tgPH_Mass_Reset(
    STg2_PH_Mass_PCU OUT0 );

/** @brief Update the mass structure mass related values. @return Result Code.
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Form identifier.
    @param [in] ARG2 Enumeration selecting the primitive type to use for the Tensor of Inertia.
    @param [in] ARG3 Pointer to primitive data. */
TgEXTN TgRESULT
tgPH_Mass_Set_Mass(
    STg2_PH_Mass_PC INOUT0, TgFLOAT32_C ARG1, ETgPM_SHORT ARG2, UTg2_CO_Primitive_F32_04_P ARG3 );

/** @} TGS_PHYSICS_MASS */




/* -- Form ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_FORM */
/** @{ */

/*                                                                                                                                                           Form -- Configuration */
/** @addtogroup TGS_PHYSICS_FORM_CONFIGURATION */
/** @{ */

/** @brief Enable the Form for World Collision (without a Body). Does nothing if attached to a Body. @return Result Code.
    @param [in] ARG0 UID for the Form to be set.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Form_Set_World_Collision(
    TgPH_FORM_ID_C ARG0, TgBOOL_C ARG1 ); 

/** @brief Retrieve the category bits assigned to this Form. @return Result Code.
    @param [out] OUT0 Pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_World_Collision(
     TgBOOL_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Setter for the category bits assigned to this Form. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Form to be set.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Form_Set_Category(
    TgPH_FORM_ID_C ARG0, TgUINT_E64_C ARG1 ); 

/** @brief Retrieve the category bits assigned to this Form. @return Result Code.
    @param [out] OUT0 Pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Category(
     TgUINT_E64_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Setter for the collision bits assigned to this Form. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Form_Set_Collide(
    TgPH_FORM_ID_C ARG0, TgUINT_E64_C ARG1 );

/** @brief Retrieve the collision bits assigned to this Form. @return Result Code.
    @param [out] OUT0 Pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Collide(
    TgUINT_E64_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Setter for the material UID. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Form_Set_Material_ID(
    TgPH_FORM_ID_C ARG0, TgPH_MATERIAL_ID_C ARG1 );

/** @brief Retrieve the material UID. @return Result Code.
    @param [out] OUT0 Pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Material_ID(
    TgPH_MATERIAL_ID_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Setter for the material UID. Calls are deferred to the end of the world step.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 Enumeration selecting the primitive type in ARG2.
    @param [in] ARG2 Pointer to primitive data. */
TgEXTN TgRESULT
tgPH_Form_Set_Collision_Primitive(
    TgPH_FORM_ID_C ARG0, ETgPM_SHORT_C ARG1, UTg2_CO_Primitive_F32_04_CPC ARG2 );

/** @brief Retrieve the primitive type of the Form. @return Result Code.
    @param [out] OUT0 Pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Primitive(
    ETgPM_SHORT_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Retrieve the primitive data of the Form. @return Result Code.
    @param [out] OUT0 Pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Primitive_Data(
    UTg2_CO_Primitive_F32_04_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Retrieve the body UID associated with this Form. @return Result Code.
    @param [out] OUT0 Pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Body_ID(
    TgPH_BODY_ID_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Retrieve the next Form in the link list for the assigned body. @return Result Code.
    @param [out] OUT0 Pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Next_Form_ID(
    TgPH_FORM_ID_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Setter for the spacial partitioning UID. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Form_Set_Sweep_ID(
    TgPH_FORM_ID_C ARG0, TgPARTITION_OBJECT_ID_C ARG1 );

/** @brief Retrieve the spacial partitioning UID. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Sweep_ID(
    TgPARTITION_OBJECT_ID_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @} TGS_PHYSICS_FORM_CONFIGURATION */


/*                                                                                                                                                              Form -- Scene Data */
/** @addtogroup TGS_PHYSICS_FORM_SCENE */
/** @{ */

/** @brief Setter for Form position in parent Body space. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Form_Set_Position_B(
    TgPH_FORM_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the Form position in parent Body space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Position_B(
    TgVEC_F32_04_1_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Setter for Form rotation in parent Body space. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Form_Set_Rotation_B(
    TgPH_FORM_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the Form rotation in parent Body space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Rotation_B(
    TgVEC_F32_04_1_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Setter for Form scale in Origin space. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Form_Set_Scale(
    TgPH_FORM_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the Form scale in Origin space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Scale(
    TgVEC_F32_04_1_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Retrieve the final transform in Body space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Final_Transform_B(
    TgVEC_F32_04_3_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Retrieve the Form's AABB in Origin space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_AABB_O(
    TgBOXAA_F32_04_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Retrieve the previous translation in World space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Last_Position_W(
    TgVEC_F32_04_1_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Retrieve the translation in World space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Position_W(
    TgVEC_F32_04_1_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Retrieve the final transform in World space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Final_Transform_W(
    TgVEC_F32_04_3_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Retrieve the Form's AABB in World space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_AABB_W(
    TgBOXAA_F32_04_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 );

/** @} TGS_PHYSICS_FORM_SCENE */


/*                                                                                                                                                           Form -- Miscellaneous */
/** @addtogroup TGS_PHYSICS_FORM_MISCELLANEOUS */
/** @{ */

/** @brief Setter for Form debug colour. Calls are deferred to the end of the world step. . @return Result Code.
    @param [in] ARG0 UID for the Form to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Form_Set_Colour(
    TgPH_FORM_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );
    
/** @brief Retrieve the Form debug colour. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Form to be queried. */
TgEXTN TgRESULT
tgPH_Form_Query_Colour(
    TgVEC_F32_04_1_PC TgANALYSIS_NO_NULL OUT0, TgPH_FORM_ID_C ARG1 ); // Debug Colour

#if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
/** @brief Display the Physics Performance Stats Page/Display.
    @param [in] ARG0 contains pointers to the data structures required by the Kernel GPU for Debug Rendering.
    @param [in] ARG1 Pointer to a data structure describing the Render Target buffers. */
TgEXTN TgVOID
tgPH_Debug_Render_Performance_Stats(
    STg2_KN_GPU_CMD_PC ARG0, STg2_KN_GPU_Render_Buffer_CPC TgANALYSIS_NO_NULL ARG1 );

/** @brief Visualize all of the Forms in a World through Debug Rendering.
    @param [in] ARG0 contains pointers to the data structures required by the Kernel GPU for Debug Rendering.
    @param [in] ARG1 Pointer to a configured Kernel Debug Render Model data structure.
    @param [in] ARG2 UID for the World to be drawn.
    @param [in] ARG3 Enumeration selecting the Render Target format.
    @param [in] ARG4 Enumeration selecting the Depth Stencil format. */
TgEXTN TgVOID
tgPH_Form_Visualize_Render(
     STg2_KN_GPU_CMD_PC ARG0, STg2_KN_GPU_DBG_Geom_PC TgANALYSIS_NO_NULL ARG1, TgPH_WORLD_ID_C ARG2, ETgKN_GPU_EXT_FORMAT_C ARG3, ETgKN_GPU_EXT_FORMAT_C ARG4 );
/*# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
/** @} TGS_PHYSICS_FORM_MISCELLANEOUS */

/** @} TGS_PHYSICS_FORM */


/* -- Body ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_BODY */
/** @{ */

/*                                                                                                                                                   Body -- Forms and Constraints */
/** @addtogroup TGS_PHYSICS_BODY_FORM_CONSTRAINT */
/** @{ */

/** @brief Associates this Form with a body at a specific position, rotation and with the designated mass. Calls are deferred to the end of the world step. 
    @param [in] ARG0 Body UID.
    @param [in] ARG1 Form UID.
    @param [in] ARG2 Pointer to a mass structure for the Form in the Form's frame of reference. */
TgEXTN TgVOID
tgPH_Body_Add_Form(
    TgPH_BODY_ID_C ARG0, TgPH_FORM_ID_C ARG1, STg2_PH_Mass_CPC ARG2 );

/** @brief Associates this Form with a body at a specific position, rotation and with the designated mass. Calls are deferred to the end of the world step. 
    @param [in] ARG0 Body UID.
    @param [in] ARG1 Form UID.
    @param [in] ARG2 Pointer to a mass structure for the Form in the Form's frame of reference. */
TgEXTN TgVOID
tgPH_Body_Remove_Form(
    TgPH_BODY_ID_C ARG0, TgPH_FORM_ID_C ARG1, STg2_PH_Mass_CPC ARG2 );

/** @brief Return the first Form (in the linked list) associated with this body.
    @param [out] OUT0 Pointer to the output value.
    @param [in] ARG1 Body UID.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_First_Form_ID(
    TgPH_FORM_ID_PC TgANALYSIS_NO_NULL OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Return the first constraint (in the linked list) associated with this body.
    @param [out] OUT0 Pointer to the output value.
    @param [in] ARG1 Body UID.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_First_Constraint_ID(
    TgPH_CONSTRAINT_ID_PC TgANALYSIS_NO_NULL OUT0, TgPH_BODY_ID_C ARG1 );

/** @} TGS_PHYSICS_BODY_FORM_CONSTRAINT */


/*                                                                                                                                                                    Body -- Mass */
/** @addtogroup TGS_PHYSICS_BODY_MASS */
/** @{ */

/** @brief Retrieve the Body's Moment of Inertia. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Moment_Of_Inertia(
    TgVEC_F32_04_3_PC TgANALYSIS_NO_NULL OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Retrieve the Body's Inerse Moment of Inertia. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Inverse_Moment_Of_Inertia(
    TgVEC_F32_04_3_PC TgANALYSIS_NO_NULL OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Retrieve the Body's Centre of Gravity. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Centre_Of_Gravity(
    TgVEC_F32_04_1_PC TgANALYSIS_NO_NULL OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Retrieve the Body's Mass. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Mass(
    TgVEC_F32_04_1_PC TgANALYSIS_NO_NULL OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Retrieve the Body's Inverse Mass. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Inverse_Mass(
    TgVEC_F32_04_1_PC TgANALYSIS_NO_NULL OUT0, TgPH_BODY_ID_C ARG1 );

/** @} TGS_PHYSICS_BODY_MASS */

/*                                                                                                                                                              Body -- Scene Data */
/** @addtogroup TGS_PHYSICS_BODY_SCENE_DATA */
/** @{ */

/** @brief Retrieve the Body's previous position in World Space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Last_Position_W(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Setter for Body's position in World space. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Body_Set_Position_W(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the Body's position in World Space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Position_W(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Setter for Body's rotation in World space. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Body_Set_Rotation_W(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the Body's rotation in World Space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Rotation_W(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Retrieve the Body's final transform in World Space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Final_Transform_W(
    TgVEC_F32_04_3_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @} TGS_PHYSICS_BODY_SCENE_DATA */

/*                                                                                                                                                                   Body -- Force */
/** @addtogroup TGS_PHYSICS_BODY_FORCE */
/** @{ */

/** @brief Increase the linear velocity in World Space of the body. Will BREAK the simulation. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is a homogeneous vector used to set the linear velocity of the body. */
TgEXTN TgRESULT
tgPH_Body_Add_Linear_Velocity(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Set the linear velocity in World Space of the body. Will BREAK the simulation. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is a homogeneous vector used to set the linear velocity of the body. */
TgEXTN TgRESULT
tgPH_Body_Set_Linear_Velocity(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );
    
/** @brief Retrieve the Body's linear velocity in World Space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Linear_Velocity(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Set the drag co-efficient (a percentage reduction of the body's velocity). Calls are deferred to the end of the world step.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 floating point in the interval [0..1]. */
TgEXTN TgVOID
tgPH_Body_Apply_Drag(
    TgPH_BODY_ID_C ARG0, TgFLOAT32_C ARG1 ); /**< Apply a constant drag to both velocities. */

/** @brief Apply a force at the given location in World Space to the body. Calls are deferred to the end of the world step.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 Force vector to be applied.
    @param [in] ARG2 Location where the force is applied in body space. */
TgEXTN TgVOID
tgPH_Body_Add_Force_At_Location(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1, TgVEC_F32_04_1_C ARG2 );

/** @brief Apply a force in World Space to the body (assumed to be applied through the centre of gravity). Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is a vector of the applied force. */
TgEXTN TgRESULT
tgPH_Body_Add_Force(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the Body's current non-persistent accumulation of forces in World Space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Force(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Add a force in World Space to the accumulated forces applied automatically every world step. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is a vector of the applied force. */
TgEXTN TgRESULT
tgPH_Body_Add_Persistent_Force(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Set the accumulator of forces applied automatically every world step. Will BREAK the simulation. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is a homogeneous vector used to set the accumulator. */
TgEXTN TgRESULT
tgPH_Body_Set_Persistent_Force(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the Body's accumulation of forces in World Space that are automatically applied every world step. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Persistent_Force(
    TgVEC_F32_04_1_PC TgANALYSIS_NO_NULL OUT0, TgPH_BODY_ID_C ARG1 );

/** @} TGS_PHYSICS_BODY_FORCE */

/*                                                                                                                                                              Body -- Torque(て) */
/** @addtogroup TGS_PHYSICS_BODY_TORQUE */
/** @{ */

/** @brief Increase the angular velocity in World Space of the body. Will BREAK the simulation. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is a homogeneous vector used to set the linear velocity of the body. */
TgEXTN TgRESULT
tgPH_Body_Add_Angular_Velocity(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Set the angular velocity in World Space of the body. Will BREAK the simulation. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is a homogeneous vector used to set the linear velocity of the body. */
TgEXTN TgRESULT
tgPH_Body_Set_Angular_Velocity(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );
    
/** @brief Retrieve the Body's angular velocity in World Space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Angular_Velocity(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Apply a torque in World Space to the body. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is a vector of the applied force. */
TgEXTN TgRESULT
tgPH_Body_Add_Torque(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the Body's current non-persistent accumulation of torques in World Space. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Torque(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Add a torque in World Space to the accumulated torques applied automatically every world step. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is a vector of the applied force. */
TgEXTN TgRESULT
tgPH_Body_Add_Persistent_Torque(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Set the accumulator of torques applied automatically every world step. Will BREAK the simulation. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is a homogeneous vector used to set the accumulator. */
TgEXTN TgRESULT
tgPH_Body_Set_Persistent_Torque(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );
    
/** @brief Retrieve the Body's accumulation of torques in World Space that are automatically applied every world step. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Persistent_Torque(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @} TGS_PHYSICS_BODY_TORQUE */

/*                                                                                                                                                              Body -- Simulation */
/** @addtogroup TGS_PHYSICS_BODY_SIMULATION */
/** @{ */

/** @brief Scale vector used as a multiplier to the force field applied to the body. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Body_Set_Force_Field_Factor(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the Body's force field multiplier. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Force_Field_Factor(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Scale vector in the range [0..1] used to scale non-contact forces and torques (see bullet time). Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Body_Set_Time_Factor(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the Body's time multiplier. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Time_Factor(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Floating-point value broadcast used to count down until a body will be auto-disabled. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Body_Set_Disable_Timer(
    TgPH_BODY_ID_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Retrieve the amount of time remaining before the Body's auto-disables. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Disable_Timer(
    TgFLOAT32_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Retrieve the enabled status of the Body. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Update(
    TgBOOL_PC TgANALYSIS_NO_NULL OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Retrieve the indicator marking if this Body is part of a ragdoll. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Ragdoll(
    TgBOOL_PC TgANALYSIS_NO_NULL OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Setter for the Body's function to calculate forces and moments. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Body_Set_CalcFM_FCN(
    TgPH_BODY_ID_C ARG0, TgPH_FCN_CALCFM_C ARG1 );

/** @brief Retrieve the Body's function to calculate forces and moments. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_CalcFM_FCN(
    TgPH_FCN_CALCFM_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Setter for the Body's function to filter or modify a contact. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Body_Set_Contact_FCN(
    TgPH_BODY_ID_C ARG0, TgPH_FCN_CONTACT_C ARG1 );

/** @brief Retrieve the Body's function to filter or modify a contact. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Contact_FCN(
    TgPH_FCN_CONTACT_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Setter for the Body's function called when the Body has moved. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Body_Set_Moved_FCN(
    TgPH_BODY_ID_C ARG0, TgPH_FCN_MOVED_C ARG1 );

/** @brief Retrieve the Body's function that is called when the Body has moved. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Moved_FCN(
    TgPH_FCN_MOVED_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Setter for the Body's context used when calling user set functions. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Body_Set_Context(
    TgPH_BODY_ID_C ARG0, TgUINT_PTR_C ARG1 );

/** @brief Retrieve the Body's context used when calling user set functions. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Body_Query_Context(
    TgUINT_PTR_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @} TGS_PHYSICS_BODY_SIMULATION */

/** @} TGS_PHYSICS_BODY */


/* -- Motor ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_MOTOR */
/** @{ */

/** @} TGS_PHYSICS_MOTOR */




/* -- Constraint ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_CONSTRAINT */
/** @{ */

/*                                                                                                                                                      Constraint - Configuration */
/** @addtogroup TGS_PHYSICS_CONSTRAINT_CONFIGURATION */
/** @{ */

/** @brief Used to configuration a new Constraint created through tgPH_Constraint_Init. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Constraint to be queried.
    @param [in] ARG1 Pointer to a configuration data structure. */
TgEXTN TgRESULT
tgPH_Constraint_Configure(
     TgPH_CONSTRAINT_ID_C ARG0, STg2_PH_Constraint_Configuration_CPC ARG1 );

/** @brief Retrieve the first Body ID associated with this Constraint. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Constraint to be queried. */
TgEXTN TgRESULT
tgPH_Constraint_Query_Body_0_ID(
     TgPH_BODY_ID_PC TgANALYSIS_NO_NULL OUT0, TgPH_CONSTRAINT_ID_C ARG1 );

/** @brief Retrieve the second Body ID associated with this Constraint. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Constraint to be queried. */
TgEXTN TgRESULT
tgPH_Constraint_Query_Body_1_ID(
     TgPH_BODY_ID_PC TgANALYSIS_NO_NULL OUT0, TgPH_CONSTRAINT_ID_C ARG1 );

/** @brief Retrieve the maximum amount of compressive force prior to breakage of the Constraint. Conceptually the applied force is to push the bodies apart. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Constraint to be queried. */
TgEXTN TgRESULT
tgPH_Constraint_Query_Breakable_Compressive_Force(
     TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_CONSTRAINT_ID_C ARG1 );

/** @brief Retrieve the maximum amount of extension force prior to breakage of the Constraint. Conceptually the applied force is to pull the bodies together. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Constraint to be queried. */
TgEXTN TgRESULT
tgPH_Constraint_Query_Breakable_Extension_Force(
     TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_CONSTRAINT_ID_C ARG1 );

/** @brief Retrieve the maximum torque (て) prior to breakage of the Constraint. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Constraint to be queried. */
TgEXTN TgRESULT
tgPH_Constraint_Query_Breakable_Max_Torque(
     TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_CONSTRAINT_ID_C ARG1 );

/** @brief Retrieve the static coefficient of friction (μs) of the Constraint. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Constraint to be queried. */
TgEXTN TgRESULT
tgPH_Constraint_Query_Static_Coefficient_of_Friction(
     TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_CONSTRAINT_ID_C ARG1 );

/** @brief Retrieve the dynamic coefficient of friction (μd) of the Constraint. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Constraint to be queried. */
TgEXTN TgRESULT
tgPH_Constraint_Query_Dynamic_Coefficient_of_Friction(
     TgFLOAT32_PC TgANALYSIS_NO_NULL OUT0, TgPH_CONSTRAINT_ID_C ARG1 );

/** @brief Setter that controls whether the Constraint will "break" when reaching a specified maximum force. Calls are deferred to the end of the world step. @return Result Code.
    @param [in] ARG0 UID for the Body to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Constraint_Set_Breakable(
    TgPH_CONSTRAINT_ID_C ARG0, TgBOOL_C ARG1 );

/** @brief Retrieve the breakable status of the Constraint. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Constraint to be queried. */
TgEXTN TgRESULT
tgPH_Constraint_Query_Breakable(
     TgBOOL_PC TgANALYSIS_NO_NULL OUT0, TgPH_CONSTRAINT_ID_C ARG1 );

/** @} TGS_PHYSICS_CONSTRAINT_CONFIGURATION */

/*                                                                                                                                                            Constraint - Utility */
/** @addtogroup TGS_PHYSICS_CONSTRAINT_UTILITY */
/** @{ */

/** @brief Test to determine if two Bodies are already connected through a Constraint. @return Result Code.
    @param [out] ARG0 UID for the Body to be tested.
    @param [in] ARG1 UID for the Body to be tested. */
TgEXTN TgBOOL
tgPH_Constraint_Query_Connected(
    TgPH_BODY_ID_C ARG0, TgPH_BODY_ID_C ARG1 );

/** @brief Retrieve the next Constraint associated with Body 0 of this Constraint. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Constraint_Query_Next_Constraint_ID_For_Body_0(
    TgPH_CONSTRAINT_ID_PC TgANALYSIS_NO_NULL OUT0, TgPH_CONSTRAINT_ID_C ARG1 );

/** @brief Retrieve the next Constraint associated with Body 1 of this Constraint. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Body to be queried. */
TgEXTN TgRESULT
tgPH_Constraint_Query_Next_Constraint_ID_For_Body_1(
    TgPH_CONSTRAINT_ID_PC TgANALYSIS_NO_NULL OUT0, TgPH_CONSTRAINT_ID_C ARG1 );

/** @} TGS_PHYSICS_CONSTRAINT_UTILITY */
/** @} TGS_PHYSICS_CONSTRAINT */




/* -- Rag Doll ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_RAGDOLL */
/** @{ */
/*                                                                                                                                                         Ragdoll - Configuration */
/** @addtogroup TGS_PHYSICS_RAGDOLL_CONFIGURATION */
/** @{ */

/** @brief Setter for the owning Context of this Ragdoll. Calls are deferred to the end of the world step. . @return Result Code.
    @param [in] ARG0 UID for the Ragdoll to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_Ragdoll_Set_Context(
    TgPH_RAGDOLL_ID_C ARG0, TgUINT_PTR_C ARG1 ); 

/** @brief Retrieve the owning Context for this Ragdoll. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Ragdoll to be queried. */
TgEXTN TgRESULT
tgPH_Ragdoll_Query_Context(
    TgUINT_PTR_PC OUT0, TgPH_RAGDOLL_ID_C ARG1 );

/** @brief Retrieve the number of bones for this Ragdoll. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Ragdoll to be queried. */
TgEXTN TgRESULT
tgPH_Ragdoll_Query_Number_Of_Bones(
     TgRSIZE_PC TgANALYSIS_NO_NULL OUT0, TgPH_RAGDOLL_ID_C ARG1 );

/** @} TGS_PHYSICS_RAGDOLL_CONFIGURATION */

/*                                                                                                                                                          Ragdoll - Ragdoll Bone */
/** @addtogroup TGS_PHYSICS_RAGDOLL_BONE */
/** @{ */

/** @brief Retrieve the position of the bone in the Ragdoll reference frame. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Ragdoll to be queried.
    @param [in] ARG2 Integer index for the selected bone. */
TgEXTN TgRESULT
tgPH_Ragdoll_Query_Bone_Position_R(
     TgVEC_F32_04_1_PC TgANALYSIS_NO_NULL OUT0, TgPH_RAGDOLL_ID_C ARG1, TgRSIZE_C ARG2 );

/** @brief Retrieve the final transform of the bone in the Ragdoll reference frame. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Ragdoll to be queried.
    @param [in] ARG2 Integer index for the selected bone. */
TgEXTN TgRESULT
tgPH_Ragdoll_Query_Bone_Final_Transform_R(
    TgVEC_F32_04_3_PC OUT0, TgPH_RAGDOLL_ID_C ARG1, TgRSIZE_C ARG2 );

/** @brief Retrieve the associated animation skeleton parent bone index for this bone. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Ragdoll to be queried.
    @param [in] ARG2 Integer index for the selected bone. */
TgEXTN TgRESULT
tgPH_Ragdoll_Query_Bone_Skeleton_Parent_Index(
     TgUINT_E32_PC TgANALYSIS_NO_NULL OUT0, TgPH_RAGDOLL_ID_C ARG1, TgRSIZE_C ARG2 );

/** @brief Retrieve the associated animation skeleton bone index for this bone. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Ragdoll to be queried.
    @param [in] ARG2 Integer index for the selected bone. */
TgEXTN TgRESULT
tgPH_Ragdoll_Query_Bone_Skeleton_Index(
    TgUINT_E32_PC OUT0, TgPH_RAGDOLL_ID_C ARG1, TgRSIZE_C ARG2 );

/** @brief Retrieve the Form ID associated with this bone. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Ragdoll to be queried.
    @param [in] ARG2 Integer index for the selected bone. */
TgEXTN TgRESULT
tgPH_Ragdoll_Query_Bone_Form_ID(
    TgPH_FORM_ID_PC OUT0, TgPH_RAGDOLL_ID_C ARG1, TgRSIZE_C ARG2 );

/** @brief Retrieve the Body ID associated with this bone. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Ragdoll to be queried.
    @param [in] ARG2 Integer index for the selected bone. */
TgEXTN TgRESULT
tgPH_Ragdoll_Query_Bone_Body_ID(
     TgPH_BODY_ID_PC TgANALYSIS_NO_NULL OUT0, TgPH_RAGDOLL_ID_C ARG1, TgRSIZE_C ARG2 );

/** @brief Retrieve the Constraint ID associated with this bone. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Ragdoll to be queried.
    @param [in] ARG2 Integer index for the selected bone. */
TgEXTN TgRESULT
tgPH_Ragdoll_Query_Bone_Constraint_ID(
    TgPH_CONSTRAINT_ID_PC OUT0, TgPH_RAGDOLL_ID_C ARG1, TgRSIZE_C ARG2 );

/** @brief Retrieve the Motor ID associated with this bone. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the Ragdoll to be queried.
    @param [in] ARG2 Integer index for the selected bone. */
TgEXTN TgRESULT
tgPH_Ragdoll_Query_Bone_Motor_ID(
     TgPH_MOTOR_ID_PC TgANALYSIS_NO_NULL OUT0, TgPH_RAGDOLL_ID_C ARG1, TgRSIZE_C ARG2 );

/** @} TGS_PHYSICS_RAGDOLL_BONE */
/** @} TGS_PHYSICS_RAGDOLL */




/* -- Scene ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_SCENE */
/** @{ */

/** @} TGS_PHYSICS_SCENE */




/* -- World ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_WORLD */
/** @{ */

/** @brief Return the world id associated with the given enumerated value. 
    @param [in] ARG0 Enumeration value selecting the world id.
    @return The world id associated with the enumeration value or the invalid world id otherwise. */
TgEXTN TgPH_WORLD_ID
tgPH_World_Query_World_Id(
    ETgPH_WORLD_C ARG0 );

/*                                                                                                                                                       World - Job Configuration */
/** @addtogroup TGS_PHYSICS_WORLD_JOB_CONFIGURATION */
/** @{ */

/** @brief Setter for the minimum number of bodies expected per simulation batch job for this World. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Simulation_Min_Batch_Size(
    TgPH_WORLD_ID_C ARG0, TgRSIZE_C ARG1 );

/** @brief Retrieve the minimum number of bodies expected per simulation batch job for this World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Simulation_Min_Batch_Size(
    TgRSIZE_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief Setter for the minimum number of bodies expected per collision batch job for this World. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Collision_Min_Batch_Size(
    TgPH_WORLD_ID_C ARG0, TgRSIZE_C ARG1 );

/** @brief Retrieve the minimum number of bodies expected per collision batch job for this World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Collision_Min_Batch_Size(
    TgRSIZE_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief Setter for the minimum number of bodies expected per solver job for this World. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Minimum_Bodies_Per_Solver_Job(
    TgPH_WORLD_ID_C ARG0, TgRSIZE_C ARG1 );

/** @brief Retrieve the minimum number of bodies expected per solver job for this World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Minimum_Bodies_Per_Solver_Job(
    TgRSIZE_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief Setter for the minimum number of degrees of freedom to be solved per solver job for this World. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Minimum_DoF_Per_Solver_Job(
    TgPH_WORLD_ID_C ARG0, TgRSIZE_C ARG1 );

/** @brief Retrieve the minimum number of degrees of freedom to be solved per solver job for this World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Minimum_DoF_Per_Solver_Job(
    TgRSIZE_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief Setter for the number of iterations done during solving (assuming an iterative approach to the solver) for this World. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Solver_Iterations(
    TgPH_WORLD_ID_C ARG0, TgRSIZE_C ARG1 );

/** @brief Retrieve the number of iterations done during solving (assuming an iterative approach to the solver) for this World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Solver_Iterations(
    TgRSIZE_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @} TGS_PHYSICS_WORLD_JOB_CONFIGURATION */

/*                                                                                                                                                World - Simulation Configuration */
/** @addtogroup TGS_PHYSICS_WORLD_SIMULATION_CONFIGURATION */
/** @{ */

/** @brief Setter for the time step used in the World time step. Try to NEVER call this after setting it during application bring up. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Fixed_Time_Step(
    TgPH_WORLD_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the time step amount for the World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Fixed_Time_Step(
    TgVEC_F32_04_1_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief Setter for the default force field for the World (e.g. gravity). @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Force_Field(
    TgPH_WORLD_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the default force field for the World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Force_Field(
    TgVEC_F32_04_1_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief Setter that controls the allowable penetration depth to be auto-disabled for the World. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Threshold_Depth(
    TgPH_WORLD_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the allowable penetration depth to be auto-disabled for the World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Threshold_Depth(
    TgVEC_F32_04_1_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief Setter that controls the allowable linear velocity to be auto-disabled for the World. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Threshold_LV(
    TgPH_WORLD_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Retrieve the allowable linear velocity to be auto-disabled for the World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Threshold_LV(
    TgVEC_F32_04_1_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief Setter that controls the allowable angular velocity to be auto-disabled for the World. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Threshold_AV(
    TgPH_WORLD_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );
    
/** @brief Retrieve the allowable angular velocity to be auto-disabled for the World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Threshold_AV(
    TgVEC_F32_04_1_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @} TGS_PHYSICS_WORLD_SIMULATION_CONFIGURATION */

/*                                                                                                                                                          World - Debug Controls */
/** @addtogroup TGS_PHYSICS_WORLD_DEBUG_CONTROLS */
/** @{ */

/** @brief Setter that controls whether the World is paused. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Pause_State(
    TgPH_WORLD_ID_C ARG0, TgBOOL_C ARG1 );

/** @brief Retrieve the pause status of the World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Pause_State(
    TgBOOL_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief Setter that controls if a World will unpause for a single step. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Single_Step(
    TgPH_WORLD_ID_C ARG0, TgBOOL_C ARG1 );

/** @brief Retrieve the current status of the single step indicator for the World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Single_Step(
    TgBOOL_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief Setter that controls whether the World runs the simulation. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Simulation_Enable(
    TgPH_WORLD_ID_C ARG0, TgBOOL_C ARG1 );

/** @brief Retrieve the status of simulation execution for the World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Simulation_Enable(
    TgBOOL_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief Setter that controls whether the World runs collision (contact generation). @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Collision_Enable(
    TgPH_WORLD_ID_C ARG0, TgBOOL_C ARG1 );

/** @brief Retrieve the status of collision (contact generation) for the World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Collision_Enable(
    TgBOOL_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief Setter that controls whether the World is paused. @return Result Code.
    @param [in] ARG0 UID for the World to be manipulated.
    @param [in] ARG1 is the data to be used in the set function. */
TgEXTN TgRESULT
tgPH_World_Set_Collision_Simple_Override(
    TgPH_WORLD_ID_C ARG0, TgBOOL_C ARG1 );

/** @brief Retrieve the pause status of the World. @return Result Code.
    @param [out] OUT0 is a pointer to store the retrieved data.
    @param [in] ARG1 UID for the World to be queried. */
TgEXTN TgRESULT
tgPH_World_Query_Collision_Simple_Override(
    TgBOOL_PC OUT0, TgPH_WORLD_ID_C ARG1 );

/** @} TGS_PHYSICS_WORLD_DEBUG_CONTROLS */
/** @} TGS_PHYSICS_WORLD */




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Declares resource specific generic object management functions. 
    Resource/Object Types: Material, Form, Body, Constraint, Motor, Ragdoll, Scene, World */

#define __PARENT_FILE__ "TgS Physics.h"
#define ENABLE_RELOAD_GUARD
#include "TgS PHYSICS/TgS Physics - Object [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_PHYSICS_H

/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if !defined(T_STATIC)
#if defined(T_GLOBAL)
/** @brief Allocate a new object.
    @return An unique UID for a new object */
TgEXTN T_ID(TgPH_,_ID)
T_NAME(tgPH_,_Init)( TgVOID );
#else
/** @brief Allocate a new object in the world UID by ARG0.
    @param [in] ARG0 World Configuration UID.
    @return An unique UID for a new object */
TgEXTN T_ID(TgPH_,_ID)
T_NAME(tgPH_,_Init)(
    TgPH_WORLD_ID_C ARG0 );
#endif
/*# !defined(T_STATIC) */
#endif

/** @brief Reset the object identified by ARG0 and add it to the free list.
    @param [in] ARG0 [in] Resource UID
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
T_NAME(tgPH_,_Reset)(
    T_ID(TgPH_,_ID_C) ARG0 );

#if defined(T_GLOBAL)
/** @brief Return the current count of registered objects.
    @return The current count of registered material objects */
TgEXTN TgRSIZE
T_NAME(tgPH_,_Query_Count)( TgVOID );
#else
/** @brief Return the current count of registered objects in the world UID by ARG0.
    @param [in] ARG0 World Configuration UID.
    @return The current count of registered material objects */
TgEXTN TgRSIZE
T_NAME(tgPH_,_Query_Count)( 
    TgPH_WORLD_ID_C ARG0 );
#endif


/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* =============================================================================================================================================================================== */
/*# defined (TGS_PHYSICS_H) */
#endif
