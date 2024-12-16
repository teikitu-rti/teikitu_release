/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Material.c
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
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Module_Material_Boot ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Module_Material_Boot( TgVOID )
{
    TgPH_MATERIAL_ID                    tiMat_Default;

    // Steel 1020, as rolled (reference: https://www.matweb.com/search/DataSheet.aspx?MatGUID=a2eed65d6e5e4b66b7315a1b30f4b391)
    tiMat_Default = tgPH_Material_Init();
    tgPH_Material_Set_Density( tiMat_Default, 7.87F ); // g/cc
    tgPH_Material_Set_Hardness_Brinell( tiMat_Default, 143 );
    tgPH_Material_Set_Tensile_Strength_Ultimate( tiMat_Default, 405E6F ); // Pa
    tgPH_Material_Set_Tensile_Strength_Yield( tiMat_Default, 330E6F ); // Pa
    tgPH_Material_Set_Elongation_At_Break( tiMat_Default, 0.15F );
    tgPH_Material_Set_Modulus_Elasticity( tiMat_Default, 186E9F ); // Pa
    tgPH_Material_Set_Poisson_Ratio( tiMat_Default, 0.29F );
    tgPH_Material_Set_Shear_Modulus( tiMat_Default, 72E9F );
    tgPH_Material_Set_Thermal_Expansion( tiMat_Default, 11.7F ); // µm/m°C
    tgPH_Material_Set_Thermal_Conductivity( tiMat_Default, 51.9F ); // W/mK
    tgPH_Material_Set_Melting_Temperature( tiMat_Default, 1515 );
    g_atiPH_Material_Default[ETgPH_MATERIAL__STEEL_1020] = tiMat_Default;

    // Aluminum 6061 (reference: https://asm.matweb.com/search/SpecificMaterial.asp?bassnum=ma6061t6)
    tiMat_Default = tgPH_Material_Init();
    tgPH_Material_Set_Density( tiMat_Default, 2.7F ); // g/cc
    tgPH_Material_Set_Hardness_Brinell( tiMat_Default, 95 );
    tgPH_Material_Set_Tensile_Strength_Ultimate( tiMat_Default, 310E6F );
    tgPH_Material_Set_Tensile_Strength_Yield( tiMat_Default, 276E6F ); // PSI
    tgPH_Material_Set_Elongation_At_Break( tiMat_Default, 0.12F );
    tgPH_Material_Set_Modulus_Elasticity( tiMat_Default, 68.9E9F ); // Pa
    tgPH_Material_Set_Poisson_Ratio( tiMat_Default, 0.33F );
    tgPH_Material_Set_Shear_Modulus( tiMat_Default, 26E9F );
    tgPH_Material_Set_Thermal_Expansion( tiMat_Default, 23.6F ); // µm/m°C
    tgPH_Material_Set_Thermal_Conductivity( tiMat_Default, 167 ); // W/mK
    tgPH_Material_Set_Melting_Temperature( tiMat_Default, 582 );
    g_atiPH_Material_Default[ETgPH_MATERIAL__ALUMINUM_6061] = tiMat_Default;

    // Water (reference: https://www.matweb.com/search/DataSheet.aspx?MatGUID=64a0e072a9ec430e92ed984c7131b690)
    tiMat_Default = tgPH_Material_Init();
    tgPH_Material_Set_Density( tiMat_Default, 0.99823F ); // g/cc
    tgPH_Material_Set_Thermal_Expansion( tiMat_Default, 0.207F ); // µm/m°C
    tgPH_Material_Set_Thermal_Conductivity( tiMat_Default, 598.4F ); // W/mK
    tgPH_Material_Set_Melting_Temperature( tiMat_Default, 0 );
    tgPH_Material_Set_Boiling_Temperature( tiMat_Default, 100 );
    tgPH_Material_Set_Vapour_Pressure( tiMat_Default, 0.023388F ); // bar
    tgPH_Material_Set_Surface_Tension( tiMat_Default, 72.75F ); // dynes/cm
    tgPH_Material_Set_Dynamic_Viscosity( tiMat_Default, 1.002F ); // Pa-s
    tgPH_Material_Set_Kinematic_Viscosity( tiMat_Default, 10040  ); // stokes
    tgPH_Material_Set_Speed_of_Sound( tiMat_Default, 1481 );
    g_atiPH_Material_Default[ETgPH_MATERIAL__WATER] = tiMat_Default;

    // Oxygen (reference: https://www.matweb.com/search/DataSheet.aspx?MatGUID=4529912ca0b74b4d945ef37121b9ef35)
    tiMat_Default = tgPH_Material_Init();
    tgPH_Material_Set_Density( tiMat_Default, 0.001308F ); // g/cc
    tgPH_Material_Set_Melting_Temperature( tiMat_Default, -218.79F );
    tgPH_Material_Set_Boiling_Temperature( tiMat_Default, -182.95F );
    tgPH_Material_Set_Vapour_Pressure( tiMat_Default, 0.1000F ); // bar @ °C
    g_atiPH_Material_Default[ETgPH_MATERIAL__OXYGEN] = tiMat_Default;
}


/* ---- tgPH_Material_Query_Default ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgPH_MATERIAL_ID tgPH_Material_Query_Default( ETgPH_MATERIAL_DEFAULT_C enMaterial )
{
    if (((TgSINT_E32)enMaterial >= (TgSINT_E32)ETgPH_MATERIAL__BEGIN) && ((TgSINT_E32)enMaterial < (TgSINT_E32)ETgPH_MATERIAL__END))
    {
        TgDIAG(KTgID__INVALID_VALUE != g_atiPH_Material_Default[enMaterial].m_uiKI);
        return (g_atiPH_Material_Default[enMaterial]);
    }
    else
    {
        return (KTgPH_MATERIAL_ID__INVALID);
    }
}


/* ---- tgPH_Material Accessors - Material Component ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Density,TgFLOAT32,m_fDensity)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Hardness_Brinell,TgFLOAT32,m_fHardness_Brinell)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Tensile_Strength_Ultimate,TgFLOAT32,m_fTensile_Strength_Ultimate)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Tensile_Strength_Yield,TgFLOAT32,m_fTensile_Strength_Yield)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Elongation_At_Break,TgFLOAT32,m_fElongation_At_Break)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Modulus_Elasticity,TgFLOAT32,m_fModulus_Elasticity)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Poisson_Ratio,TgFLOAT32,m_fPoisson_Ratio)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Shear_Modulus,TgFLOAT32,m_fShear_Modulus)


/* ---- tgPH_Material Accessors - Thermal Component ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Thermal_Conductivity,TgFLOAT32,m_fThermal_Conductivity)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Thermal_Expansion,TgFLOAT32,m_fThermal_Expansion)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Melting_Temperature,TgFLOAT32,m_fMelting_Temperature)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Boiling_Temperature,TgFLOAT32,m_fBoiling_Temperature)


/* ---- tgPH_Material Accessors - Fluid Component -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Vapour_Pressure,TgFLOAT32,m_fVapour_Pressure)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Surface_Tension,TgFLOAT32,m_fSurface_Tension)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Dynamic_Viscosity,TgFLOAT32,m_fDynamic_Viscosity)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Kinematic_Viscosity,TgFLOAT32,m_fKinematic_Viscosity)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__ASSIGN(Material,MATERIAL,Speed_of_Sound,TgFLOAT32,m_fSpeed_of_Sound)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Module_Material_Init_Internal --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Module_Material_Init_Internal( TgVOID )
{
    tgMM_Set_U08_0x00( g_atiPH_Material_Default, sizeof( g_atiPH_Material_Default ) );

    g_nuiPH_Material_Increase_Commit = 10;
    g_nuiPH_Material_Total_Commit = 0;
    g_nuiPH_Material_Total_Reserve = 100;
}


/* ---- tgPH_Material_Init_Do_Command ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Material_Init_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    typedef struct {
        TgPH_MATERIAL_ID tiID;
    } STg2_FCN_Command;
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };

    STg2_PH_Material_P                  psMaterial;

    TgPARAM_CHECK( sizeof( STg2_FCN_Command ) == nbyCommand_Buffer );
    (void)nbyCommand_Buffer;

    /* Acquire the body, assuming the identifier is still valid. */
    psMaterial = tgPH_Material_Get_Material_From_ID( uCMD.pCommand->tiID );

    if (nullptr == psMaterial)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Material ID submitted for reset." );
        return;
    };

    psMaterial->m_tiMaterial.m_uiKI = KTgID__INVALID_VALUE;
    psMaterial->m_fDensity = 0.0F;
    psMaterial->m_fHardness_Brinell = 0.0F;
    psMaterial->m_fTensile_Strength_Ultimate = 0.0F;
    psMaterial->m_fTensile_Strength_Yield = 0.0F;
    psMaterial->m_fElongation_At_Break = 0.0F;
    psMaterial->m_fModulus_Elasticity = 0.0F;
    psMaterial->m_fPoisson_Ratio = 0.0F;
    psMaterial->m_fShear_Modulus = 0.0F;
    psMaterial->m_fThermal_Conductivity = 0.0F;
    psMaterial->m_fThermal_Expansion = 0.0F;
    psMaterial->m_fMelting_Temperature = 0.0F;
    psMaterial->m_fBoiling_Temperature = 0.0F;
    psMaterial->m_fVapour_Pressure = 0.0F;
    psMaterial->m_fSurface_Tension = 0.0F;
    psMaterial->m_fDynamic_Viscosity = 0.0F;
    psMaterial->m_fKinematic_Viscosity = 0.0F;
    psMaterial->m_fSpeed_of_Sound = 0.0F;
}


/* ---- tgPH_Material_Reset_Do_Command ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Material_Reset_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    typedef struct {
        TgPH_MATERIAL_ID tiID;
    } STg2_FCN_Command;
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };

    STg2_PH_Material_P                  psMaterial;

    TgPARAM_CHECK( sizeof( STg2_FCN_Command ) == nbyCommand_Buffer );
    (void)nbyCommand_Buffer;

    TgDIAG(nullptr != uCMD.pCommand);

    /* Acquire the body, assuming the identifier is still valid. */
    psMaterial = tgPH_Material_Get_Material_From_ID( uCMD.pCommand->tiID );

    if (nullptr == psMaterial)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Material ID submitted for reset." );
        return;
    };

    /* Reset the data to zero or its equivalents. */

    tgMM_Set_U08_0x00( psMaterial, sizeof(STg2_PH_Material) );
    psMaterial->m_tiMaterial.m_uiKI = KTgID__INVALID_VALUE;

    tgCM_UT_LF__ST__Push( &g_asPH_Body_Free_Stack[uCMD.pCommand->tiID.m_uiWorld].m_sStack, &psMaterial->m_sStack_Node );
    TgSTD_ATOMIC(fetch_sub)( &g_xnuiPH_Material, 1 );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Debug Functions                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgBUILD_DEBUG__PHYSICS)

/* ---- tgPH_Material_Validate --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Material_Validate( STg2_Output_PC psOUT, TgPH_MATERIAL_ID_C tiMT )
{
    (void)psOUT;
    (void)tiMT;

}

/*# defined(TgBUILD_DEBUG__PHYSICS) */
#endif


