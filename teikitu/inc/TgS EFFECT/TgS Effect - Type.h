/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Type.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_EFFECT_TYPE_H)
#define TGS_EFFECT_TYPE_H
#pragma once

#include "TgS Ring 4 - Type.h"


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

typedef TgBOOL (*TgFCN_CB_ON_TERMINATE)( TgFX_CLIENT_INST_ID_C, TgUINT_PTR_C );
typedef TgVOID (*TgFCN_CB_ON_CONTACT)( TgFLOAT32_PCU, TgFX_CLIENT_INST_ID_C, TgUINT_PTR_C, TgVEC_F32_04_1 );


/* ---- Client ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_FX_Instance,)
{
    TgVEC_F32_04_1                              m_vPos_N2W; /**< Position relative to World Reference Frame */
    TgVEC_F32_04_1                              m_vNormal; /**< Surface Normal - Used when creating decals */
    TgVEC_F32_04_1                              m_vScale; /**< Scale in Object / Effect space */
    TgVEC_F32_04_1                              m_qRot_N2W; /**< Rotation relative to World Reference Frame */
    TgATTACHMENT_ID                             m_tiAttachment;
    TgFX_CLIENT_INST_ID                         m_tiParent;
    TgRN_TARGET_ID                              m_tiTarget;

    TgFCN_CB_ON_TERMINATE                       m_pfnTerminate; /**< Executed on client thread */
    TgUINT_PTR                                  m_uiTerminate_Parameter;
    TgFCN_CB_ON_CONTACT                         m_pfnContact; /**< Executed on client thread after a render thread contact event */
    TgUINT_PTR                                  m_uiContact_Parameter;

    TgSINT_E16                                  m_iPriority; /**< Zero is median priority */
    TgUINT_E16                                  m_uiInternal;
    TgBOOL                                      m_uiRender_Visible;
    TgUINT_E08                                  m_uiPad[3];
};


/* ---- Render ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#if defined(TgBUILD_FEATURE__GRAPHICS)
TgTYPE_STRUCT(STg2_FX_Rnd_Output,)
{
    /* Input: From Render to FX */

    TgUN_V128                                   m_uDT;
    STg2_KN_GPU_Camera_CP                       m_psCamera;

    /* Output: Buffers supplied from Render, and Filled by FX */

    TgRSIZE_P                                   m_puiContext_To_Particle_Header_Index;
    STg2_RN_Particle_Header_P                   m_psFX_Header;
    TgRSIZE_A                                   m_xnuiFX_Header; /**< May read as larger than max, but still limited to max */
    TgRSIZE                                     m_nuiFX_Header_Max;

    TgUINT_E08_P                                m_puiBuffer;
    TgRSIZE                                     m_nbyUsed;
    TgRSIZE                                     m_nbyFree;
};
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


/* ---- Effect Parameter --------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_FX_AnimData,)
{
    ETgFX_ANIM_DATA                             m_enType;
    TgUINT_E32                                  m_uiSize;
};

TgTYPE_STRUCT(STg2_FX_AnimData__Constant_UXX,)
{
    STg2_FX_AnimData                            m_sParam;
    TgUINT_E64                                  m_uiPad;
    TgUINT_MAX                                  m_uiVal;
};

TgTYPE_STRUCT(STg2_FX_AnimData__Constant_F32_04,)
{
    STg2_FX_AnimData                            m_sParam;
    TgUINT_E64                                  m_uiPad;
    TgVEC_F32_04_1                              m_vParam;
};

TgTYPE_STRUCT(STg2_FX_AnimData__Key_Frame,)
{
    STg2_FX_AnimData                            m_sParam;
    TgRSIZE                                     m_nuiKey_Frame;
    TgFLOAT32_P                                 m_pfTime;
};

TgTYPE_STRUCT(STg2_FX_AnimData__Key_Frame_F32_01,)
{
    STg2_FX_AnimData__Key_Frame                 m_sKey_Frame;
    TgFLOAT32_P                                 m_pfVal; ///< One data element per key frame.
};

TgTYPE_STRUCT(STg2_FX_AnimData__Key_Frame_F32_02,)
{
    STg2_FX_AnimData__Key_Frame                 m_sKey_Frame;
    TgFLOAT32_P                                 m_pfVal; ///< Two data element per key frame.
};

TgTYPE_STRUCT(STg2_FX_AnimData__Key_Frame_F32_03,)
{
    STg2_FX_AnimData__Key_Frame                 m_sKey_Frame;
    TgFLOAT32_P                                 m_pfVal; ///< Three data element per key frame.
};

TgTYPE_STRUCT(STg2_FX_AnimData__Key_Frame_F32_04,)
{
    STg2_FX_AnimData__Key_Frame                 m_sKey_Frame;
    TgVEC_F32_04_1_P                            m_pvVal; ///< One data element per key frame.
};

TgTYPE_STRUCT(STg2_FX_AnimData__Sinusoidal_F32,)
{
    STg2_FX_AnimData                            m_sParam;
    TgUINT_E64                                  m_uiPad;
    TgVEC_F32_04_1                              m_vAmplitude;
    TgVEC_F32_04_1                              m_vFrequency;
    TgVEC_F32_04_1                              m_vPhase;
};

TgTYPE_STRUCT(STg2_FX_AnimData__Square_F32,)
{
    STg2_FX_AnimData                            m_sParam;
    TgUINT_E64                                  m_uiPad;
    TgVEC_F32_04_1                              m_vAmplitude;
};

TgTYPE_STRUCT(STg2_FX_AnimData__Spline_F32,)
{
    STg2_FX_AnimData                            m_sParam;
};

TgTYPE_STRUCT(STg2_FX_AnimData__Flicker_F32,)
{
    STg2_FX_AnimData                            m_sParam;
    TgUINT_E64                                  m_uiPad;
    TgVEC_F32_04_1                              m_vMult_MID, m_vMult_RNG;
    TgVEC_F32_04_1                              m_vTime_MID, m_vTime_RNG;
};

TgTYPE_UNION(UTg2_FX_AnimData,)
{
    STg2_FX_AnimData_P                          psAnimData;
    STg2_FX_AnimData__Constant_UXX_P            psConstant_UXX;
    STg2_FX_AnimData__Constant_F32_04_P         psConstant_F32_04;
    STg2_FX_AnimData__Key_Frame_P               psKey_Frame;
    STg2_FX_AnimData__Key_Frame_F32_01_P        psKey_Frame_F32_01;
    STg2_FX_AnimData__Key_Frame_F32_02_P        psKey_Frame_F32_02;
    STg2_FX_AnimData__Key_Frame_F32_03_P        psKey_Frame_F32_03;
    STg2_FX_AnimData__Key_Frame_F32_04_P        psKey_Frame_F32_04;
    STg2_FX_AnimData__Sinusoidal_F32_P          psSinusoidal_F32;
    STg2_FX_AnimData__Square_F32_P              psSquare_F32;
    STg2_FX_AnimData__Spline_F32_P              psSpline_F32;
    STg2_FX_AnimData__Flicker_F32_P             psFlicker_F32;
};


/* ---- Effect Data - Beam ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Used to draw*/

TgTYPE_STRUCT(STg2_FX_Beam__File_Data,)
{
    /* Spawn Data */
    TgFLOAT32                                   m_fTime_Total_MID, m_fTime_Total_RNG; //< Mean and range for when an effect instance ends.
    TgFLOAT32                                   m_fTime_Start_End_MID, m_fTime_Start_End_RNG; //< Mean and range for when an effect instance goes to stead-state.
    TgFLOAT32                                   m_fTime_End_Start_MID, m_fTime_End_Start_RNG; //< Mean and range for when an effect instance starts a finish state.
    TgUINT_MAX                                  m_uiHash_Material; //< Render material name hash
    TgVEC_F32_04_1                              m_vEnd_Position_MID, m_vEnd_Position_RNG; //< Mean and range for a variance in the end position of the effect.
    TgVEC_F32_04_1                              m_vScale_U, m_vScale_V; //< UV Scale (U0, 0, U1, 0), (0, V0, 0, V1)

    /* Fixed Data */
    TgUINT_E32                                  m_uiSort_Order; //< Used to control sort ordering during the depth sort.
    TgUINT_E32                                  m_uiPad0;

    /* Shape Data */
    TgRSIZE                                     m_nuiPoints; //< There will be Points - 1 segments in the beam.
    union
    {
        struct /**< Written out in the data file */
        {
            TgUINT_PTR                                  m_uiShape_Colour;
            TgUINT_PTR                                  m_uiShape_Offset;
            TgUINT_PTR                                  m_uiShape_Width;
            TgUINT_PTR                                  m_uiShape_Fraction;
            TgUINT_PTR                                  m_uiShape_Normalized_T;
        }                                           m_sData_Offset;
        struct /**< Fixed up after load */
        {
            TgVEC_F32_04_1_P                            m_pvShape_Colour; //< F4 
            TgVEC_F32_04_1_P                            m_pvShape_Offset; //< F3 Homogeneous direction vector that is the offset (orthogonal to beam only) at fraction value.
            TgFLOAT32_P                                 m_pfShape_Width; //< F1 
            TgFLOAT32_P                                 m_pfShape_Fraction; //< F1 Percentage (distance) along the shape for each segment.
            TgFLOAT32_P                                 m_pfShape_Normalized_T; //< F1 Normalized [0..1] value used to mark/refer to this index.
        }                                           m_sData;
    }                                           m_sShape;

    /* Animation Data */
    TgRSIZE                                     m_nbyData;
    union
    {
        struct /**< Written out in the data file */
        {
            TgUINT_PTR                                  m_uiEnd_Position;
            TgUINT_PTR                                  m_uiSG0_SG1;
        }                                           m_sData_Offset;
        struct /**< Fixed up after load */
        {
            STg2_FX_AnimData_P                          m_psEnd_Position; //< F3 End position for the beam.
            STg2_FX_AnimData_P                          m_psSG0_SG1; //< F2 Percentage of the beam segment to start and the width, followed by the same for the end.
        }                                           m_sParameter;
        STg2_FX_AnimData_P                          m_apsList[4]; //< Animation describes how the parameters change over time (normalized).
    }                                           m_sAnim;
};


/* ---- Effect Data - Billboard -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Billboards are quads (or a render mesh) that self-align based on their configuration and the active camera. */

TgTYPE_STRUCT(STg2_FX_Billboard__File_Data,)
{
    /* Spawn Data */
    TgFLOAT32                                   m_fTime_Total_MID, m_fTime_Total_RNG; //< Mean and range for when an effect instance ends.
    TgFLOAT32                                   m_fTime_Start_End_MID, m_fTime_Start_End_RNG; //< Mean and range for when an effect instance goes to stead-state.
    TgFLOAT32                                   m_fTime_End_Start_MID, m_fTime_End_Start_RNG; //< Mean and range for when an effect instance starts a finish state.
    TgUINT_MAX                                  m_uiHash_Material; //< Render material name hash.
    TgVEC_F32_04_1                              m_vPivot_X, m_vPivot_Y; //*< Normalized pivot/root location of the billboard.
    TgVEC_F32_04_1                              m_vPlnX, m_vPlnY, m_vPlnZ; //< Billboard plane definition.
    TgVEC_F32_04_1                              m_vFade_Start, m_vFade_RNG; //<
    TgFLOAT32                                   m_fSpin_MID, m_fSpin_RNG; //< Random range for the spin (in plane rotation).
    TgFLOAT32                                   m_fSpin_Speed;

    /* Fixed Data */
    ETgFX_BILLBOARD_ORIENTATION                 m_enOrientation;
    TgUINT_E32                                  m_uiFlags;
    TgUINT_E32                                  m_uiSort_Order; //< Used to control sort ordering during the depth sort.
    TgUINT_E32                                  m_uiPad0;

    /* Animation Data */
    TgUINT_E32                                  m_nbyData;
    union
    {
        struct /**< Written out in the data file */
        {
            TgUINT_PTR                                  m_uiColour;
            TgUINT_PTR                                  m_uiSize;
        }                                           m_sData_Offset;
        struct /**< Fixed up after load */
        {
            STg2_FX_AnimData_P                          m_psColour; //< F4
            STg2_FX_AnimData_P                          m_psSize; //< F2
        }                                           m_sParameter;
        STg2_FX_AnimData_P                          m_apsList[2]; //< Animation describes how the parameters change over time (normalized).
    }                                           m_sAnim;
};


/* ---- Effect Data - Decal ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* Used to collect triangles from collision geometry so that they can be rendered with a new texture. Example: Bullet holes on a wall. */

TgTYPE_STRUCT(STg2_FX_Decal__File_Data,)
{
    /* Spawn Data */
    TgFLOAT32                                   m_fTime_Total_MID, m_fTime_Total_RNG; //< Mean and range for when an effect instance ends.
    TgFLOAT32                                   m_fTime_Start_End_MID, m_fTime_Start_End_RNG; //< Mean and range for when an effect instance goes to stead-state.
    TgFLOAT32                                   m_fTime_End_Start_MID, m_fTime_End_Start_RNG; //< Mean and range for when an effect instance starts a finish state.
    TgUINT_MAX                                  m_uiHash_Material; /**< Render material name hash */
    TgVEC_F32_04_1                              m_vSize_MID[2], m_vSize_RNG[2]; /**< Decal start size, and then final size */
    TgFLOAT32                                   m_fSpin_MID, m_fSpin_RNG; /**< Random range for the spin (in plane rotation) */

    /* Fixed Data */
    TgUINT_E32                                  m_uiSort_Order; /**< Used to control sort ordering during the depth sort */

    /* Animation Data */
    TgUINT_E32                                  m_nbyData;
    union
    {
        struct /**< Written out in the data file */
        {
            TgUINT_PTR                                  m_uiColour; /**< F4 */
        }                                           m_sData_Offset;
        struct /**< Fixed up after load */
        {
            STg2_FX_AnimData_P                          m_psColour; /**< F4 */
        }                                           m_sParameter;
        STg2_FX_AnimData_P                          m_apsList[1];
    }                                           m_sAnim;
    TgUINT_E64                                  m_uiPad0;
};


/* ---- Effect Data - Emitter ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Easiest real world example would be fireworks. Used when you want to have a location automatically generate a set of quads (particles) for a period of time. */

TgTYPE_STRUCT(STg2_FX_Particle__File_Data,)
{
    /* Spawn Data */
    TgVEC_F32_04_1                              m_vPivot_X, m_vPivot_Y; ///< Normalized pivot/root location of the particle.
    TgVEC_F32_04_1                              m_vL_Vel_Acceleration_W; ///< Additive to key frame velocity.

                                                /* Used for creating a per instance difference from the key frame data */
    TgVEC_F32_04_1                              m_vLVel_Variance_MID, m_vLVel_Variance_RNG;
    TgVEC_F32_04_1                              m_vRot_Variance_MID, m_vRot_Variance_RNG; ///< (Quat.xyzw,Spin.xxxx)
    TgVEC_F32_04_1                              m_vSize_Variance_MID, m_vSize_Variance_RNG;
    TgVEC_F32_04_1                              m_vRVel_Acceleration_MID, m_vRVel_Acceleration_RNG; ///< (Quat.xyzw,Spin.xxxx)
    TgFLOAT32                                   m_fTime_MID, m_fTime_RNG; ///< Random range for the life time of the particle.
    TgFLOAT32                                   m_fContact_Restitution_MID, m_fContact_Restitution_RNG;

    /* Fixed Data */
    ETgFX_PARTICLE_ORIENTATION                  m_enOrientation;
    TgUINT_E32                                  m_uiPad0;
    TgUINT_MAX                                  m_uiCollision_New_Effect_Hash;

    /* Animation Data */
    TgRSIZE                                     m_nbyData;
    TgRSIZE                                     m_uiPad1;
    union
    {
        struct /**< Written out in the data file */
        {
            TgUINT_PTR                                  m_uiPos_N;
            TgUINT_PTR                                  m_uiRot_N;
            TgUINT_PTR                                  m_uiLVel_N;
            TgUINT_PTR                                  m_uiSpin;
            TgUINT_PTR                                  m_uiTurbulence;
            TgUINT_PTR                                  m_uiSize;
            TgUINT_PTR                                  m_uiColour;
            TgUINT_PTR                                  m_uiNew_Effect_Hash;
        }                                           m_sData_Offset;
        struct /**< Fixed up after load */
        {
            STg2_FX_AnimData_P                          m_psPos_N; ///< F3: (x,y,z) Position transform from root to model reference frame - e.g. canned, single use animations.
            STg2_FX_AnimData_P                          m_psRot_N; ///< F3: (x,y,z) Rotation transform from root to model reference frame.
            STg2_FX_AnimData_P                          m_psLVel_N; ///< F3: (x,y,z) Velocity data in root reference frame. Acceleration will be computed real-time.
            STg2_FX_AnimData_P                          m_psSpin; ///< F1: (x) spin value of the particle quad.s
            STg2_FX_AnimData_P                          m_psTurbulence; ///< F3: Random jitter that is generated on a per-frame basis and added to the position of the particle.
            STg2_FX_AnimData_P                          m_psSize; ///< F2: (width,height) Size data of the particle quad.
            STg2_FX_AnimData_P                          m_psColour; ///< F4: (red,green,blue,alpha) in G10 P709 for the particle vertex colours.
            STg2_FX_AnimData_P                          m_psNew_Effect_Hash; ///< U64 Hash value of an effect to spawn.
        }                                           m_sParameter;
        STg2_FX_AnimData_P                          m_apsList[6];
    }                                           m_sAnim;
};


TgTYPE_STRUCT(STg2_FX_Emitter__File_Data,)
{
    /* Spawn Data */
    TgFLOAT32                                   m_fTime_Total_MID, m_fTime_Total_RNG; //< Mean and range for when an effect instance ends.
    TgFLOAT32                                   m_fTime_Start_End_MID, m_fTime_Start_End_RNG; //< Mean and range for when an effect instance goes to stead-state.
    TgFLOAT32                                   m_fTime_End_Start_MID, m_fTime_End_Start_RNG; //< Mean and range for when an effect instance starts a finish state.
    TgUINT_MAX                                  m_uiHash_Material; /**< Render material name hash */
    TgFLOAT32                                   m_fEmission_Pivot_X, m_fEmission_Pivot_Y;
    TgRSIZE                                     m_anuiEmission_Max_Particle[2]; /**< [Low(0), High(9)] Value Range */
    TgFLOAT32                                   m_afEmission_Interval_MID[2], m_afEmission_Interval_RNG[2]; /**< [Low(0), High(9)] Value Range */
    TgFLOAT32                                   m_afEmission_Quantity_MID[2], m_afEmission_Quantity_RNG[2]; /**< [Low(0), High(9)] Value Range */
    TgUINT_E08                                  m_uiPad_0[8];

    /* Fixed Data */
    TgVEC_F32_04_1                              m_vL_Vel_Acceleration_W; /**< Additive to key frame velocity */
    ETgFX_EMISSION_SHAPE                        m_enEmission_Shape;
    TgFLOAT32                                   m_fEmitter_Attraction;
    TgUINT_E32                                  m_uiFlags;
    TgUINT_E32                                  m_uiSort_Order; /**< Used to control sort ordering during the depth sort */
    TgUINT_E32                                  m_uiPad_1;

    /* Animation Data */
    TgUINT_E32                                  m_nbyData;
    union
    {
        struct /**< Written out in the data file */
        {
            TgUINT_PTR                                  m_uiEmitter_LVel_N; /**< F4 */
            TgUINT_PTR                                  m_uiEmitter_Rot_N; /**< F4 */
            TgUINT_PTR                                  m_uiEmission_Shape; /**< F4 */
        }                                           m_sData_Offset;
        struct /**< Fixed up after load */
        {
            STg2_FX_AnimData_P                          m_psEmitter_LVel_N; ///< F3: (x,y,z)
            STg2_FX_AnimData_P                          m_psEmitter_Rot_N;
            STg2_FX_AnimData_P                          m_psEmission_Shape;
        }                                           m_sParameter;
        STg2_FX_AnimData_P                          m_apsList[3];
    }                                           m_sAnim;
};


/* ---- Effect Data - GIB -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Originally body parts that are blown off a creature. This effect is used when the desire is to render and simulate a standard render mesh for a brief period of time as an FX. */

TgTYPE_STRUCT(STg2_FX_GIB__File_Data,)
{
    /* Spawn Data */
    TgFLOAT32                                   m_fTime_Total_MID, m_fTime_Total_RNG; //< Mean and range for when an effect instance ends.
    TgFLOAT32                                   m_fTime_Start_End_MID, m_fTime_Start_End_RNG; //< Mean and range for when an effect instance goes to stead-state.
    TgFLOAT32                                   m_fTime_End_Start_MID, m_fTime_End_Start_RNG; //< Mean and range for when an effect instance starts a finish state.
    TgUINT_MAX                                  m_uiHash_Material; /**< Render material name hash */

    /* Fixed Data */

    /* Animation Data */
    TgUINT_E32                                  m_nbyData;
    TgUINT_E08                                  m_auiData[4]; /**< Actual size is m_nuiData */
};


/* ---- Effect Data - Glass ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* Glass effect is used to model planar glass objects (windows) that needs to crack and fracture. */

TgTYPE_STRUCT(STg2_FX_Glass__File_Data,)
{
    /* Spawn Data */
    TgFLOAT32                                   m_fTime_Total_MID, m_fTime_Total_RNG; //< Mean and range for when an effect instance ends.
    TgFLOAT32                                   m_fTime_Start_End_MID, m_fTime_Start_End_RNG; //< Mean and range for when an effect instance goes to stead-state.
    TgFLOAT32                                   m_fTime_End_Start_MID, m_fTime_End_Start_RNG; //< Mean and range for when an effect instance starts a finish state.
    TgUINT_MAX                                  m_uiHash_Material; /**< Render material name hash */

    /* Fixed Data */

    /* Animation Data */
    TgUINT_E32                                  m_nbyData;
    TgUINT_E08                                  m_auiData[4]; /**< Actual size is m_nuiData */
};


/* ---- Effect Data - Group ------------------------------------------------------------------------------------------------------------------------------------------------------ */

TgTYPE_STRUCT(STg2_FX_Group_Effect__File_Data,)
{
    TgVEC_F32_04_1                              m_vPosition;
    TgVEC_F32_04_1                              m_vRotation;

    TgUINT_MAX                                  m_uiHash_Effect;
    TgFLOAT32                                   m_fStart;
    TgUINT_E32                                  m_uiPad0;
};

TgTYPE_STRUCT(STg2_FX_Group__File_Data,)
{
    /* Spawn Data */
    TgFLOAT32                                   m_fTime_Total_MID, m_fTime_Total_RNG; /**< Unused - always -1 */
    TgFLOAT32                                   m_fTime_Start_End_MID, m_fTime_Start_End_RNG; /**< Unused - always -1 */
    TgFLOAT32                                   m_fTime_End_Start_MID, m_fTime_End_Start_RNG; /**< Unused - always -1 */
    TgSINT_E32                                  m_niEffect;
    TgUINT_E32                                  m_uiPad0;

    /* Fixed Data */
    STg2_FX_Group_Effect__File_Data             m_asEffect[1]; /**< Actual size is m_nuiEffect */
};


/* ---- Effect Data - Light ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* Allows an effect to dynamically add a light to the scene. */

TgTYPE_STRUCT(STg2_FX_Light__File_Data,)
{
    /* Spawn Data */
    TgFLOAT32                                   m_fTime_Total_MID, m_fTime_Total_RNG; //< Mean and range for when an effect instance ends.
    TgFLOAT32                                   m_fTime_Start_End_MID, m_fTime_Start_End_RNG; //< Mean and range for when an effect instance goes to stead-state.
    TgFLOAT32                                   m_fTime_End_Start_MID, m_fTime_End_Start_RNG; //< Mean and range for when an effect instance starts a finish state.
    TgUINT_PTR                                  m_uiPad;
    TgVEC_F32_04_1                              m_vMin_BA;
    TgVEC_F32_04_1                              m_vMax_BA;

    /* Fixed Data */
    TgUINT_E32                                  m_uiFlags;

    /* Animation Data */
    TgUINT_E32                                  m_nbyData;
    union
    {
        struct /**< Written out in the data file */
        {
            TgUINT_PTR                                  m_uiPosition;
            TgUINT_PTR                                  m_uiDirection;
            TgUINT_PTR                                  m_uiDiffuse_G10_P709;
            TgUINT_PTR                                  m_uiSpecular_G10_P709;
            TgUINT_PTR                                  m_uiAmbient_G10_P709;
            TgUINT_PTR                                  m_uiGeom_Light;
        }                                           m_sData_Offset;
        struct /**< Fixed up after load */
        {
            STg2_FX_AnimData_P                          m_psPos_N;
            STg2_FX_AnimData_P                          m_psRot_N;
            STg2_FX_AnimData_P                          m_psDiffuse_G10_P709;
            STg2_FX_AnimData_P                          m_psSpecular_G10_P709;
            STg2_FX_AnimData_P                          m_psAmbient_G10_P709;
            STg2_FX_AnimData_P                          m_psGeom_Light;
        }                                           m_sParameter;
        STg2_FX_AnimData_P                          m_apsList[6];
    }                                           m_sAnim;

    TgUINT_E64                                  m_uiPad0;
};


/* ---- Effect Data - Liquid ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Used to model small pools of liquids (most often either water puddles, or pools of blood. */

TgTYPE_STRUCT(STg2_FX_Liquid__File_Data,)
{
    /* Spawn Data */
    TgFLOAT32                                   m_fTime_Total_MID, m_fTime_Total_RNG; //< Mean and range for when an effect instance ends.
    TgFLOAT32                                   m_fTime_Start_End_MID, m_fTime_Start_End_RNG; //< Mean and range for when an effect instance goes to stead-state.
    TgFLOAT32                                   m_fTime_End_Start_MID, m_fTime_End_Start_RNG; //< Mean and range for when an effect instance starts a finish state.
    TgUINT_MAX                                  m_uiHash_Material; /**< Render material name hash */

    /* Fixed Data */

    /* Animation Data */
    TgUINT_E32                                  m_nbyData;
    TgUINT_E08                                  m_auiData[4]; /**< Actual size is m_nuiData */
};


/* ---- Effect Data - Post ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Used to dynamically modify the post processing chain. */

TgTYPE_STRUCT(STg2_FX_Post__File_Data,)
{
    /* Spawn Data */
    TgFLOAT32                                   m_fTime_Total_MID, m_fTime_Total_RNG; //< Mean and range for when an effect instance ends.
    TgFLOAT32                                   m_fTime_Start_End_MID, m_fTime_Start_End_RNG; //< Mean and range for when an effect instance goes to stead-state.
    TgFLOAT32                                   m_fTime_End_Start_MID, m_fTime_End_Start_RNG; //< Mean and range for when an effect instance starts a finish state.
    TgUINT_MAX                                  m_uiHash_Material; /**< Render material name hash */

    TgUINT_E32                                  m_uiPad0;
    TgUINT_E32                                  m_uiPad1;
    TgUINT_E32                                  m_uiPad2;
    TgUINT_E32                                  m_nuiData;

    /* Fixed Data */
    /* Animation Data */
    TgUINT_E08                                  m_auiData[8]; /**< Actual size is m_nuiData */
};


/* ---- Effect Data - Sound ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* Used to dynamically add a sound to the scene. */

TgTYPE_STRUCT(STg2_FX_Sound__File_Data,)
{
    /* Spawn Data */
    TgFLOAT32                                   m_fTime_Total_MID, m_fTime_Total_RNG; /**< Unused - always -1 */
    TgFLOAT32                                   m_fTime_Start_End_MID, m_fTime_Start_End_RNG; /**< Unused - always -1 */
    TgFLOAT32                                   m_fTime_End_Start_MID, m_fTime_End_Start_RNG; /**< Unused - always -1 */
    TgUINT_PTR                                  m_uiPad;
    TgVEC_F32_04_1                              m_vDirection;
    TgVEC_F32_04_1                              m_vVelocity;

    /* Fixed Data */
    TgUINT_MAX                                  m_uiHash_Sound_Bank;
    TgUINT_MAX                                  m_uiHash_Sound;
    TgUINT_E32                                  m_uiEvent;
    TgUINT_E32                                  m_uiPad0;

                                                /* Fixed up after load */
    TgSN_BANK_ID                                m_tiSound_Bank;
    TgSN_ID                                     m_tiSound;
    TgUINT_E64                                  m_uiPad1;
};


/* ---- Effect Data - Trail ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* Trails dynamically create a set of quads that follow a path (spline). Think of a kite's tail in the wind. */

TgTYPE_STRUCT(STg2_FX_Trail__File_Data,)
{
    /* Spawn Data */
    TgFLOAT32                                   m_fTime_Total_MID, m_fTime_Total_RNG; //< Mean and range for when an effect instance ends.
    TgFLOAT32                                   m_fTime_Start_End_MID, m_fTime_Start_End_RNG; //< Mean and range for when an effect instance goes to stead-state.
    TgFLOAT32                                   m_fTime_End_Start_MID, m_fTime_End_Start_RNG; //< Mean and range for when an effect instance starts a finish state.
    TgUINT_MAX                                  m_uiHash_Material; /**< Render material name hash */
    TgVEC_F32_04_1                              m_vScale_U, m_vScale_V; /**< UV Scale (U0, 0, U1, 0), (0, V0, 0, V1) */

    /* Fixed Data */
    TgFLOAT32                                   m_fFollow_Fraction;
    TgUINT_E32                                  m_nuiMax_Points;
    TgUINT_E32                                  m_uiSort_Order; /**< Used to control sort ordering during the depth sort */
    TgUINT_E32                                  m_enTex;
    TgUINT_E32                                  m_uiPad1;

    /* Animation Data */
    TgUINT_E32                                  m_nbyData;
    union
    {
        struct /**< Written out in the data file */
        {
            TgUINT_PTR                                  m_uiColour; /**< F4 */
            TgUINT_PTR                                  m_uiWidth; /**< F2 */
        }                                           m_sData_Offset;
        struct /**< Fixed up after load */
        {
            STg2_FX_AnimData_P                          m_psColour;
            STg2_FX_AnimData_P                          m_psWidth;
        }                                           m_sParameter;
        STg2_FX_AnimData_P                          m_apsList[2];
    }                                           m_sAnim;
    TgUINT_E64                                  m_uiPad2;
};


/* ---- Effect Data -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_File_Data__FXFX,)
{
    STg2_File_Data                              m_sHeader;
    ETgFX__EFFECT                               m_enEffect;
    TgUINT_E32                                  m_uiPad0;
    TgUINT_MAX                                  m_uiHash;
    union
    {
        STg2_FX_Beam__File_Data                     m_sBeam;
        STg2_FX_Billboard__File_Data                m_sBillboard;
        STg2_FX_Decal__File_Data                    m_sDecal;
        STg2_FX_Particle__File_Data                 m_sParticle;
        STg2_FX_Emitter__File_Data                  m_sEmitter;
        STg2_FX_GIB__File_Data                      m_sGIB;
        STg2_FX_Glass__File_Data                    m_sGlass;
        STg2_FX_Group__File_Data                    m_sGroup;
        STg2_FX_Light__File_Data                    m_sLight;
        STg2_FX_Liquid__File_Data                   m_sLiquid;
        STg2_FX_Post__File_Data                     m_sPost;
        STg2_FX_Sound__File_Data                    m_sSound;
        STg2_FX_Trail__File_Data                    m_sTrail;
    }                                           m_sData;
};


TgTYPE_STRUCT(STg2_File_Data__FXDB,)
{
    STg2_File_Data                              m_sHeader;
    TgUINT_E32                                  m_uiPad0;
    TgUINT_E32                                  m_nuiNames;
    struct 
    {
        TgCHAR_U8                                   m_szName[32];
        TgUINT_MAX                                  m_uiHash;
    }                                           m_asName[1];
};


/* =============================================================================================================================================================================== */
#endif
