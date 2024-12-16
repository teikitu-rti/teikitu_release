/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Emitter - Update - Particle.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Effect - Internal.inl"


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgFX__Update__Emitter_Update_Particle__Update_Anim_Data(
    STg2_FX__Emitter__Particle_P TgANALYSIS_NO_NULL OUT0, STg2_FX__Emitter_P TgANALYSIS_NO_NULL ARG1, TgVEC_F32_04_1 ARG2 );

static TgVOID
tgFX__Update__Emitter_Update_Particle__Init(
    STg2_FX__Emitter__Particle_P TgANALYSIS_NO_NULL OUT0, STg2_FX__Emitter_P TgANALYSIS_NO_NULL ARG1, TgVEC_F32_04_1 ARG2, TgVEC_F32_04_1 ARG3 );

static TgVOID
tgFX__Update__Emitter_Update_Particle__Update_W(
    STg2_FX__Emitter_P TgANALYSIS_NO_NULL OUT0, STg2_FX__Emitter__Particle_P TgANALYSIS_NO_NULL ARG1 );

static TgVOID
tgFX_Effect__Emitter__Update__Update_Particle__Update_N(
    STg2_FX__Emitter_P TgANALYSIS_NO_NULL OUT0, STg2_FX__Emitter__Particle_P TgANALYSIS_NO_NULL ARG1 );

static TgBOOL
tgFX__Update__Emitter_Update_Particle__Update(
    STg2_FX__Emitter_P TgANALYSIS_NO_NULL OUT0, STg2_FX__Emitter__Particle_P TgANALYSIS_NO_NULL ARG1, TgFLOAT32_C ARG2, TgVEC_F32_04_1 ARG3 );

static TgVOID
tgFX__Update__Emitter_Update_Particle__Update_Collision(
    STg2_FX__Emitter_P TgANALYSIS_NO_NULL OUT0, STg2_FX__Emitter__Particle_P TgANALYSIS_NO_NULL ARG1, TgFLOAT32_C ARG2, TgVEC_F32_04_1 ARG3, TgVEC_F32_04_1 ARG4 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__File__Particle_Patch_File_Data ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__File__Particle_Patch_File_Data( STg2_FX_Particle__File_Data_P psData )
{
    TgUINT_PTR                          uiData_Top;

    uiData_Top = (TgUINT_PTR)psData;

    psData->m_sAnim.m_sData_Offset.m_uiPos_N += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiRot_N += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiLVel_N += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiSpin += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiTurbulence += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiSize += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiColour += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiNew_Effect_Hash += uiData_Top;
}


/* ---- tgFX__Update__Emitter_Add_Particle --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Emitter_Add_Particle( STg2_FX__Emitter_P psEmitter, TgRSIZE nuiParticle )
{
    /* Commit the necessary memory for the particles */
    if ((psEmitter->m_sExtend.m_nuiParticle + nuiParticle) > psEmitter->m_sExtend.m_nuiParticle_Commit)
    {
        TgRSIZE                             nuiParticle_Commit;
        TgRSIZE                             uiCommit;
        TgRSIZE                             uiIndex;

        nuiParticle_Commit = tgCM_MIN_UMAX( psEmitter->m_sExtend.m_nuiParticle + nuiParticle, psEmitter->m_sExtend.m_nuiParticle_Max );
        uiCommit = 1 + nuiParticle_Commit * sizeof( STg2_FX__Emitter__Particle ) / tgMM_Page_Size();
        if (nullptr == TgCOMMIT_VIRTUAL( psEmitter->m_sExtend.m_psParticle_Memory, 0, tgMM_Page_Size()*uiCommit ))
        {
            return;
        };

        nuiParticle_Commit = tgMM_Page_Size()*uiCommit / sizeof( STg2_FX__Emitter__Particle );
        for (uiIndex = psEmitter->m_sExtend.m_nuiParticle_Commit; uiIndex + 1 < nuiParticle_Commit; ++uiIndex)
        {
            psEmitter->m_sExtend.m_psParticle_Memory[uiIndex].m_psNext = psEmitter->m_sExtend.m_psParticle_Memory + uiIndex + 1;
        };
        psEmitter->m_sExtend.m_psParticle_Memory[uiIndex].m_psNext = psEmitter->m_sExtend.m_psParticle_Free;
        psEmitter->m_sExtend.m_psParticle_Free = psEmitter->m_sExtend.m_psParticle_Memory + psEmitter->m_sExtend.m_nuiParticle_Commit;
        psEmitter->m_sExtend.m_nuiParticle_Commit = nuiParticle_Commit;
    };

    if ((psEmitter->m_sExtend.m_nuiParticle + nuiParticle) > psEmitter->m_sExtend.m_nuiParticle_Commit)
    {
        TgERROR(false);
        return; /* WTF - Should not be possible */
    };

    while (nuiParticle)
    {
        STg2_FX_Emitter__File_Data_CP       psFile_Data;
        STg2_FX_Particle__File_Data_CP      psFile_Data__Particle;
        STg2_FX__Emitter__Particle_P        psParticle;
        TgUN_V128                           uNorm_Rnd;
        TgUN_V128                           uLength;
        TgUN_V128                           uPos_N;

        psFile_Data = psEmitter->m_psFile_Data;
        psFile_Data__Particle = psEmitter->m_sExtend.m_psFile_Data__Particle;
        psParticle = psEmitter->m_sExtend.m_psParticle_Free;

        if (nullptr == psParticle)
        {
            TgERROR(false);
            return; /* WTF - Should not be possible */
        };

        psEmitter->m_sExtend.m_psParticle_Free = psParticle->m_psNext;
        psParticle->m_psNext = nullptr;

        uPos_N.m_vF32_04_1 = tgMH_SET1_F32_04_1( 0.0F );

        do
        {
            uNorm_Rnd.m_vF32_04_1 = tgMH_RAND_ONE_F32_04_1();
            uNorm_Rnd.m_vS_F32_04_1.y = tgPM_ABS_F32( uNorm_Rnd.m_vS_F32_04_1.y );
            uNorm_Rnd.m_vS_F32_04_1.w = 0.0F;
            uNorm_Rnd.m_vF32_04_1 = tgMH_NORM_LEN_F32_04_1( &uLength.m_vF32_04_1, uNorm_Rnd.m_vF32_04_1 );
        } while (uLength.m_vS_F32_04_1.x < KTgEPS_F32);

        switch (psFile_Data->m_enEmission_Shape)
        {
            case ETgFX_EMISSION_SHAPE__POINT:
                break;

            case ETgFX_EMISSION_SHAPE__SPHERE:
            {
                TgVEC_F32_04_1                      vEmission_Rnd;

                vEmission_Rnd = tgMH_MUL_F32_04_1( tgMH_RAND_ONE_F32_04_1(), psEmitter->m_sExtend.m_vEmission_Shape );
                uPos_N.m_vF32_04_1 = tgMH_Init_Point_F32_04_1( tgMH_MUL_F32_04_1( uNorm_Rnd.m_vF32_04_1, vEmission_Rnd ) );
            };
            break;
            
            case ETgFX_EMISSION_SHAPE__BOX:
            {
                uPos_N.m_vF32_04_1 = tgMH_Init_Point_F32_04_1( tgMH_MUL_F32_04_1( tgMH_RAND_ONE_F32_04_1(), psEmitter->m_sExtend.m_vEmission_Shape ) );
            };
            break;

            case ETgFX_EMISSION_SHAPE__DISK:
            {
                uPos_N.m_vF32_04_1 = KTgZERO_F32_04_1;
                tgPM_SINCOS_F32( &uPos_N.m_vS_F32_04_1.x, &uPos_N.m_vS_F32_04_1.z, tgCM_RAND_ONE_F32() * KTgPI_F32 );
                uPos_N.m_vF32_04_1 = tgMH_MUL_F32_04_1( uPos_N.m_vF32_04_1, tgMH_MUL_F32_04_1( tgMH_RAND_ONE_F32_04_1(), psEmitter->m_sExtend.m_vEmission_Shape ) );
                uPos_N.m_vF32_04_1 = tgMH_Init_Point_F32_04_1( uPos_N.m_vF32_04_1 );
            };
            break;

            case ETgFX_EMISSION_SHAPE__CIRCLE:
            {
                uPos_N.m_vF32_04_1 = KTgZERO_F32_04_1;
                tgPM_SINCOS_F32( &uPos_N.m_vS_F32_04_1.x, &uPos_N.m_vS_F32_04_1.z, tgCM_RAND_ONE_F32() * KTgPI_F32 );
                uPos_N.m_vF32_04_1 = tgMH_Init_Point_F32_04_1( tgMH_MUL_F32_04_1( uPos_N.m_vF32_04_1, psEmitter->m_sExtend.m_vEmission_Shape ) );
                do
                {
                    uNorm_Rnd.m_vF32_04_1 = uPos_N.m_vF32_04_1;
                    uNorm_Rnd.m_vS_F32_04_1.y = tgPM_ABS_F32( tgCM_RAND_ONE_F32() );
                    uNorm_Rnd.m_vS_F32_04_1.w = 0.0F;
                    uNorm_Rnd.m_vF32_04_1 = tgMH_NORM_LEN_F32_04_1( &uLength.m_vF32_04_1, uNorm_Rnd.m_vF32_04_1 );
                } while (uLength.m_vS_F32_04_1.x < KTgEPS_F32);
            };
            break;

            case ETgFX_EMISSION_SHAPE__VELOCITY:
            {
                uPos_N.m_vF32_04_1 = tgMH_Init_Point_F32_04_1( tgMH_MUL_F32_04_1( uNorm_Rnd.m_vF32_04_1, psEmitter->m_sExtend.m_vEmission_Shape ) );
            };
            break;
        };

        if (psFile_Data__Particle->m_enOrientation == ETgFX_PARTICLE_ORIENTATION__SCREEN_SPACE)
        {
            uPos_N.m_vF32_04_1 = tgMH_RAND_F32_04_1();
            uPos_N.m_vS_F32_04_1.z = 0.0f;
            uPos_N.m_vS_F32_04_1.w = 1.0f;
            tgFX__Update__Emitter_Update_Particle__Init( psParticle, psEmitter, uPos_N.m_vF32_04_1, KTgZERO_F32_04_1 );
        }
        else
        {
            tgFX__Update__Emitter_Update_Particle__Init( psParticle, psEmitter, uPos_N.m_vF32_04_1, uNorm_Rnd.m_vF32_04_1 );
        };

        ++psEmitter->m_sExtend.m_nuiParticle;
        --nuiParticle;
        psParticle->m_psNext = psEmitter->m_sExtend.m_psParticle_Active;
        psEmitter->m_sExtend.m_psParticle_Active = psParticle;
    };
}


/* ---- tgFX__Update__Emitter_Update_Particle ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Emitter_Update_Particle( STg2_FX__Emitter_P psEmitter, TgFLOAT32_C fDT, TgVEC_F32_04_1 vdT )
{
    STg2_FX__Emitter__Particle_P        psPrev_Particle;
    STg2_FX__Emitter__Particle_P        psParticle;

    psPrev_Particle = nullptr;
    psParticle = psEmitter->m_sExtend.m_psParticle_Active;
    while (psParticle)
    {
        psParticle = psParticle->m_psNext;
    };

    psParticle = psEmitter->m_sExtend.m_psParticle_Active;
    while (psParticle)
    {
        if (!tgFX__Update__Emitter_Update_Particle__Update( psEmitter, psParticle, fDT, vdT ))
        {
            STg2_FX__Emitter__Particle_P        psNext_Particle;

            psNext_Particle = psParticle->m_psNext;
            psParticle->m_psNext = psEmitter->m_sExtend.m_psParticle_Free;
            psEmitter->m_sExtend.m_psParticle_Free = psParticle;

            if (psPrev_Particle)
            {
                psPrev_Particle->m_psNext = psNext_Particle;
                psParticle = psNext_Particle;
            }
            else
            {
                psEmitter->m_sExtend.m_psParticle_Active = psNext_Particle;
                psParticle = psNext_Particle;
            };

            TgDIAG( psEmitter->m_sExtend.m_nuiParticle );
            --psEmitter->m_sExtend.m_nuiParticle;
        }
        else
        {
            psPrev_Particle = psParticle;
            psParticle = psParticle->m_psNext;
        };
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Update__Emitter_Update_Particle ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX__Update__Emitter_Update_Particle__Update_Anim_Data( STg2_FX__Emitter__Particle_P psParticle, STg2_FX__Emitter_P psEmitter, TgVEC_F32_04_1 vDT )
{
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    STg2_FX_Particle__File_Data_CPC     psFile_Data__Particle = psEmitter->m_sExtend.m_psFile_Data__Particle;
    TgVEC_F32_04_1                      vSize;

    if (psFile_Data__Particle->m_sAnim.m_sParameter.m_psPos_N)
    {
        tgFX_Evaluate_AnimData_F32_04_1( &psParticle->m_vPos_Anim_RT, psFile_Data__Particle->m_sAnim.m_sParameter.m_psPos_N, psParticle->m_vLive_Time );
    }
    else
    {
        psParticle->m_vPos_Anim_RT = KTgZERO_F32_04_1;
    };

    if (psFile_Data__Particle->m_sAnim.m_sParameter.m_psRot_N)
    {
        TgVEC_F32_04_1                      vRot_N;

        tgFX_Evaluate_AnimData_F32_04_1( &vRot_N, psFile_Data__Particle->m_sAnim.m_sParameter.m_psRot_N, psParticle->m_vLive_Time );
        psParticle->m_qRot_Anim_RT = tgMH_QT_MUL_F32_04_1( vRot_N, psParticle->m_vRot_Variance );
    }
    else
    {
        psParticle->m_qRot_Anim_RT = KTgUNIT_W_F32_04_1;
    };

    if (psFile_Data__Particle->m_sAnim.m_sParameter.m_psLVel_N)
    {
        tgFX_Integrate_AnimData_F32_04_1( &psParticle->m_vLVel_NT, psFile_Data__Particle->m_sAnim.m_sParameter.m_psLVel_N, psParticle->m_vLive_Time, vDT );
        psParticle->m_vLVel_NT = tgMH_MAD_F32_04_1( psParticle->m_vLVel_Variance, psParticle->m_vLive_Time, psParticle->m_vLVel_NT );
        psParticle->m_vLVel_NT = tgMH_MUL_F32_04_1( psParticle->m_vSpawn_LVel_N, psParticle->m_vLVel_NT );
    }
    else
    {
        psParticle->m_vLVel_NT = KTgZERO_F32_04_1;
    };

    tgFX_Evaluate_AnimData_F32_04_1( &psParticle->m_vSpin, psFile_Data__Particle->m_sAnim.m_sParameter.m_psSpin, psParticle->m_vLive_Time );
    psParticle->m_vSpin = tgMH_SPX_F32_04_1( psParticle->m_vSpin );

    tgFX_Evaluate_AnimData_F32_04_1( &psParticle->m_vTurbulence, psFile_Data__Particle->m_sAnim.m_sParameter.m_psTurbulence, psParticle->m_vLive_Time );
    psParticle->m_vTurbulence = tgMH_SPX_F32_04_1( psParticle->m_vTurbulence );

    tgFX_Evaluate_AnimData_F32_04_1( &vSize, psFile_Data__Particle->m_sAnim.m_sParameter.m_psSize, psParticle->m_vLive_Time );
    vSize = tgMH_SUB_F32_04_1( vSize, psParticle->m_vSize_Variance );
    vSize = tgMH_MAX_F32_04_1( vSize, tgMH_SET1_F32_04_1( 0.0F ) );
    psParticle->m_vSize_X = tgMH_SPX_F32_04_1( vSize );
    psParticle->m_vSize_Y = tgMH_SPY_F32_04_1( vSize );

#if TgS_DEBUG__EFFECT
    {
        TgBOOL                              bDraw;

        if ((tgCN_Var_Query_Bool( &bDraw, g_tiFX_Debug__Emitter__Draw_Debug_Colour )) && (!bDraw))
        {
            tgFX_Evaluate_AnimData_F32_04_1( &psParticle->m_vColour, psFile_Data__Particle->m_sAnim.m_sParameter.m_psColour, psParticle->m_vLive_Time );
        };
    }
/*# TgS_DEBUG__EFFECT */
#else
    tgFX_Evaluate_AnimData_F32_04_1( &psParticle->m_vColour, psFile_Data__Particle->m_sAnim.m_sParameter.m_psColour, psParticle->m_vLive_Time );
/*# TgS_DEBUG__EFFECT */
#endif

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#else
    (void)psParticle;
    (void)psEmitter;
    (void)vDT;
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
}


/* ---- tgFX__Update__Emitter_Update_Particle ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX__Update__Emitter_Update_Particle__Init( STg2_FX__Emitter__Particle_P psParticle, STg2_FX__Emitter_P psEmitter, TgVEC_F32_04_1 vPos_N, TgVEC_F32_04_1 vVel_N )
{
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    STg2_FX_Particle__File_Data_CP      psFile_Data__Particle;
    TgVEC_F32_04_1                      vSize_Variance;
    TgVEC_F32_04_1                      vRot_Variance;
    TgVEC_F32_04_1                      vLVel_Variance;
    TgVEC_F32_04_1                      vRVel_Acceleration;
    TgFLOAT32                           fCollision_Restitution;

    psFile_Data__Particle = psEmitter->m_sExtend.m_psFile_Data__Particle;

    vSize_Variance = tgMH_MAD_F32_04_1( tgMH_RAND_F32_04_1(), psFile_Data__Particle->m_vSize_Variance_RNG, psFile_Data__Particle->m_vSize_Variance_MID );
    vRot_Variance = tgMH_MAD_F32_04_1( tgMH_RAND_F32_04_1(), psFile_Data__Particle->m_vRot_Variance_RNG, psFile_Data__Particle->m_vRot_Variance_MID );
    vLVel_Variance = tgMH_MAD_F32_04_1( tgMH_RAND_F32_04_1(), psFile_Data__Particle->m_vLVel_Variance_RNG, psFile_Data__Particle->m_vLVel_Variance_MID );
    vRVel_Acceleration = tgMH_MAD_F32_04_1( tgMH_RAND_F32_04_1(), psFile_Data__Particle->m_vRVel_Acceleration_RNG, psFile_Data__Particle->m_vRVel_Acceleration_MID );
    fCollision_Restitution = tgCM_RAND_ONE_F32()*psFile_Data__Particle->m_fContact_Restitution_RNG + psFile_Data__Particle->m_fContact_Restitution_MID;

    psParticle->m_vCollision_Restitution = tgMH_SET1_F32_04_1( fCollision_Restitution );
    psParticle->m_vSize_Variance = vSize_Variance;
    psParticle->m_vRot_Variance = vRot_Variance;
    psParticle->m_vLVel_Variance = vLVel_Variance;
    psParticle->m_vRVel_Acceleration = vRVel_Acceleration;
    psParticle->m_vSpawn_Pos_R2N = vPos_N;
    psParticle->m_vSpawn_Pos_N2W = psEmitter->m_vPos_N2W;
    psParticle->m_vSpawn_Rot_R2N = KTgUNIT_W_F32_04_1;
    psParticle->m_vSpawn_Rot_N2W = psEmitter->m_qRot_N2W;
    psParticle->m_vSpawn_LVel_N = vVel_N;

    tgFX__Update__Emitter_Update_Particle__Update_Anim_Data( psParticle, psEmitter, KTgZERO_F32_04_1 );
    psParticle->m_vLive_Time = tgMH_SET1_F32_04_1( 0.0F );
    psParticle->m_vLife_Time = tgMH_SET1_F32_04_1( tgCM_MAX_F32( 0.0F, tgCM_RAND_ONE_F32()*psFile_Data__Particle->m_fTime_RNG + psFile_Data__Particle->m_fTime_MID ) );
    tgFX__Update__Emitter_Update_Particle__Update_W( psEmitter, psParticle );


#if TgS_DEBUG__EFFECT
    {
        TgBOOL                              bDraw;

        tgCN_Var_Set_Bool( g_tiFX_Debug__Emitter__Draw_Debug_Colour, true );

        if ((tgCN_Var_Query_Bool( &bDraw, g_tiFX_Debug__Emitter__Draw_Debug_Colour )) && (bDraw))
        {
            TgUN_V128                           uCL;

            uCL.m_vF32_04_1 = tgMH_Init_Point_F32_04_1( tgMH_RAND_F32_04_1() );
            uCL.m_vS_F32_04_1.w = 0.5F;
            psParticle->m_vColour = uCL.m_vF32_04_1;
        };
    }
/*# TgS_DEBUG__EFFECT */
#endif

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#else
    (void)psParticle;
    (void)psEmitter;
    (void)vPos_N;
    (void)vVel_N;
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
}


/* ---- tgFX__Update__Emitter_Update_Particle ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX__Update__Emitter_Update_Particle__Update_W( STg2_FX__Emitter_P psEmitter, STg2_FX__Emitter__Particle_P psParticle )
{
    TgVEC_F32_04_1                      vL_Vel_Acceleration_W;
    TgVEC_F32_04_1                      vAccelTerm;

    if (0 != (ETgFX_EMITTER_FLAGS__EMISSION__ROTATION_CURRENT_RELATIVE & psEmitter->m_psFile_Data->m_uiFlags))
    {
        psParticle->m_vPos_W = tgMH_QT_TX_F32_04_1( psParticle->m_vPos_Anim_RT, psParticle->m_vSpawn_Rot_R2N );
        psParticle->m_vPos_W = tgMH_ADD_F32_04_1( psParticle->m_vPos_W, psParticle->m_vSpawn_Pos_R2N );
        psParticle->m_vPos_W = tgMH_QT_TX_F32_04_1( psParticle->m_vPos_W, psEmitter->m_qRot_N2W );

        psParticle->m_qRot_N2W = tgMH_QT_MUL_F32_04_1( psParticle->m_qRot_Anim_RT, psParticle->m_vSpawn_Rot_R2N );
        psParticle->m_qRot_N2W = tgMH_QT_MUL_F32_04_1( psParticle->m_qRot_N2W, psEmitter->m_qRot_N2W );

        psParticle->m_vLVel_WT = tgMH_QT_MUL_F32_04_1( psParticle->m_vLVel_NT, psParticle->m_vSpawn_Rot_R2N );
        psParticle->m_vLVel_WT = tgMH_QT_MUL_F32_04_1( psParticle->m_vLVel_NT, psEmitter->m_qRot_N2W );
    }
    else if (0 != (ETgFX_EMITTER_FLAGS__EMISSION__ROTATION_START_RELATIVE & psEmitter->m_psFile_Data->m_uiFlags))
    {
        psParticle->m_vPos_W = tgMH_QT_TX_F32_04_1( psParticle->m_vPos_Anim_RT, psParticle->m_vSpawn_Rot_R2N );
        psParticle->m_vPos_W = tgMH_ADD_F32_04_1( psParticle->m_vPos_W, psParticle->m_vSpawn_Pos_R2N );
        psParticle->m_vPos_W = tgMH_QT_TX_F32_04_1( psParticle->m_vPos_W, psParticle->m_vSpawn_Rot_N2W );

        psParticle->m_qRot_N2W = tgMH_QT_MUL_F32_04_1( psParticle->m_qRot_Anim_RT, psParticle->m_vSpawn_Rot_R2N );
        psParticle->m_qRot_N2W = tgMH_QT_MUL_F32_04_1( psParticle->m_qRot_N2W, psParticle->m_vSpawn_Rot_N2W );

        psParticle->m_vLVel_WT = tgMH_QT_MUL_F32_04_1( psParticle->m_vLVel_NT, psParticle->m_vSpawn_Rot_R2N );
        psParticle->m_vLVel_WT = tgMH_QT_MUL_F32_04_1( psParticle->m_vLVel_NT, psParticle->m_vSpawn_Rot_N2W );
    }
    else
    {
        psParticle->m_vPos_W = psParticle->m_vSpawn_Pos_R2N;
        psParticle->m_qRot_N2W = psParticle->m_vSpawn_Rot_R2N;
        psParticle->m_vLVel_WT = tgMH_QT_MUL_F32_04_1( psParticle->m_vLVel_NT, psParticle->m_vSpawn_Rot_R2N );
    };

    if (0 != (ETgFX_EMITTER_FLAGS__EMISSION__POSITION_CURRENT_RELATIVE & psEmitter->m_psFile_Data->m_uiFlags))
    {
        psParticle->m_vPos_W = tgMH_ADD_F32_04_1( psParticle->m_vPos_W, psEmitter->m_vPos_N2W );
    }
    else if (psEmitter->m_sExtend.m_psFile_Data__Particle->m_enOrientation != ETgFX_PARTICLE_ORIENTATION__SCREEN_SPACE)
    {
        psParticle->m_vPos_W = tgMH_ADD_F32_04_1( psParticle->m_vPos_W, psParticle->m_vSpawn_Pos_N2W );
    }

    vL_Vel_Acceleration_W = psEmitter->m_sExtend.m_psFile_Data__Particle->m_vL_Vel_Acceleration_W;
    if (0 != (ETgFX_EMITTER_FLAGS__EMISSION__EMITTER_ATTRACTOR & psEmitter->m_psFile_Data->m_uiFlags))
    {
        TgVEC_F32_04_1                    vDist_W;

        vDist_W = tgMH_SUB_F32_04_1( psParticle->m_vPos_W, psEmitter->m_vPos_W );
        vL_Vel_Acceleration_W = tgMH_MAD_F32_04_1( tgMH_SET1_F32_04_1( psEmitter->m_psFile_Data->m_fEmitter_Attraction ), vDist_W, vL_Vel_Acceleration_W );
    };

    vAccelTerm = tgMH_MUL_F32_04_1( tgMH_MUL_F32_04_1( tgMH_SET1_F32_04_1( 0.5F ), psParticle->m_vLive_Time ), psParticle->m_vLive_Time );
    psParticle->m_vPos_W =tgMH_ADD_F32_04_1( psParticle->m_vPos_W, psParticle->m_vLVel_WT );
    psParticle->m_vPos_W = tgMH_MAD_F32_04_1( vAccelTerm, vL_Vel_Acceleration_W, psParticle->m_vPos_W );
}


/* ---- tgFX__Update__Emitter_Update_Particle ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX_Effect__Emitter__Update__Update_Particle__Update_N( STg2_FX__Emitter_P psEmitter, STg2_FX__Emitter__Particle_P psParticle )
{
    TgVEC_F32_04_1                      vL_Vel_Acceleration_W;
    TgVEC_F32_04_1                      vAccelTerm;
    TgVEC_F32_04_1                      vPos_Temp;

    vL_Vel_Acceleration_W = psEmitter->m_sExtend.m_psFile_Data__Particle->m_vL_Vel_Acceleration_W;
    if (0 != (ETgFX_EMITTER_FLAGS__EMISSION__EMITTER_ATTRACTOR & psEmitter->m_psFile_Data->m_uiFlags))
    {
        TgVEC_F32_04_1                    vDist_W;

        vDist_W = tgMH_SUB_F32_04_1( psParticle->m_vPos_W, psEmitter->m_vPos_W );
        vL_Vel_Acceleration_W = tgMH_MAD_F32_04_1( tgMH_SET1_F32_04_1( psEmitter->m_psFile_Data->m_fEmitter_Attraction ), vDist_W, vL_Vel_Acceleration_W );
    };

    vAccelTerm = tgMH_MUL_F32_04_1( tgMH_MUL_F32_04_1( tgMH_SET1_F32_04_1( 0.5F ), psParticle->m_vLive_Time ), psParticle->m_vLive_Time );
    vPos_Temp = tgMH_SUB_F32_04_1( psParticle->m_vPos_W, tgMH_MUL_F32_04_1( vAccelTerm, vL_Vel_Acceleration_W ) );

    if (0 != (ETgFX_EMITTER_FLAGS__EMISSION__POSITION_CURRENT_RELATIVE & psEmitter->m_psFile_Data->m_uiFlags))
    {
        vPos_Temp = tgMH_SUB_F32_04_1( vPos_Temp, psEmitter->m_vPos_N2W );
    }
    else if (psEmitter->m_sExtend.m_psFile_Data__Particle->m_enOrientation != ETgFX_PARTICLE_ORIENTATION__SCREEN_SPACE)
    {
        vPos_Temp = tgMH_SUB_F32_04_1( vPos_Temp, psParticle->m_vSpawn_Pos_N2W );
    };

    if (0 != (ETgFX_EMITTER_FLAGS__EMISSION__ROTATION_CURRENT_RELATIVE & psEmitter->m_psFile_Data->m_uiFlags))
    {
        TgVEC_F32_04_1                    qRot_W2N = tgMH_QT_INV_F32_04_1( psEmitter->m_qRot_N2W );

        psParticle->m_vSpawn_Pos_R2N = tgMH_QT_TX_F32_04_1( vPos_Temp, qRot_W2N );
        psParticle->m_vSpawn_Rot_R2N = tgMH_QT_MUL_F32_04_1( psParticle->m_qRot_N2W, qRot_W2N );
        psParticle->m_vSpawn_LVel_N = tgMH_QT_TX_F32_04_1( psParticle->m_vLVel_W, qRot_W2N );
    }
    else if (0 != (ETgFX_EMITTER_FLAGS__EMISSION__ROTATION_START_RELATIVE & psEmitter->m_psFile_Data->m_uiFlags))
    {
        TgVEC_F32_04_1                    qInv_Rot = tgMH_QT_INV_F32_04_1( psParticle->m_vSpawn_Rot_N2W );

        psParticle->m_vSpawn_Pos_R2N = tgMH_QT_TX_F32_04_1( vPos_Temp, qInv_Rot );
        psParticle->m_vSpawn_Rot_R2N = tgMH_QT_MUL_F32_04_1( psParticle->m_qRot_N2W, qInv_Rot );
        psParticle->m_vSpawn_LVel_N = tgMH_QT_TX_F32_04_1( psParticle->m_vLVel_W, qInv_Rot );
    }
    else
    {
        TgVEC_F32_04_1                    qInv_Rot = tgMH_QT_INV_F32_04_1( psParticle->m_vSpawn_Rot_N2W );

        psParticle->m_vSpawn_Pos_R2N = vPos_Temp;
        psParticle->m_vSpawn_Rot_R2N = psParticle->m_qRot_N2W;
        psParticle->m_vSpawn_LVel_N = tgMH_QT_TX_F32_04_1( psParticle->m_vLVel_W, qInv_Rot );
    };

    if (psEmitter->m_sExtend.m_psFile_Data__Particle->m_sAnim.m_sParameter.m_psRot_N)
    {
        TgVEC_F32_04_1                      vInv_Rot_N;

        tgFX_Evaluate_AnimData_F32_04_1( &vInv_Rot_N, psEmitter->m_sExtend.m_psFile_Data__Particle->m_sAnim.m_sParameter.m_psRot_N, psParticle->m_vLive_Time );
        vInv_Rot_N = tgMH_QT_MUL_F32_04_1( vInv_Rot_N, psParticle->m_vRot_Variance );
        vInv_Rot_N = tgMH_QT_INV_F32_04_1( vInv_Rot_N );
        psParticle->m_vSpawn_Rot_R2N = tgMH_QT_MUL_F32_04_1( vInv_Rot_N, psParticle->m_vSpawn_Rot_R2N );
    };

    if (psEmitter->m_sExtend.m_psFile_Data__Particle->m_sAnim.m_sParameter.m_psPos_N)
    {
        TgVEC_F32_04_1                      vPos_N;

        tgFX_Evaluate_AnimData_F32_04_1( &vPos_N, psEmitter->m_sExtend.m_psFile_Data__Particle->m_sAnim.m_sParameter.m_psPos_N, psParticle->m_vLive_Time );
        vPos_N = tgMH_QT_TX_F32_04_1( vPos_N, psParticle->m_vSpawn_Rot_R2N );
        psParticle->m_vSpawn_Pos_R2N = tgMH_SUB_F32_04_1( vPos_N, psParticle->m_vSpawn_Pos_R2N );
    };
}


/* ---- tgFX__Update__Emitter_Update_Particle ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL tgFX__Update__Emitter_Update_Particle__Update( STg2_FX__Emitter_P psEmitter, STg2_FX__Emitter__Particle_P psParticle, TgFLOAT32_C fDT, TgVEC_F32_04_1 vDT )
{
    STg2_FX_Particle__File_Data_CP      psFile_Data__Particle;
    TgUINT_MAX                          uiEffect_Hash;
    TgVEC_F32_04_1                      vPrev_Pos_W;
    TgRESULT                            iRet;
    TgUN_V128                           uLive_Time;

    if (tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_CMP_LT_F32_04_1(psParticle->m_vLife_Time,vDT)))
    {
        return (false);
    };

    psParticle->m_vLive_Time = tgMH_ADD_F32_04_1( psParticle->m_vLive_Time, vDT );
    psParticle->m_vLife_Time = tgMH_SUB_F32_04_1( psParticle->m_vLife_Time, vDT );
    uLive_Time.m_vF32_04_1 = psParticle->m_vLive_Time;
    psFile_Data__Particle = psEmitter->m_sExtend.m_psFile_Data__Particle;

    vPrev_Pos_W = psParticle->m_vPos_W;
    tgFX__Update__Emitter_Update_Particle__Update_Anim_Data( psParticle, psEmitter, vDT );
    tgFX__Update__Emitter_Update_Particle__Update_W( psEmitter, psParticle );

    iRet = tgFX_Evaluate_Single_AnimData_UXX( &uiEffect_Hash, psFile_Data__Particle->m_sAnim.m_sParameter.m_psNew_Effect_Hash, uLive_Time.m_vS_F32_04_1.x );
    if (TgSUCCEEDED(iRet) && KTgEMPTY_HASH != uiEffect_Hash)
    {
        STg2_FX_Instance                    sInstance;

        tgMM_Set_U08_0x00( &sInstance, sizeof( sInstance ) );
        while (TgSUCCEEDED(iRet) && KTgEMPTY_HASH != uiEffect_Hash)
        {
            sInstance.m_vPos_N2W = psParticle->m_vPos_W;
            sInstance.m_vNormal = psParticle->m_vLVel_W;
            sInstance.m_vScale = psEmitter->m_vScale;
            sInstance.m_qRot_N2W = psParticle->m_qRot_N2W;
            sInstance.m_tiParent = psEmitter->m_tiClient;

            tgFX__Update__Command__Emitter_Create( uiEffect_Hash, &sInstance );
            iRet = tgFX_Evaluate_Single_AnimData_UXX( &uiEffect_Hash, psFile_Data__Particle->m_sAnim.m_sParameter.m_psNew_Effect_Hash, fDT );
        };
    };

    if (0 != (ETgFX_EMITTER_FLAGS__EMISSION__PARTICLE_COLLIDE_MASK & psEmitter->m_psFile_Data->m_uiFlags))
    {
        tgFX__Update__Emitter_Update_Particle__Update_Collision( psEmitter, psParticle, fDT, vDT, vPrev_Pos_W );
    };

    return (true);
}


/* ---- tgFX__Update__Emitter_Update_Particle__Update_Collision ------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX__Update__Emitter_Update_Particle__Update_Collision(
    STg2_FX__Emitter_P psEmitter, STg2_FX__Emitter__Particle_P psParticle, TgATTRIBUTE_UNUSED TgFLOAT32_C fDT, TgATTRIBUTE_UNUSED TgVEC_F32_04_1 vdT, TgVEC_F32_04_1 vPrev_Pos_W )
{
    STg2_SE_CO_Request_F32_04           sRequest;
    STg2_CO_Contact_F32_04_P            psContact;
    TgVEC_F32_04_1                      vLVelW_Normal;
    TgVEC_F32_04_1                      vBounce;
    TgVEC_F32_04_1                      vLVel_W;
    TgVEC_F32_04_1                      vPos_Dist;
    TgUN_V128                           uPos_Dist_Normal;
    TgVEC_F32_04_1                      vResult_Dist;
    TgVEC_F32_04_1                      vResult_Dist_Normal;
    TgVEC_F32_04_1                      vNudge;
    TgVEC_F32_04_1                      vPos_W;

    tgSE_Init_Request( &sRequest );
    tgCO_REQ_Init_Intersect_F32_04( &sRequest.m_sCollision_Request, ETgPM_SG, ETgCO_PURPOSE__RAY_CAST );
    tgCO_REQ_Set_Include_Filter_F32_04( &sRequest.m_sCollision_Request, ETgCO_FILTER__STATIC_LOW | ETgCO_FILTER__RAG_DOLL );
    tgGM_SG_Init_F32_04( &sRequest.m_sCollision_Request.m_uPM.m_sSG, vPrev_Pos_W, psParticle->m_vPos_W );

    if (TgFAILED(tgSE_Collide( &sRequest, ETgSE_CHANNEL__SET )))
    {
        return;
    };

    psContact = &sRequest.m_sCollision_Request.m_psResult->m_sContact;

    vLVelW_Normal = tgMH_DOT_F32_04_1( psParticle->m_vLVel_W, psContact->m_vN0 );
    vBounce = tgMH_MUL_F32_04_1( psParticle->m_vCollision_Restitution, vLVelW_Normal );
    vLVel_W = tgMH_NMS_F32_04_1( psContact->m_vN0, vBounce, psParticle->m_vLVel_W );

    vPos_Dist = tgMH_SUB_F32_04_1( psParticle->m_vPos_W, vPrev_Pos_W );
    uPos_Dist_Normal.m_vF32_04_1 = tgMH_DOT_F32_04_1( vPos_Dist, psContact->m_vN0 );
    vResult_Dist = tgMH_SUB_F32_04_1( psContact->m_vS0, vPrev_Pos_W );
    vResult_Dist_Normal = tgMH_DOT_F32_04_1( vResult_Dist, psContact->m_vN0 );
    vNudge = tgMH_MUL_F32_04_1( psContact->m_vN0, tgMH_SET1_F32_04_1( sRequest.m_sCollision_Request.m_fNudge ) );

    psParticle->m_vLVel_W = vLVel_W;

    if (uPos_Dist_Normal.m_vS_F32_04_1.x > KTgEPS_F32)
    {
        TgVEC_F32_04_1                    vDist_Ratio;
        TgVEC_F32_04_1                    vTravel;

        vDist_Ratio = tgMH_DIV_F32_04_1( vResult_Dist_Normal, uPos_Dist_Normal.m_vF32_04_1 );
        vTravel = tgMH_SUB_F32_04_1( tgMH_SET1_F32_04_1( 1.0F ), vDist_Ratio );
        vPos_W = tgMH_MAD_F32_04_1( vLVel_W, vTravel, psContact->m_vS0 );
    }
    else
    {
        vPos_W = psContact->m_vS0;
    };

    psParticle->m_vPos_W = tgMH_ADD_F32_04_1( vPos_W, vNudge );

    tgFX_Effect__Emitter__Update__Update_Particle__Update_N( psEmitter, psParticle );

    if (KTgEMPTY_HASH != psEmitter->m_sExtend.m_psFile_Data__Particle->m_uiCollision_New_Effect_Hash)
    {
        STg2_FX_Instance                    sInstance;

        tgMM_Set_U08_0x00( &sInstance, sizeof( sInstance ) );
        sInstance.m_vPos_N2W = psParticle->m_vPos_W;
        sInstance.m_vNormal = psContact->m_vN0;
        sInstance.m_vScale = psEmitter->m_vScale;
        sInstance.m_qRot_N2W = psParticle->m_qRot_N2W;
        sInstance.m_tiParent = psEmitter->m_tiClient;
        tgFX__Update__Command__Emitter_Create( psEmitter->m_sExtend.m_psFile_Data__Particle->m_uiCollision_New_Effect_Hash, &sInstance );
    };
}
