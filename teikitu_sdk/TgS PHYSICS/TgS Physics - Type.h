/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Type.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_TYPE_H)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS Ring 3 - Type.h"


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Objects                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define __PARENT_FILE__ "TgS Physics - Type.h"
#define ENABLE_RELOAD_GUARD
#include "TgS PHYSICS/TgS Physics - Object [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_PHYSICS_TYPE_H




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* -- Material ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_UNION( STg2_PH_Material, )
{
    STg2_UT_ST__ST_Node                         m_sNode_Stack;
    struct
    {
        TgPH_MATERIAL_ID                            m_tiMaterial;
        TgFLOAT32                                   m_fDensity;
        TgFLOAT32                                   m_fHardness_Brinell;
        TgFLOAT32                                   m_fTensile_Strength_Ultimate;
        TgFLOAT32                                   m_fTensile_Strength_Yield;
        TgFLOAT32                                   m_fElongation_At_Break;
        TgFLOAT32                                   m_fModulus_Elasticity;
        TgFLOAT32                                   m_fPoisson_Ratio;
        TgFLOAT32                                   m_fShear_Modulus;
        TgFLOAT32                                   m_fThermal_Conductivity;
        TgFLOAT32                                   m_fThermal_Expansion;
        TgFLOAT32                                   m_fMelting_Temperature;
        TgFLOAT32                                   m_fBoiling_Temperature;
        TgFLOAT32                                   m_fVapour_Pressure;
        TgFLOAT32                                   m_fSurface_Tension;
        TgFLOAT32                                   m_fDynamic_Viscosity;
        TgFLOAT32                                   m_fKinematic_Viscosity;
        TgFLOAT32                                   m_fSpeed_of_Sound;
        TgFLOAT32                                   m_fPad;
    #if 0 != (176 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad[176 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif  
    };
};


/* -- Mass ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT( STg2_PH_Mass, )
{
    TgVEC_F32_04_3                              m_mMOI; /**< Moment of Inertia */
    TgVEC_F32_04_3                              m_mInv_MOI; /**< Inverse Moment of Inertia. */
    TgVEC_F32_04_1                              m_vCG; /**< Centre of gravity (mass). */
    TgUN_V128                                   m_uMass; /**< Mass value. */
    TgUN_V128                                   m_uInv_Mass; /**< Inverse mass value. */
};

/* -- Configuration -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_PH_Constraint_Configuration,)
{
    TgPH_BODY_ID                                m_tiBY0; /**< Identifier for the first body in the constraint. */
    TgPH_BODY_ID                                m_tiBY1; /**< Identifier for the second body in the constraint. */

    TgFLOAT32                                   m_fMin; /**< Lower Limit, Compression failure. */
    TgFLOAT32                                   m_fMax; /**< Upper Limit, Extension failure. */
    TgFLOAT32                                   m_fMax_Torque; /**< Upper Limit, Twist failure. */
    TgFLOAT32                                   m_fμs, m_fμd; /**< Static and Dynamic coefficients of friction. */

    ETgPH_CONSTRAINT                            m_enConstraint;

    TgUINT_E64                                  m_bBreakable : 1;
    TgUINT_E64                                  m_uiPad : 62;
};

/* -- Functions ------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

typedef TgVOID(*TgPH_FCN_CALCFM)( TgVEC_F32_04_1_P, TgVEC_F32_04_1_P, TgPH_BODY_ID_C, TgUINT_PTR_C, TgVEC_F32_04_1_C );
typedef TgVOID(*TgPH_FCN_CONTACT)( TgPH_BODY_ID_C, TgUINT_PTR_C, STg2_CO_Packet_F32_04_PCU );
typedef TgVOID(*TgPH_FCN_MOVED)( TgPH_BODY_ID_C, TgUINT_PTR_C );
typedef TgVOID(*TgPH_FCN_UPDATE_COLLISION_SCENE)( TgPH_WORLD_ID_C );

TgTYPE_MODIFIER_DEFAULT(TgPH_FCN_CALCFM);
TgTYPE_MODIFIER_DEFAULT(TgPH_FCN_CONTACT);
TgTYPE_MODIFIER_DEFAULT(TgPH_FCN_MOVED);
TgTYPE_MODIFIER_DEFAULT(TgPH_FCN_UPDATE_COLLISION_SCENE);


/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Objects                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_UNION(T_ID(TgPH_,_ID),)
{
    TgUINT_E64                                  m_uiKI;
    struct {
        TgUINT_E64                                  m_uiScene : KTgPH_OBJ_BIT__SCENE; /**< Scene Index. */
        TgUINT_E64                                  m_uiI : KTgPH_OBJ_BIT__MAX_INDEX; /**< Index identification of object within storage array. */
        TgUINT_E64                                  m_uiWorld : KTgPH_OBJ_BIT__WORLD; /**< World Index. */
        TgUINT_E64                                  m_uiK : KTgPH_OBJ_BIT__SALT; /**< Salt value to prevent ABA atomic issues. */
    };
};
TgTYPE_MODIFIER_ALL(T_ID(TgPH_,_ID));
TgKI_CUSTOM_DECLARE_AND_INLINE(T_ID(PH_,_ID))


/*# defined (ENABLE_RELOAD_GUARD) */
#endif


/* =============================================================================================================================================================================== */
/*# defined (TGS_PHYSICS_TYPE_H) */
#endif
