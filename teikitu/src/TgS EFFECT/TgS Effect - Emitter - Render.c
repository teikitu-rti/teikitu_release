/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Emitter - Render.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS Effect - Render.inl"


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_FX__Emitter__Render_Point,)
{
    /* --------------- Input --------------- */
    STg2_FX__Emitter_P                          m_psEmitter;
    STg2_FX__Emitter__Extend_Data_P             m_psExtend;
    STg2_FX_Emitter__File_Data_CP               m_psFile_Data;
    TgUINT_F32                                  m_uiPad0[2];
    TgVEC_F32_04_1                              m_vCam_Pos_W;
    TgVEC_F32_04_1                              m_vCam_Right;
    TgVEC_F32_04_1                              m_vCam_Up;
    TgVEC_F32_04_1                              m_vCam_Forward;
    TgVEC_F32_04_1                              m_vUV_Mask[4];
    TgVEC_F32_04_1                              m_vPivotX;
    TgVEC_F32_04_1                              m_vPivotY;
    TgVEC_F32_04_4_CP                           m_pxFrustum_S2C; /**< Screen to Camera (Inverse Proj) */
    TgFLOAT32                                   m_fAspect_Ratio;
    TgUINT_F32                                  m_uiPad1;

    /* --------------- Output -------------- */
    TgVEC_F32_04_1                              m_vRight;
    TgVEC_F32_04_1                              m_vUp;
    TgVEC_F32_04_1                              m_avPos_W[4];
    TgVEC_F32_04_1                              m_avBasis[2];
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgFX_Effect__Emitter__Render_Init_Point(
    STg2_FX__Emitter__Render_Point_P, STg2_FX_Rnd_Output_PC );

static TgVOID
tgFX_Effect__Emitter__Reference_Frame(
    STg2_FX__Emitter__Render_Point_P, TgVEC_F32_04_1_C );

static TgVOID
tgFX_Effect__Emitter__Render_Calculate_Point(
    STg2_FX__Emitter__Render_Point_P, STg2_FX__Emitter__Particle_CP );

static TgUINT_F32
tgFX__Render__Emitter_Render_Generate_Particle_Tangent_00(
    STg2_FX__Emitter__Render_Point_P, STg2_FX_Rnd_Output_PC, STg2_RN_Particle_Header_PC, STg2_FX__Emitter_P );

static TgUINT_F32
tgFX__Render__Emitter_Render_Generate_Particle_Tangent_01(
    STg2_FX__Emitter__Render_Point_P, STg2_FX_Rnd_Output_PC, STg2_RN_Particle_Header_PC, STg2_FX__Emitter_P );

TgFORCEINLINE TgVOID
tgFX_Effect__Emitter__Render_Write_Quad_00(
    STg2_KN_GPU_Vertex_Particle_00_P, STg2_FX__Emitter__Render_Point_CP, STg2_FX__Emitter__Particle_CP );

TgFORCEINLINE TgVOID
tgFX_Effect__Emitter__Render_Write_Quad_01(
    STg2_KN_GPU_Vertex_Particle_01_P, STg2_FX__Emitter__Render_Point_CP, STg2_FX__Emitter__Particle_CP );

TgFORCEINLINE TgVOID
tgFX_Effect__Emitter__Render_Write_Quad_Tangent_00(
    STg2_KN_GPU_Vertex_Particle_00_P, STg2_FX__Emitter__Render_Point_CP, STg2_FX__Emitter__Particle_CP );

TgFORCEINLINE TgVOID
tgFX_Effect__Emitter__Render_Write_Quad_Tangent_01(
    STg2_KN_GPU_Vertex_Particle_01_P, STg2_FX__Emitter__Render_Point_CP, STg2_FX__Emitter__Particle_CP );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define ENABLE_RELOAD_GUARD
#define T(A) A##_00
#include __FILE__
#undef T
#define T(A) A##_01
#include __FILE__
#undef T
#undef ENABLE_RELOAD_GUARD




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Effect__Emitter__Render_Init_Point ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX_Effect__Emitter__Render_Init_Point( STg2_FX__Emitter__Render_Point_P psPoint, STg2_FX_Rnd_Output_PC psRndOut )
{
    psPoint->m_psExtend = &(psPoint->m_psEmitter->m_sExtend);
    psPoint->m_psFile_Data = psPoint->m_psEmitter->m_psFile_Data;
    psPoint->m_vCam_Pos_W = psRndOut->m_psCamera->m_sCamera.m_uCam_Position.m_vF32_04_1;
    psPoint->m_vCam_Right = psRndOut->m_psCamera->m_vCam_Right;
    psPoint->m_vCam_Up = psRndOut->m_psCamera->m_vCam_Up;
    psPoint->m_vCam_Forward = psRndOut->m_psCamera->m_vCam_Forward;

    psPoint->m_vUV_Mask[0] = tgMH_Init_ELEM_F32_04_1( 0.0F, 0.0F, 0.0F, 0.0F );
    psPoint->m_vUV_Mask[1] = tgMH_Init_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F, 1.0F );
    psPoint->m_vUV_Mask[2] = tgMH_Init_ELEM_F32_04_1( 1.0F, 1.0F, 1.0F, 1.0F );
    psPoint->m_vUV_Mask[3] = tgMH_Init_ELEM_F32_04_1( 1.0F, 0.0F, 1.0F, 0.0F );

    psPoint->m_vPivotX = tgMH_SET1_F32_04_1( psPoint->m_psFile_Data->m_fEmission_Pivot_X );
    psPoint->m_vPivotY = tgMH_SET1_F32_04_1( psPoint->m_psFile_Data->m_fEmission_Pivot_Y );

    psPoint->m_pxFrustum_S2C = &psRndOut->m_psCamera->m_xFrustum_S2C;
    psPoint->m_fAspect_Ratio = psRndOut->m_psCamera->m_sCamera.m_fAspect_Ratio;

#if TgS_DEBUG__EFFECT
    {
        TgBOOL                              bDraw;
        if ((tgCN_Var_Query_Bool( &bDraw, g_tiFX_Debug__Emitter__Draw_Debug )) && (bDraw))
        {
            TgVEC_F32_04_3                    xM0;
            TgVEC_F32_04_1                    qRot_W;
            TgVEC_F32_04_1                    vPos_W;

            qRot_W = psPoint->m_psEmitter->m_qRot_N2W;
            vPos_W = psPoint->m_psEmitter->m_vPos_N2W;

            tgMH_Init_Quat_F32_04_3( &xM0, qRot_W );
            tgMH_Init_T_F32_04_3( &xM0, vPos_W );
            tgRN_DBG_Axes( &xM0, 0.1F );
            tgRN_DBG_Sphere( KTg_WHITE_G10_P709_U32, psPoint->m_psEmitter->m_vPos_N2W, 0.1F );
        };
    }
/*# TgS_DEBUG__EFFECT */
#endif
}


/* ---- tgFX_Effect__Emitter__Reference_Frame ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX_Effect__Emitter__Reference_Frame( STg2_FX__Emitter__Render_Point_P psPoint, TgVEC_F32_04_1_C vPos_W )
{
    TgVEC_F32_04_1                    vDirTest;
    TgVEC_F32_04_1                    vForward;

    psPoint->m_vRight = psPoint->m_vCam_Right;
    psPoint->m_vUp = psPoint->m_vCam_Up;

    switch (psPoint->m_psExtend->m_psFile_Data__Particle->m_enOrientation)
    {
        case ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_SPHERE:

            vForward = tgMH_SUB_F32_04_1( psPoint->m_vCam_Pos_W, vPos_W );
            vForward = tgMH_NORM_F32_04_1( vForward );
            vDirTest = tgMH_DOT_F32_04_1( psPoint->m_vCam_Up, vForward );
            if (!tgCM_NR1_F32( tgPM_ABS_F32( ((TgVEC_S_F32_04_1_P)(&vDirTest))->x ) ))
            {
                psPoint->m_vRight = tgMH_UCX_F32_04_1( psPoint->m_vCam_Up, vForward );
                psPoint->m_vUp = tgMH_UCX_F32_04_1( vForward, psPoint->m_vRight );
            }
            else
            {
                psPoint->m_vUp = tgMH_UCX_F32_04_1( vForward, psPoint->m_vCam_Right );
                psPoint->m_vRight = tgMH_UCX_F32_04_1( psPoint->m_vUp, vForward );
            };
            break;

        case ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_PLANE:
            break;

        case ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_SPHERE__FIXED_Y:

            vForward = tgMH_SUB_F32_04_1( psPoint->m_vCam_Pos_W, vPos_W );
            vForward = tgMH_NORM_F32_04_1( vForward );
            vDirTest = tgMH_DOT_F32_04_1( KTgUNIT_Y_V128.m_vF32_04_1, vForward );
            if (!tgCM_NR1_F32( tgPM_ABS_F32( ((TgVEC_S_F32_04_1_P)(&vDirTest))->x ) ))
            {
                psPoint->m_vUp = KTgUNIT_Y_V128.m_vF32_04_1;
                psPoint->m_vRight = tgMH_UCX_F32_04_1( KTgUNIT_Y_V128.m_vF32_04_1, vForward );
            }
            else
            {
                psPoint->m_vUp = KTgZERO_V128.m_vF32_04_1;
                psPoint->m_vRight = KTgZERO_V128.m_vF32_04_1;
            };
            break;

        case ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_PLANE__FIXED_Y:

            vDirTest = tgMH_DOT_F32_04_1( KTgUNIT_Y_V128.m_vF32_04_1, psPoint->m_vCam_Right );
            if (!tgCM_NR1_F32( tgPM_ABS_F32( ((TgVEC_S_F32_04_1_P)(&vDirTest))->x ) ))
            {
                psPoint->m_vRight = tgMH_UCX_F32_04_1( KTgUNIT_Y_V128.m_vF32_04_1, tgMH_CX_F32_04_1( psPoint->m_vCam_Right, KTgUNIT_Y_V128.m_vF32_04_1 ) );
            }
            else
            {
                psPoint->m_vRight = psPoint->m_vCam_Up;
            };

            psPoint->m_vUp = KTgUNIT_Y_V128.m_vF32_04_1;
            break;

        case ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_SPHERE__FIXED_XZ:

            vForward = tgMH_SUB_F32_04_1( psPoint->m_vCam_Pos_W, vPos_W );
            vForward = tgMH_NORM_F32_04_1( vForward );
            vDirTest = tgMH_DOT_F32_04_1( KTgUNIT_Y_V128.m_vF32_04_1, vForward );
            if (!tgCM_NR1_F32( tgPM_ABS_F32( ((TgVEC_S_F32_04_1_P)(&vDirTest))->x ) ))
            {
                psPoint->m_vRight = tgMH_UCX_F32_04_1( KTgUNIT_Y_V128.m_vF32_04_1, vForward );
                psPoint->m_vUp = tgMH_UCX_F32_04_1( psPoint->m_vRight, KTgUNIT_Y_V128.m_vF32_04_1 );
            }
            else
            {
                psPoint->m_vRight = psPoint->m_vCam_Forward;
            };
            break;

        case ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_PLANE__FIXED_XZ:

            vDirTest = tgMH_DOT_F32_04_1( KTgUNIT_Y_V128.m_vF32_04_1, psPoint->m_vCam_Right );
            if (!tgCM_NR1_F32( tgPM_ABS_F32( ((TgVEC_S_F32_04_1_P)(&vDirTest))->x ) ))
            {
                psPoint->m_vUp = tgMH_UCX_F32_04_1( psPoint->m_vCam_Right, KTgUNIT_Y_V128.m_vF32_04_1 );
                psPoint->m_vRight = tgMH_UCX_F32_04_1( KTgUNIT_Y_V128.m_vF32_04_1, psPoint->m_vUp );
            }
            else
            {
                psPoint->m_vRight = psPoint->m_vCam_Forward;
            };
            break;

        case ETgFX_PARTICLE_ORIENTATION__SCREEN_SPACE:
            psPoint->m_vRight = KTgUNIT_X_V128.m_vF32_04_1;
            psPoint->m_vUp = KTgUNIT_Y_V128.m_vF32_04_1;
            break;

        case ETgFX_PARTICLE_ORIENTATION__VELOCITY_TANGENT:
        case ETgFX_PARTICLE_ORIENTATION__NONE:
        default:
            TgS_NO_DEFAULT(break);
    };
}

/* ---- tgFX_Effect__Emitter__Render_Calculate_Point ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX_Effect__Emitter__Render_Calculate_Point( STg2_FX__Emitter__Render_Point_P psPoint, STg2_FX__Emitter__Particle_CP psParticle )
{
    STg2_FX_Calc_Quad                   sData;
    TgVEC_F32_04_1                      vLive_Time_Squared;
    TgVEC_F32_04_1                      vSpin_Accel;
    TgUN_V128                           uSpin;

    sData.m_vPivot_X = psPoint->m_vPivotX;
    sData.m_vPivot_Y = psPoint->m_vPivotY;
    sData.m_vSize_X = tgMH_MUL_F32_04_1( psParticle->m_vSize_X, psPoint->m_psEmitter->m_vScale );
    sData.m_vSize_Y = tgMH_MUL_F32_04_1( psParticle->m_vSize_Y, psPoint->m_psEmitter->m_vScale );
    sData.m_vPos_W = tgMH_Init_Point_F32_04_1( tgMH_ADD_F32_04_1( psParticle->m_vPos_W, psParticle->m_vTurbulence ) );
    sData.m_vDir_Right = psPoint->m_vRight;
    sData.m_vDir_Up = psPoint->m_vUp;

    vLive_Time_Squared = tgMH_MUL_F32_04_1( psParticle->m_vLive_Time, psParticle->m_vLive_Time );
    vSpin_Accel = tgMH_MUL_F32_04_1( psParticle->m_vRVel_Acceleration, vLive_Time_Squared );
    vSpin_Accel = tgMH_MUL_F32_04_1( tgMH_SET1_F32_04_1( 0.5F ), vSpin_Accel );
    uSpin.m_vF32_04_1 = tgMH_ADD_F32_04_1( psParticle->m_vSpin, vSpin_Accel );

    if (ETgFX_PARTICLE_ORIENTATION__SCREEN_SPACE == psPoint->m_psExtend->m_psFile_Data__Particle->m_enOrientation)
    {
        sData.m_vSize_Y = tgMH_MUL_F32_04_1( sData.m_vSize_Y, tgMH_SET1_F32_04_1( psPoint->m_fAspect_Ratio ) );
    };

    tgFX_Calc_Quad( /* Output */ psPoint->m_avPos_W, psPoint->m_avBasis, /* Input */ uSpin.m_vS_F32_04_1.x, &sData );

    if (ETgFX_PARTICLE_ORIENTATION__SCREEN_SPACE == psPoint->m_psExtend->m_psFile_Data__Particle->m_enOrientation)
    {
        TgVEC_F32_04_1                      vBound;
        TgVEC_F32_04_1                      vAdjust;
        TgVEC_F32_04_1                      vW;
        TgRSIZE                             uiVert;

        vBound = tgMH_Init_ELEM_F32_04_1( 1.0F, 1.0F, KTgMAX_F32, KTgMAX_F32 );

        for (uiVert = 0; uiVert < 4; ++uiVert)
        {
            psPoint->m_avPos_W[uiVert] = tgMH_BND_F32_04_1( psPoint->m_avPos_W[uiVert], vBound );
            vAdjust = tgMH_Init_Vector_F32_04_1( psPoint->m_avPos_W[uiVert] );
            vAdjust = tgMH_TX_F32_04_4( vAdjust, psPoint->m_pxFrustum_S2C );
            vW = tgMH_SPW_F32_04_1( vAdjust );
            vAdjust = tgMH_DIV_F32_04_1( vAdjust, vW );
            psPoint->m_avPos_W[uiVert] = tgMH_Init_Point_F32_04_1( vAdjust );
        };
    };

#if TgS_DEBUG__EFFECT
    {
        TgBOOL                              bDraw;
        if ((tgCN_Var_Query_Bool( &bDraw, g_tiFX_Debug__Emitter__Draw_Debug )) && (bDraw))
        {
            tgRN_DBG_Sphere( KTg_RED_G10_P709_U32, sData.m_vPos_W, 0.1F );
        };
    }
/*# TgS_DEBUG__EFFECT */
#endif
}


/* ---- tgFX_Effect__Emitter__Render_Write_Quad_00 ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgVOID tgFX_Effect__Emitter__Render_Write_Quad_00(
    STg2_KN_GPU_Vertex_Particle_00_P psVert, STg2_FX__Emitter__Render_Point_CP psPoint, STg2_FX__Emitter__Particle_CP psParticle )
{
    unsigned short                      sIndex_Gradient[] = { 0, 1, 2, 3, 0, 2 };
    TgVEC_F32_04_1                      vUV;
    TgRSIZE                             uiIndex, uiVert;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(sIndex_Gradient); ++uiIndex)
    {
        uiVert = sIndex_Gradient[uiIndex];
        vUV = tgMH_MAD_F32_04_1( psPoint->m_vUV_Mask[uiVert], psParticle->m_vUV_01_Scale, psParticle->m_vUV_01_Constant );

        psVert[uiIndex].m_vS0 = psPoint->m_avPos_W[uiVert];
        psVert[uiIndex].m_vUV = vUV;
        psVert[uiIndex].m_vCL = psParticle->m_vColour;
    };
}


/* ---- tgFX_Effect__Emitter__Render_Write_Quad_01 ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgVOID tgFX_Effect__Emitter__Render_Write_Quad_01(
    STg2_KN_GPU_Vertex_Particle_01_P psVert, STg2_FX__Emitter__Render_Point_CP psPoint, STg2_FX__Emitter__Particle_CP psParticle )
{
    TgVEC_F32_04_1                      vUV;
    TgRSIZE                             uiVert;

    for (uiVert = 0; uiVert < 4; ++uiVert)
    {
        vUV = tgMH_MAD_F32_04_1( psPoint->m_vUV_Mask[uiVert], psParticle->m_vUV_01_Scale, psParticle->m_vUV_01_Constant );

        psVert[uiVert].m_vS0 = psPoint->m_avPos_W[uiVert];
        psVert[uiVert].m_vT0 = psPoint->m_avBasis[0];
        psVert[uiVert].m_vB0 = psPoint->m_avBasis[1];
        psVert[uiVert].m_vUV = vUV;
        psVert[uiVert].m_vCL = psParticle->m_vColour;
    };
}


/* ---- tgFX_Effect__Emitter__Render_Write_Quad_Tangent_00 ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgVOID tgFX_Effect__Emitter__Render_Write_Quad_Tangent_00(
    STg2_KN_GPU_Vertex_Particle_00_P psVert, STg2_FX__Emitter__Render_Point_CP psPoint, STg2_FX__Emitter__Particle_CP psParticle )
{
    TgVEC_F32_04_1                    vUV;
    TgVEC_F32_04_1                    vE0;
    TgVEC_F32_04_1                    vN0;
    TgVEC_F32_04_1                    vDirTest;
    TgBOOL                              bQuad_Camera_Facing;
    TgRSIZE                             uiVert;

    vE0 = tgMH_SUB_F32_04_1( psPoint->m_avBasis[0], psPoint->m_avBasis[1] );
    vN0 = tgMH_CX_F32_04_1( vE0, psPoint->m_avBasis[1] );
    vDirTest = tgMH_DOT_F32_04_1( vN0, psPoint->m_vCam_Forward );
    bQuad_Camera_Facing = tgCM_NR0_F32( ((TgVEC_S_F32_04_1_P)(&vDirTest))->x );

    if (!bQuad_Camera_Facing)
    {
        for (uiVert = 0; uiVert < 4; ++uiVert)
        {
            vUV = tgMH_MAD_F32_04_1( psPoint->m_vUV_Mask[uiVert], psParticle->m_vUV_01_Scale, psParticle->m_vUV_01_Constant );

            psVert[uiVert].m_vS0 = psPoint->m_avPos_W[uiVert];
            psVert[uiVert].m_vUV = vUV;
            psVert[uiVert].m_vCL = psParticle->m_vColour;
        };
    }
    else
    {
        for (uiVert = 0; uiVert < 4; ++uiVert)
        {
            vUV = tgMH_MAD_F32_04_1( psPoint->m_vUV_Mask[3 - uiVert], psParticle->m_vUV_01_Scale, psParticle->m_vUV_01_Constant );

            psVert[uiVert].m_vS0 = psPoint->m_avPos_W[3 - uiVert];
            psVert[uiVert].m_vUV = vUV;
            psVert[uiVert].m_vCL = psParticle->m_vColour;
        };
    };
}


/* ---- tgFX_Effect__Emitter__Render_Write_Quad_Tangent_01 ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgVOID tgFX_Effect__Emitter__Render_Write_Quad_Tangent_01(
    STg2_KN_GPU_Vertex_Particle_01_P psVert, STg2_FX__Emitter__Render_Point_CP psPoint, STg2_FX__Emitter__Particle_CP psParticle )
{
    TgVEC_F32_04_1                    vUV;
    TgVEC_F32_04_1                    vE0;
    TgVEC_F32_04_1                    vN0;
    TgVEC_F32_04_1                    vDirTest;
    TgBOOL                              bQuad_Camera_Facing;
    TgRSIZE                             uiVert;

    vE0 = tgMH_SUB_F32_04_1( psPoint->m_avBasis[0], psPoint->m_avBasis[1] );
    vN0 = tgMH_CX_F32_04_1( vE0, psPoint->m_avBasis[1] );
    vDirTest = tgMH_DOT_F32_04_1( vN0, psPoint->m_vCam_Forward );
    bQuad_Camera_Facing = tgCM_NR0_F32( ((TgVEC_S_F32_04_1_P)(&vDirTest))->x );

    if (!bQuad_Camera_Facing)
    {
        for (uiVert = 0; uiVert < 4; ++uiVert)
        {
            vUV = tgMH_MAD_F32_04_1( psPoint->m_vUV_Mask[uiVert], psParticle->m_vUV_01_Scale, psParticle->m_vUV_01_Constant );

            psVert[uiVert].m_vS0 = psPoint->m_avPos_W[uiVert];
            psVert[uiVert].m_vT0 = psPoint->m_avBasis[0];
            psVert[uiVert].m_vB0 = psPoint->m_avBasis[1];
            psVert[uiVert].m_vUV = vUV;
            psVert[uiVert].m_vCL = psParticle->m_vColour;
        };
    }
    else
    {
        for (uiVert = 0; uiVert < 4; ++uiVert)
        {
            vUV = tgMH_MAD_F32_04_1( psPoint->m_vUV_Mask[3 - uiVert], psParticle->m_vUV_01_Scale, psParticle->m_vUV_01_Constant );

            psVert[uiVert].m_vS0 = psPoint->m_avPos_W[3 - uiVert];
            psVert[uiVert].m_vT0 = psPoint->m_avBasis[0];
            psVert[uiVert].m_vB0 = psPoint->m_avBasis[1];
            psVert[uiVert].m_vUV = vUV;
            psVert[uiVert].m_vCL = psParticle->m_vColour;
        };
    };
}


#else

/* ---- T(tgFX__Render__Emitter_Render_Generate_Particle) ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F32 T(tgFX__Render__Emitter_Render_Generate_Particle)( STg2_FX_Rnd_Output_PC psRndOut, STg2_RN_Particle_Header_PC psHeader, STg2_FX__Emitter_P psEmitter )
{
    union
    {
        TgUINT_F08_P                        pui;
        T(STg2_KN_GPU_Vertex_Particle)*         ps;
    }                                   sVert;
    TgRSIZE                             uiQuad_Size;
    TgRSIZE                             nuiMaxQuad;
    STg2_FX__Emitter__Render_Point      sPoint;
    STg2_FX__Emitter__Particle_P        psParticle;
    TgUINT_F32                          nuiQuad;
    TgRSIZE                             uiVert;

    /* If there was no room in the buffer, then the error value would be set as the offset value. */
    if (KTgMAX_RSIZE == psHeader->m_uiBuffer_Offset)
    {
        TgERROR(0 == psHeader->m_nbyVertex);
        return (0);
    };

    sVert.pui = psRndOut->m_puiBuffer + psHeader->m_uiBuffer_Offset;
    uiQuad_Size = 6 * sizeof( T(STg2_KN_GPU_Vertex_Particle) );
    nuiMaxQuad = psHeader->m_nbyVertex / uiQuad_Size;

    /* This should not happen, but do not proceed if there is insufficient memory to hold a single quad.*/
    if (0 == nuiMaxQuad)
    {
        TgWARNING(nuiMaxQuad > 0);
        return (0);
    };

    tgMM_Set_U08_0x00( &sPoint, sizeof( sPoint ) );
    sPoint.m_psEmitter = psEmitter;
    tgFX_Effect__Emitter__Render_Init_Point( &sPoint, psRndOut );

    if (ETgFX_PARTICLE_ORIENTATION__VELOCITY_TANGENT == sPoint.m_psExtend->m_psFile_Data__Particle->m_enOrientation)
    {
        return (T(tgFX__Render__Emitter_Render_Generate_Particle_Tangent)( &sPoint, psRndOut, psHeader, psEmitter ));
    };

    tgFX_Effect__Emitter__Reference_Frame( &sPoint, psEmitter->m_vPos_N2W );

    psParticle = sPoint.m_psExtend->m_psParticle_Active;
    nuiQuad = 0;
    while ((nuiQuad < nuiMaxQuad) && (nullptr != psParticle))
    {
        tgRN_Calc_UV_Animation_F32_04_1( &psParticle->m_vUV_01_Constant, &psParticle->m_vUV_01_Scale, psEmitter->m_tiMaterial, psRndOut->m_uDT.m_vF32_04_1, psParticle->m_vLive_Time );
        tgFX_Effect__Emitter__Render_Calculate_Point( &sPoint, psParticle );

        T(tgFX_Effect__Emitter__Render_Write_Quad)( sVert.ps + 6 * nuiQuad, &sPoint, psParticle );
        for (uiVert = 0; uiVert < 4; ++uiVert)
        {
            psEmitter->m_vBA_Max_W = tgMH_MAX_F32_04_1( psEmitter->m_vBA_Max_W, sPoint.m_avPos_W[uiVert] );
            psEmitter->m_vBA_Min_W = tgMH_MIN_F32_04_1( psEmitter->m_vBA_Min_W, sPoint.m_avPos_W[uiVert] );
        };

        ++nuiQuad;
        psParticle = psParticle->m_psNext;
    }

    if (ETgFX_PARTICLE_ORIENTATION__SCREEN_SPACE == sPoint.m_psExtend->m_psFile_Data__Particle->m_enOrientation)
    {
        psEmitter->m_vBA_Max_W = tgMH_SET1_F32_04_1(  KTgMAX_F32 );
        psEmitter->m_vBA_Min_W = tgMH_SET1_F32_04_1( -KTgMAX_F32 );
    }

    return (TgUINT_F32)(6 * nuiQuad);
}


/* ---- T(tgFX__Render__Emitter_Render_Generate_Particle_Tangent) ---------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgUINT_F32 T(tgFX__Render__Emitter_Render_Generate_Particle_Tangent)(
    STg2_FX__Emitter__Render_Point_P psPoint, STg2_FX_Rnd_Output_PC psRndOut, STg2_RN_Particle_Header_PC psHeader, STg2_FX__Emitter_P psEmitter )
{
    union
    {
        TgUINT_F08_P                        pui;
        T(STg2_KN_GPU_Vertex_Particle)*         ps;
    }                                   sVert;
    TgRSIZE                             uiQuad_Size;
    TgRSIZE                             nuiMaxQuad;
    TgVEC_F32_04_1                    vL_Vel_Acceleration_W;
    STg2_FX__Emitter__Particle_P        psParticle;
    TgUINT_F32                          nuiQuad;
    TgVEC_F32_04_1                    vLive_Time_Squared;
    TgVEC_F32_04_1                    vAccel_W;
    TgVEC_F32_04_1                    vVel_W;
    TgRSIZE                             uiVert;

    sVert.pui = psRndOut->m_puiBuffer + psHeader->m_uiBuffer_Offset;
    uiQuad_Size = 6 * sizeof( T(STg2_KN_GPU_Vertex_Particle) );
    nuiMaxQuad = psHeader->m_nbyVertex / uiQuad_Size;
    TgERROR( nuiMaxQuad >= 1 );

    vL_Vel_Acceleration_W = psPoint->m_psExtend->m_psFile_Data__Particle->m_vL_Vel_Acceleration_W;

    psParticle = psPoint->m_psExtend->m_psParticle_Active;
    nuiQuad = 0;
    while ((nuiQuad < nuiMaxQuad) && (nullptr != psParticle))
    {
        vLive_Time_Squared = tgMH_MUL_F32_04_1( psParticle->m_vLive_Time, psParticle->m_vLive_Time );
        vAccel_W = tgMH_MUL_F32_04_1( vL_Vel_Acceleration_W, vLive_Time_Squared );
        vAccel_W = tgMH_MUL_F32_04_1( tgMH_SET1_F32_04_1( 0.5F ), vAccel_W );
        vVel_W = tgMH_ADD_F32_04_1( psParticle->m_vLVel_W, vAccel_W );

        psPoint->m_vRight = tgMH_NORM_F32_04_1( vVel_W );
        psPoint->m_vUp = tgMH_UCX_F32_04_1( psPoint->m_vCam_Forward, psPoint->m_vRight );

        tgRN_Calc_UV_Animation_F32_04_1( &psParticle->m_vUV_01_Constant, &psParticle->m_vUV_01_Scale, psEmitter->m_tiMaterial, psRndOut->m_uDT.m_vF32_04_1, psParticle->m_vLive_Time );
        tgFX_Effect__Emitter__Render_Calculate_Point( psPoint, psParticle );

        T(tgFX_Effect__Emitter__Render_Write_Quad_Tangent)( sVert.ps + 6 * nuiQuad, psPoint, psParticle );

        for (uiVert = 0; uiVert < 4; ++uiVert)
        {
            psEmitter->m_vBA_Max_W = tgMH_MAX_F32_04_1( psEmitter->m_vBA_Max_W, psPoint->m_avPos_W[uiVert] );
            psEmitter->m_vBA_Min_W = tgMH_MIN_F32_04_1( psEmitter->m_vBA_Min_W, psPoint->m_avPos_W[uiVert] );
        };

        ++nuiQuad;
    }

    return (TgUINT_F32)(6 * nuiQuad);
}


/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* == Effect ===================================================================================================================================================================== */

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif

