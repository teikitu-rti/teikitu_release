/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Internal - Type.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_EFFECT_INTERNAL_TYPE_H)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS Effect - Internal - Constants.h"


/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT( STg2_FX_Calc_Quad, )
{
    TgVEC_F32_04_1                      m_vPivot_X;
    TgVEC_F32_04_1                      m_vPivot_Y;
    TgVEC_F32_04_1                      m_vSize_X;
    TgVEC_F32_04_1                      m_vSize_Y;
    TgVEC_F32_04_1                      m_vPos_W;
    TgVEC_F32_04_1                      m_vDir_Up;
    TgVEC_F32_04_1                      m_vDir_Right;
};

TgTYPE_STRUCT(STg2_FX_Time,)
{
    TgFLOAT32                                   m_fTime_Total; ///< Total time of the effect. In case of data inconsistency, duration values are limited by the total time.
    TgFLOAT32                                   m_fTime_Start__End; ///< The duration of the start phase of the effect. Start is assumed to be zero.
    TgFLOAT32                                   m_fTime_End__Start; ///< The point in time that the end phase of the effects starts.
    TgFLOAT32                                   m_fLive_Time; ///< Starts at zero and counts up to the full life time of the FX
};


/* ---- Effect Commands ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_FX_Command__Update__NoParam,)
{
    ETgFX_COMMAND TgALIGN(16)                   m_enCommand;
    TgUINT_E32                                  m_uiPad0;
    union
    {
        TgFX_CLIENT_INST_ID                         m_tiClient;
        TgFX_DATA_INST_ID                           m_tiData;
    }                                           m_sDest;
};

TgTYPE_STRUCT(STg2_FX_Command__Update__1_S32,)
{
    ETgFX_COMMAND TgALIGN(16)                   m_enCommand;
    TgSINT_E32                                  m_iVal;
    union
    {
        TgFX_CLIENT_INST_ID                         m_tiClient;
        TgFX_DATA_INST_ID                           m_tiData;
    }                                           m_sDest;
};

TgTYPE_STRUCT(STg2_FX_Command__Update__1_F32,)
{
    ETgFX_COMMAND TgALIGN(16)                   m_enCommand;
    TgFLOAT32                                   m_fVal;
    union
    {
        TgFX_CLIENT_INST_ID                         m_tiClient;
        TgFX_DATA_INST_ID                           m_tiData;
    }                                           m_sDest;
};

TgTYPE_STRUCT(STg2_FX_Command__Update__1_F32_04,)
{
    ETgFX_COMMAND TgALIGN(16)                   m_enCommand;
    TgUINT_E32                                  m_uiPad0;
    union
    {
        TgFX_CLIENT_INST_ID                         m_tiClient;
        TgFX_DATA_INST_ID                           m_tiData;
    }                                           m_sDest;
    TgVEC_F32_04_1                            m_vF32_04;
};

TgTYPE_STRUCT(STg2_FX_Command__Update__2_F32_04,)
{
    ETgFX_COMMAND TgALIGN(16)                   m_enCommand;
    TgUINT_E32                                  m_uiPad0;
    union
    {
        TgFX_CLIENT_INST_ID                         m_tiClient;
        TgFX_DATA_INST_ID                           m_tiData;
    }                                           m_sDest;
    TgVEC_F32_04_1                            m_vF32_04[2];
};

TgTYPE_STRUCT(STg2_FX_Command__Update__1_UXX,)
{
    ETgFX_COMMAND TgALIGN(16)                   m_enCommand;
    TgUINT_E32                                  m_uiPad0;
    union
    {
        TgFX_CLIENT_INST_ID                         m_tiClient;
        TgFX_DATA_INST_ID                           m_tiData;
    }                                           m_sDest;
    TgUINT_MAX                                  m_uiVal;
    TgUINT_PTR                                  m_uiPad1;
};

TgTYPE_STRUCT(STg2_FX_Command__Update__2_UXX,)
{
    ETgFX_COMMAND TgALIGN(16)                   m_enCommand;
    TgUINT_E32                                  m_uiPad0;
    union
    {
        TgFX_CLIENT_INST_ID                         m_tiClient;
        TgFX_DATA_INST_ID                           m_tiData;
    }                                           m_sDest;
    TgUINT_MAX                                  m_uiVal[2];
};

TgTYPE_STRUCT(STg2_FX_Command__Notify,)
{
    ETgFX_COMMAND TgALIGN(16)                   m_enCommand;
    TgUINT_E32                                  m_uiMessage;
    TgVOID_P                                    m_pNotify;
};

TgTYPE_STRUCT(STg2_FX_Command__Update__Create,)
{
    ETgFX_COMMAND TgALIGN(16)                   m_enCommand;
    TgUINT_E32                                  m_uiPad0;
    TgFX_DATA_INST_ID                           m_tiData;
    TgFX_CLIENT_INST_ID                         m_tiClient;
    TgVOID_CP                                   m_psFile_Data_0;
    TgVOID_CP                                   m_psFile_Data_1;
    TgUINT_E32                                  m_uiPad1[2];
    STg2_FX_Instance                            m_sInstance;
};

TgTYPE_STRUCT(STg2_FX_Command__Client__Create,)
{
    ETgFX_COMMAND TgALIGN(16)                   m_enCommand;
    TgUINT_E32                                  m_uiPad0;
    TgUINT_MAX                                  m_uiHash;
    STg2_FX_Instance                            m_sInstance;
};

TgTYPE_STRUCT(STg2_FX_Command__Client__Free,)
{
    ETgFX_COMMAND TgALIGN(16)                   m_enCommand;
    TgUINT_E32                                  m_uiPad0;
    TgFX_DATA_INST_ID                           m_tiData;
    TgFX_CLIENT_INST_ID                         m_tiClient;
    TgUINT_PTR                                  m_uiPad1;
};

TgTYPE_STRUCT(STg2_FX_Command__Render__Patch,)
{
    ETgFX_COMMAND TgALIGN(16)                   m_enCommand;
    TgUINT_E32                                  m_uiPad0;
    TgFX_DATA_INST_ID                           m_tiData;
    TgSINT_E32                                  m_iIndex_In_SE_Context;
    TgUINT_E32                                  m_uiPad1[3];
};


/* ---- Effect File Data --------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_FX_Data__Effect,)
{
    TgFX_EFFECT_ID_SINGLETON                    m_tiEffect_Singleton;
    TgKN_FILE_ID                                m_tiFile;
    TgFX_CACHE_ID                               m_tiCache;
    STg2_File_Data__FXFX_CP                     m_psFile_Data;
    ETgFX__EFFECT                               m_enEffect;
    TgUINT_E32                                  m_nuiReference;
};

TgTYPE_STRUCT(STg2_FX_Data__Data,)
{
    TgFX_EFFECT_ID                              m_tiEffect;
    TgFX_CACHE_ID_SINGLETON                     m_tiCache;
    union
    {
        struct
        {
            TgSN_BANK_ID                                m_tiSound_Bank;
            TgSN_ID                                     m_tiSound;
        }                                           m_sSound;
    #if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
        struct
        {
            TgRN_MATERIAL_ID                            m_tiMaterial;
            TgRN_MESH_SET_ID                            m_tiMesh_Set;
            ETgKN_GPU_DEFAULT_INPUT_LAYOUT              m_enVertex;
            TgUINT_E32                                  m_uiPad;
        }                                           m_sRender;
    #endif
    }                                           m_sData;
};


/* ---- Effect Data - General ---------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_FX_Descriptor,)
{
    ETgFX__EFFECT                               m_enEffect;
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    ETgKN_GPU_EXT_TOPOLOGY_TYPE                 m_enPrimitive;
#else
    TgUINT_E32                                  m_uiPad;
#endif
    TgUINT_E32                                  m_uiMax;
};

TgTYPE_STRUCT(STg2_FX__Client,)
{
    TgFX_CLIENT_INST_ID                         m_tiUpdate_Next;

    TgFX_CLIENT_INST_ID_SINGLETON               m_tiClient_Singleton;
    TgFX_DATA_INST_ID                           m_tiData;
    TgATTACHMENT_ID                             m_tiAttachment;
    TgFX_CLIENT_INST_ID                         m_tiParent;
    TgRN_TARGET_ID                              m_tiTarget;

    TgFCN_CB_ON_TERMINATE                       m_pfnTerminate; ///< Executed on client thread.
    TgUINT_PTR                                  m_uiTerminate_Parameter;
    TgFCN_CB_ON_CONTACT                         m_pfnContact; ///< Executed on client thread after a render thread contact event.
    TgUINT_PTR                                  m_uiContact_Parameter;

    ETgFX__EFFECT                               m_enEffect;
    TgSINT_E32                                  m_iPriority; ///< Zero is median priority.
    TgFX_EFFECT_ID                              m_tiEffect;
    TgUINT_E32                                  m_uiUpdate : 2; ///< Must be large enough to hold ETgFX_UPDATE__MAX - 1.
    TgUINT_E32                                  m_uiRender_Visible : 1; /**< Boolean value */
    TgUINT_E32                                  m_uiPad2: 29;
    TgUINT_E32                                  m_uiPad3;
};


/* ---- Effect Data -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_FX__Beam__Extend_Data,)
{
    /* ------------ Create Data ------------ */
    TgVEC_F32_04_1 TgALIGN(16)                  m_vEnd_Variance;

    /* ------------ Update Data ------------ */
    TgVEC_F32_04_1                              m_vUV_01_Constant;
    TgVEC_F32_04_1                              m_vUV_01_Scale;
    TgVEC_F32_04_1                              m_vEnd_Position;
    TgFLOAT32                                   m_fShape_Start_Fraction;
    TgFLOAT32                                   m_fShape_End_Fraction;
    TgUINT_E08                                  m_uiPad[8];
};


TgTYPE_STRUCT(STg2_FX__Billboard__Extend_Data,)
{
    /* ------------ Create Data ------------ */
    TgVEC_F32_04_1                              m_vPlnX, m_vPlnY;

    /* ------------ Update Data ------------ */
    TgFLOAT32                                   m_fSpin;
    TgUINT_E32                                  m_uiPad0[3];
    TgVEC_F32_04_1                              m_vColour;
    TgVEC_F32_04_1                              m_vSize; /**< X=Size X, Y= Size Y, W, Z */
    TgVEC_F32_04_1                              m_vUV_01_Constant;
    TgVEC_F32_04_1                              m_vUV_01_Scale;
};


TgTYPE_STRUCT(STg2_FX__Decal__Vertex,)
{
    TgVEC_F32_04_1                              m_vS0_W;
    TgVEC_F32_04_1                              m_vT0;
    TgVEC_F32_04_1                              m_vB0;
    TgVEC_F32_04_1                              m_vUV_A; /* X=U, Y=V, Z=Alpha Mult, W=? */
};


TgTYPE_STRUCT(STg2_FX__Decal__Extend_Data,)
{
    /* ------------ Create Data ------------ */
    TgVEC_F32_04_1                              m_vSize_Start;
    TgVEC_F32_04_1                              m_vSize_Final;

    /* ------------ Update Data ------------ */
    TgVEC_F32_04_1                              m_vPos_N2W;
    TgVEC_F32_04_1                              m_vNormal;
    TgVEC_F32_04_1                              m_vScale;
    TgVEC_F32_04_1                              m_vSpin;
    TgVEC_F32_04_1                              m_vSize;
    TgVEC_F32_04_1                              m_vColour;
    TgVEC_F32_04_1                              m_vUV_01_Constant;
    TgVEC_F32_04_1                              m_vUV_01_Scale;

    /* ------------ Render Data ------------ */
    STg2_FX__Decal__Vertex_P                    m_psVert;
    TgRSIZE                                     m_nuiVert;
    TgRSIZE                                     m_nuiVert_Commit;
    TgUINT_E32                                  m_uiPad0[2];
};


TgTYPE_STRUCT(STg2_FX__Emitter__Particle,)
{
    /* ------------ Create Data ------------ */
    STg2_FX__Emitter__Particle_P                m_psNext;
    TgUINT_E32                                  m_uiPad0[2];
    TgVEC_F32_04_1                              m_vCollision_Restitution; ///< Collision Restitution factor, used if this particle is marked to collide.
    TgVEC_F32_04_1                              m_vSize_Variance; ///< Size variance for this particle's quad.
    TgVEC_F32_04_1                              m_vRot_Variance; ///< Rotational Variance applied in the Particle Root Reference Frame.
    TgVEC_F32_04_1                              m_vLVel_Variance; ///< Linear Velocity Variance applied in the Particle Root Reference Frame.
    TgVEC_F32_04_1                              m_vRVel_Acceleration; ///< Rotation Acceleration in Particle Root Reference Frame.

    TgVEC_F32_04_1                              m_vSpawn_Pos_R2N; ///< Translation from Particle Data (RT) Reference Frame to Emitter Root Reference Frame.
    TgVEC_F32_04_1                              m_vSpawn_Pos_N2W; ///< Translation from Emitter Root Reference Frame to World Reference Frame.
    TgVEC_F32_04_1                              m_vSpawn_Rot_R2N; ///< Rotation from Particle Data (RT) Reference Frame to Emitter Root Reference Frame.
    TgVEC_F32_04_1                              m_vSpawn_Rot_N2W; ///< Translation from Emitter Root Reference Frame to World Reference Frame.

    /* ---------- Animation Data ----------- */
    TgVEC_F32_04_1                              m_vPos_Anim_RT; ///< Translation transform from Raw Data at time 0 to time T.
    TgVEC_F32_04_1                              m_qRot_Anim_RT; ///< Rotation transform from Raw Data at time 0 to time T.
    TgVEC_F32_04_1                              m_vLVel_N; ///< Linear Velocity at time T in Particle Root Reference Frame.
    TgVEC_F32_04_1                              m_vSpin; ///< Spin at time T.
    TgVEC_F32_04_1                              m_vTurbulence; ///< Turbulence (position jitter) applied to the particle quad at time T.
    TgVEC_F32_04_1                              m_vSize_X; ///< Width of the particle quad at time T.
    TgVEC_F32_04_1                              m_vSize_Y; ///< Height of the particle quad at time T.
    TgVEC_F32_04_1                              m_vColour; ///< Colour of the particle quad at time T.

    /* ------------ Update Data ------------ */
    TgVEC_F32_04_1                              m_vLife_Time; ///< This counts from the total life time of the particle down to zero.
    TgVEC_F32_04_1                              m_vLive_Time; ///< This counts up from zero to the total life time of the particle.

    TgVEC_F32_04_1                              m_vPos_W; ///< Position in World Reference Frame.
    TgVEC_F32_04_1                              m_qRot_N2W; ///< Rotation transform to move from the Emitter Root Reference Frame to the World Reference Frame.
    TgVEC_F32_04_1                              m_vLVel_W; ///< Linear velocity in the World Reference Frame.

    TgVEC_F32_04_1                              m_vUV_01_Constant; //< Calculated during render
    TgVEC_F32_04_1                              m_vUV_01_Scale; //< Calculated during render
};

TgTYPE_STRUCT(STg2_FX__Emitter__Extend_Data,)
{
    /* ------------ Create Data ------------ */
    TgFLOAT32                                   m_fEmission_Interval; ///< Time in ms between emissions.
    TgFLOAT32                                   m_fEmission_Quantity; ///< Amount of particles to emit, when emitting (fractions carry over to the next emission period).
    TgRSIZE                                     m_nuiParticle_Max; ///< Maximum number of particles supported by this emitter.

    TgRSIZE                                     m_nuiParticle_Commit; ///< Amount of memory that is committed from the reserved virtual address space for this emitter's particles.
    STg2_FX__Emitter__Particle_P                m_psParticle_Active; ///< Head of the linked list of active particles.
    STg2_FX__Emitter__Particle_P                m_psParticle_Free; ///< Head of the linked list of free particles.
    STg2_FX__Emitter__Particle_P                m_psParticle_Memory; ///< Pointer to the first particle in the committed address space.
    STg2_FX_Particle__File_Data_CP              m_psFile_Data__Particle; ///< Pointer to the file data for the particle descriptor.
    TgSINT_E08                                  m_iPad_0[8];

    /* ------------ Update Data ------------ */
    TgVEC_F32_04_1                              m_vLVel_N; ///< Linear velocity for the emitter in it's Root Reference Frame.
    TgVEC_F32_04_1                              m_vEmission_Shape; ///< Used to describe the extents of the space for the particle's spawn location.
    TgRSIZE                                     m_nuiParticle; ///< Number of active particles.
    TgRSIZE                                     m_nuiParticle_Render; ///< Number of rendered particles.
};

TgTYPE_STRUCT(STg2_FX__GIB__Extend_Data,)
{
    TgVEC_F32_04_1                            m_vUnused;
};

TgTYPE_STRUCT(STg2_FX__Glass__Extend_Data,)
{
    TgVEC_F32_04_1                            m_vUnused;
};

TgTYPE_STRUCT(STg2_FX__Group__Extend_Data,)
{
    /* ------------ Client Data ------------ */
    TgFX_CLIENT_INST_ID TgALIGN(16)             m_atiChildren[KTgFX_MAX_GROUP_SUB_EFFECTS];
    TgSINT_E32_A                                m_xniChildren;
    
    /* ------------ Update Data ------------ */
    TgFLOAT32                                   m_fLive_Time;
    TgSINT_E64                                  m_iPad1;
};

TgTYPE_STRUCT(STg2_FX__Light__Extend_Data,)
{
    /* ------------ Update Data ------------ */
    TgVEC_F32_04_1                              m_vDiffuse_G10_P709;
    TgVEC_F32_04_1                              m_vSpecular_G10_P709;
    TgVEC_F32_04_1                              m_vAmbient_G10_P709;
    TgVEC_F32_04_1                              m_vGeom_Light;
};

TgTYPE_STRUCT(STg2_FX__Liquid__Extend_Data,)
{
    /* ------------ Update Data ------------ */
    TgVEC_F32_04_1                            m_qRot_N2W;
    TgVEC_F32_04_1                            m_vPos_N2W;
};

TgTYPE_STRUCT(STg2_FX__Post__Extend_Data,)
{
    TgVEC_F32_04_1                            m_vUnused;
};

TgTYPE_STRUCT(STg2_FX__Sound__Extend_Data,)
{
    TgSN_INST_ID                                m_tiSound_Instance;
    TgSINT_E64                                  m_iPad0;
    TgVEC_F32_04_1                              m_vDir_W;
};

TgTYPE_STRUCT(STg2_FX__Trail__Extend_Data,)
{
    /* ------------ Update Data ------------ */
    TgVEC_F32_04_1                              m_vPos_N2W[KTgFX_MAX_POINTS_IN_TRAIL];
    TgVEC_F32_04_1                              m_vScaleFactor; /**< Single scale value */
    TgFLOAT32                                   m_fU[KTgFX_MAX_POINTS_IN_TRAIL];
    TgUINT_E32                                  m_uiPoint_Head;
    TgUINT_E32                                  m_uiPoint_Tail;
    TgUINT_E32                                  m_uiHead_Offset;
    TgUINT_E32                                  m_uiPad2;
    TgVEC_F32_04_1                              m_vEnd_Time;
    TgVEC_F32_04_1                              m_vColour;
    TgVEC_F32_04_1                              m_vWidth;
    TgVEC_F32_04_1                              m_vUV_01_Constant;
    TgVEC_F32_04_1                              m_vUV_01_Scale;
};


/* ---- Effect Job Type ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_FX_Job__Update_Data,)
{
    TgVEC_F32_04_1 TgALIGN(16)                  m_vDT; /* Time Step */
    TgFLOAT32                                   m_fDT; /* Time Step */
    ETgFX_UPDATE                                m_enUpdate;
    TgUINT_E08                                  m_uiPad[8];
};
TgCOMPILER_ASSERT( sizeof( STg2_FX_Job__Update_Data ) <= KTgJOB_DATA_SIZE, 0 );

TgTYPE_STRUCT(STg2_FX_Job__Scene__Bounding_Box,)
{
    ETgFX_UPDATE TgALIGN(16)                    m_enUpdate;
    TgUINT_E08                                  m_uiPad_0[12];
};
TgCOMPILER_ASSERT( sizeof( STg2_FX_Job__Scene__Bounding_Box ) <= KTgJOB_DATA_SIZE, 0 );

#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)

TgTYPE_STRUCT(STg2_FX_Job__Scene__Cull_Data,)
{
    ETgFX_UPDATE TgALIGN(16)                    m_enUpdate;
    TgUINT_E08                                  m_uiPad_0[4];
    TgRSIZE                                     m_uiView_Index;
    STg2_SE_Context_P                           m_psScene_Context;
    TgUINT_E08                                  m_uiPad_1[8];
};
TgCOMPILER_ASSERT( sizeof( STg2_FX_Job__Scene__Cull_Data ) <= KTgJOB_DATA_SIZE, 0 );

TgTYPE_STRUCT(STg2_FX_Job__Scene__Finish,)
{
    STg2_SE_Context_P TgALIGN(16)               m_psScene_Context;
    TgRSIZE                                     m_uiView_Index;
//  TgUINT_E08                                  m_uiPad_0[12];
};
TgCOMPILER_ASSERT( sizeof( STg2_FX_Job__Scene__Finish ) <= KTgJOB_DATA_SIZE, 0 );

TgTYPE_STRUCT(STg2_FX_Job__Process_Headers,)
{
    STg2_FX_Rnd_Output_P TgALIGN(16)            m_psRndOut;
    ETgFX_UPDATE                                m_enUpdate;
    TgUINT_F32                                  m_uiPad;
};
TgCOMPILER_ASSERT( sizeof( STg2_FX_Job__Process_Headers ) <= KTgJOB_DATA_SIZE, 0 );

TgTYPE_STRUCT(STg2_FX_Job__Render_Allocate,)
{
    STg2_FX_Rnd_Output_P TgALIGN(16)            m_psRndOut;
    TgUINT_F32                                  m_uiPad0[2];
};
TgCOMPILER_ASSERT( sizeof( STg2_FX_Job__Render_Allocate ) <= KTgJOB_DATA_SIZE, 0 );

TgTYPE_STRUCT(STg2_FX_Job__Render_Generate,)
{
    STg2_FX_Rnd_Output_P TgALIGN(16)            m_psRndOut;
    TgUINT_F32                                  m_uiPad0[2];
};
TgCOMPILER_ASSERT( sizeof( STg2_FX_Job__Render_Generate ) <= KTgJOB_DATA_SIZE, 0 );

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif


/* ---- Effect Generic Type ------------------------------------------------------------------------------------------------------------------------------------------------------ */

#define __PARENT_FILE__ "TgS Effect - Internal - Type.h"
#define ENABLE_RELOAD_GUARD
#include "TgS EFFECT/TgS Effect - Effect [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_EFFECT_INTERNAL_TYPE_H

/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Type                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(T_NAME(STg2_FX__,),)
{
    union
    {
        STg2_UT_ST__ST_Node                         m_sStack_Node;
        T_NAME(STg2_FX_, __File_Data_CP)            m_psFile_Data;
    };

    TgFX_CLIENT_INST_ID                         m_tiClient;
    TgFX_DATA_INST_ID                           m_tiData;

#if T_EFFECT_TIME
    STg2_FX_Time                                m_sTime;

    TgFLOAT32                                   m_fTime_End__Duration; ///< Duration of the end phase of the FX
    TgFLOAT32                                   m_fLife_Time; ///< Starts at the full life time of the FX, and counts down to 0
    TgVEC_F32_04_1                              m_vLive_Time; ///< Starts at zero and counts up to the full life time of the FX, broadcast across all lanes.
/*# T_EFFECT_TIME */
#else
    TgUINT_E32                                  m_uiPad_0[2];
/*# T_EFFECT_TIME */
#endif

#if T_EFFECT_FRAME
    TgVEC_F32_04_1                              m_qRot_N2M; ///< Root (no transformations) rotational reference frame to model rotational reference frame.
    TgVEC_F32_04_1                              m_qRot_M2W; ///< Model rotational reference frame to world rotational reference frame.
    TgVEC_F32_04_1                              m_qRot_N2W; ///< Root (no transformations) rotational reference frame to world rotational reference frame.
    TgVEC_F32_04_1                              m_vPos_W; ///< Position in the world reference frame.
    TgVEC_F32_04_1                              m_vPos_N2M; ///< Root (no transformations) translation reference frame to model translation reference frame.
    TgVEC_F32_04_1                              m_vPos_M2W; ///< Model translation reference frame to world translation reference frame.
    TgVEC_F32_04_1                              m_vPos_N2W; ///< Root (no transformations) translation reference frame to world translation reference frame.
    TgVEC_F32_04_1                              m_vScale; ///< Scale of the model
/*# T_EFFECT_FRAME */
#endif

#if T_EFFECT_SCENE || T_EFFECT_RENDER
    TgVEC_F32_04_1                              m_vBA_Max_W; ///< Maximum values of an axis aligned bounding box in the world reference frame.
    TgVEC_F32_04_1                              m_vBA_Min_W; ///< Minimum values of an axis aligned bounding box in the world reference frame.
/*# T_EFFECT_SCENE || T_EFFECT_RENDER */
#endif

    T_NAME(STg2_FX__, __Extend_Data)            m_sExtend;

#if T_EFFECT_RENDER
    TgFX_DATA_INST_ID                           m_tiNext[ETgFX_NEXT__RENDER + 1];
#elif T_EFFECT_SCENE
    TgFX_DATA_INST_ID                           m_tiNext[ETgFX_NEXT__SCENE + 1];
#elif T_EFFECT_UPDATE
    TgFX_DATA_INST_ID                           m_tiNext[ETgFX_NEXT__UPDATE + 1];
#endif
    
#if T_EFFECT_RENDER
    TgRN_MESH_SET_ID                            m_tiMesh_Set; ///< UID for the Mesh Set used by this effect in the render module.
    TgRN_MATERIAL_ID                            m_tiMaterial; ///< UID for the material of this effect in the render module.
    TgRSIZE                                     m_uiIndex_In_SE_Context; ///< Index in the SE Context for this Effect.
    TgRSIZE                                     m_uiIndex_In_RN_Context; ///< Index in the Render Output Context for this Effect.
    TgFLOAT32                                   m_fSE_Quality_Score; ///< Quality score determine by SE Module.
    ETgKN_GPU_DEFAULT_INPUT_LAYOUT              m_enVertex; ///< Input Layout enumeration selector.
    TgUINT_E32                                  m_uiPad_1[3];
#elif T_EFFECT_SCENE
    TgUINT_E32                                  m_uiPad_1[3];
#elif T_EFFECT_UPDATE
    TgUINT_E32                                  m_uiPad_1[1];
#endif

    TgUINT_E32                                  m_uiUpdate : 2; ///< Must be large enough to hold ETgFX_UPDATE__MAX - 1
    TgUINT_E32                                  m_uiScene__Cull__Insert_Frame_Mesh : 1; ///< Boolean value
    TgUINT_E32                                  m_uiRender__NotVisible : 1; ///< Boolean value
    TgUINT_E32                                  m_uiRender__ScreenSpace : 1; ///< Boolean value
    TgUINT_E32                                  m_uiFlagPad: 27;
};


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/*# !defined(TGS_EFFECT_INTERNAL_TYPE_H) */
#endif
