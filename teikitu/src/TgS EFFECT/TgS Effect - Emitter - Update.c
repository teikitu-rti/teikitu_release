/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Emitter - Update.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Effect - Internal.inl"


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
static TgBOOL                               tgFX__Update__Emitter_Reserve_Particle_Buffer( STg2_FX__Emitter_P );
static TgVOID                               tgFX__Update__Emitter_Free_Particle_Buffer( STg2_FX__Emitter_P );
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__File__Emitter_Patch_File_Data -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__File__Emitter_Patch_File_Data( STg2_FX_Emitter__File_Data_P psData )
{
    TgUINT_PTR                          uiData_Top;

    uiData_Top = (TgUINT_PTR)psData;

    psData->m_sAnim.m_sData_Offset.m_uiEmitter_LVel_N += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiEmitter_Rot_N += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiEmission_Shape += uiData_Top;
}


/* ---- tgFX__Update__Emitter_Create_Command ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX__Update__Emitter_Create_Command( STg2_FX_Instance_CP UNUSED_PARAM psInst, TgFX_DATA_INST_ID_C tiData, TgVOID_CP pData1 )
{
    STg2_FX_Emitter__File_Data_CP       psFile_Data;
    STg2_FX__Emitter_P                  psFX;

    psFX = g_asFX__Emitter + tiData.m_uiI;
    psFile_Data = psFX->m_psFile_Data;

    if (nullptr == pData1)
    {
        return (false);
    };

    psFX->m_sExtend.m_fEmission_Interval = tgFX_Quality_Setting_Lerp__Range_F32( psFile_Data->m_afEmission_Interval_MID, psFile_Data->m_afEmission_Interval_RNG );
    psFX->m_sExtend.m_fEmission_Quantity = tgFX_Quality_Setting_Lerp__Range_F32( psFile_Data->m_afEmission_Quantity_MID, psFile_Data->m_afEmission_Quantity_RNG );
    psFX->m_sExtend.m_nuiParticle_Max = tgFX_Quality_Setting_Lerp__Value_UMAX( psFile_Data->m_anuiEmission_Max_Particle );
    psFX->m_sExtend.m_psFile_Data__Particle = (STg2_FX_Particle__File_Data_CP)pData1;
    tgFX_Evaluate_AnimData_F32_04_1( &psFX->m_sExtend.m_vLVel_N, psFile_Data->m_sAnim.m_sParameter.m_psEmitter_LVel_N, tgMH_SET1_F32_04_1( 0.0F ) );
    tgFX_Evaluate_AnimData_F32_04_1( &psFX->m_sExtend.m_vEmission_Shape, psFile_Data->m_sAnim.m_sParameter.m_psEmission_Shape, tgMH_SET1_F32_04_1( 0.0F ) );
    psFX->m_sExtend.m_nuiParticle = 0;
    psFX->m_sExtend.m_nuiParticle_Render = 0;
    psFX->m_uiRender__NotVisible = 1;

#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    {
        TgBOOL                              bEmitMesh = 0 != (psFile_Data->m_uiFlags & ETgFX_EMITTER_FLAGS__EMISSION__MESH_SET);

        psFX->m_sExtend.m_nuiParticle_Max = tgCM_MIN_UMAX( psFX->m_sExtend.m_nuiParticle_Max, KTgRN_MAX_PRTCL_BUFFER_SIZE / 6 / sizeof(STg2_KN_GPU_Vertex_Particle_00) );

        tgFX__Update__Set_Render_Data_From_Material_Hash( bEmitMesh ? &psFX->m_tiMesh_Set : nullptr, &psFX->m_tiMaterial, &psFX->m_enVertex, psFile_Data->m_uiHash_Material );

        if (KTgID__INVALID_VALUE == psFX->m_tiMaterial.m_uiKI)
        {
            return (false);
        };

        if (!tgFX__Update__Emitter_Reserve_Particle_Buffer( psFX ))
        {
            return (false);
        };
    }
#else

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif

    if (psFX->m_sTime.m_fTime_End__Start < 0.0F)
        g_aenFX__Emitter__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_INFINITE;
    else
        g_aenFX__Emitter__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_FIRST;

    return (true);
}


/* ---- tgFX__Update__Emitter_Update --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Emitter_Update( TgVEC_F32_04_1 vdT, TgFLOAT32_C fDT, ETgFX_UPDATE_C enUpdate )
{
    TgFX_DATA_INST_ID                   tiActive;
    STg2_FX__Emitter_P                  psEmitter;
    STg2_FX_Emitter__File_Data_CP       psFile_Data;

    tiActive = g_atiFX__Emitter__Update__Head[enUpdate];

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        TgVEC_F32_04_1                    vPos_Delta_N;

        tgFX__Update__Emitter_Diag_Check_Effect( tiActive );

        psEmitter = g_asFX__Emitter + tiActive.m_uiI;
        psFile_Data = psEmitter->m_psFile_Data;

        /* Life Time Update */
        TgDIAG( ETgFX_EFFECT_STATE__UPDATE__ACTIVE_WAITING_TO_DIE >= g_aenFX__Emitter__Shared__State[tiActive.m_uiI] );
        TgDIAG( ETgFX_EFFECT_STATE__UPDATE__ACTIVE <= g_aenFX__Emitter__Shared__State[tiActive.m_uiI] );
        if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE == g_aenFX__Emitter__Shared__State[tiActive.m_uiI])
        {
            if (psEmitter->m_fLife_Time <= fDT)
            {
                psEmitter->m_fLife_Time = 0.0F;
                g_aenFX__Emitter__Shared__State[tiActive.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_WAITING_TO_DIE;
            }
            else
            {
                psEmitter->m_fLife_Time -= fDT;
            };
        }
        else if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE_INFINITE == g_aenFX__Emitter__Shared__State[tiActive.m_uiI])
        {
            /* Intentionally left blank */
        }
        else if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE_FIRST == g_aenFX__Emitter__Shared__State[tiActive.m_uiI])
        {
            g_aenFX__Emitter__Shared__State[tiActive.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE;
        }
        else if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE_WAITING_TO_DIE == g_aenFX__Emitter__Shared__State[tiActive.m_uiI])
        {
            /* Intentionally left blank */
        }
        else
        {
            tgFX__Update__Command__Emitter_Kill_Self( psEmitter->m_tiData );
            tiActive = g_asFX__Emitter[tiActive.m_uiI].m_tiNext[ETgFX_NEXT__UPDATE];
            TgERROR_MSGF( 0, u8"%-16.16s(%-32.32s): Invalid Effect State.\n", u8"Effect", u8"tgFX__Emitter__Update__Update" );
            continue;
        };

        if (TgFAILED(tgFX_Integrate_AnimData_F32_04_1( &vPos_Delta_N, psFile_Data->m_sAnim.m_sParameter.m_psEmitter_LVel_N, vdT, psEmitter->m_vLive_Time )))
            vPos_Delta_N = KTgZERO_F32_04_1;

        tgFX_Evaluate_AnimData_F32_04_1( &psEmitter->m_qRot_N2M, psFile_Data->m_sAnim.m_sParameter.m_psEmitter_Rot_N, psEmitter->m_vLive_Time );
        psEmitter->m_vPos_N2M = tgMH_ADD_F32_04_1( psEmitter->m_vPos_N2M, vPos_Delta_N );
        psEmitter->m_qRot_N2W = tgMH_QT_MUL_F32_04_1( psEmitter->m_qRot_N2M, psEmitter->m_qRot_M2W );
        psEmitter->m_vPos_N2W = tgMH_ADD_F32_04_1( psEmitter->m_vPos_M2W, tgMH_QT_TX_F32_04_1( psEmitter->m_vPos_N2M, psEmitter->m_qRot_M2W ) );
        psEmitter->m_vPos_N2W = tgMH_MAD_F32_04_1( tgMH_SET1_F32_04_1( 0.5F*fDT*fDT ), psFile_Data->m_vL_Vel_Acceleration_W, psEmitter->m_vPos_N2W );
        psEmitter->m_vLive_Time = tgMH_ADD_F32_04_1( psEmitter->m_vLive_Time, vdT );
        psEmitter->m_sTime.m_fLive_Time += fDT;
        tgFX_Evaluate_AnimData_F32_04_1( &psEmitter->m_sExtend.m_vEmission_Shape, psFile_Data->m_sAnim.m_sParameter.m_psEmission_Shape, psEmitter->m_vLive_Time );


        /* Particle Update */
        if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE_WAITING_TO_DIE == g_aenFX__Emitter__Shared__State[tiActive.m_uiI])
        {
            tgFX__Update__Emitter_Update_Particle( psEmitter, fDT, vdT );

            if (0 >= psEmitter->m_sExtend.m_nuiParticle)
            {
                tgFX__Update__Command__Emitter_Kill_Self( psEmitter->m_tiData );
            };
        }
        else
        {
            if (psEmitter->m_sExtend.m_fEmission_Interval <= fDT)
            {
                TgRSIZE_C                           nuiParticle_Max = psEmitter->m_sExtend.m_nuiParticle_Max - psEmitter->m_sExtend.m_nuiParticle;
                TgFLOAT32                           fEmission_Quantity;

                fEmission_Quantity = tgPM_FLOOR_F32( psEmitter->m_sExtend.m_fEmission_Quantity );
                psEmitter->m_sExtend.m_fEmission_Interval = tgFX_Quality_Setting_Lerp__Range_F32( psFile_Data->m_afEmission_Interval_MID, psFile_Data->m_afEmission_Interval_RNG );
                psEmitter->m_sExtend.m_fEmission_Quantity -= fEmission_Quantity;
                psEmitter->m_sExtend.m_fEmission_Quantity += tgFX_Quality_Setting_Lerp__Range_F32( psFile_Data->m_afEmission_Quantity_MID, psFile_Data->m_afEmission_Quantity_RNG );
                psEmitter->m_sExtend.m_fEmission_Quantity = tgCM_MIN_F32( psEmitter->m_sExtend.m_fEmission_Quantity, (TgFLOAT32)nuiParticle_Max );
                fEmission_Quantity = tgCM_MIN_F32( fEmission_Quantity, (TgFLOAT32)nuiParticle_Max );

                if (0.0f < fEmission_Quantity)
                {
                    tgFX__Update__Emitter_Add_Particle( psEmitter, (TgRSIZE)fEmission_Quantity );
                };
            }
            else
            {
                psEmitter->m_sExtend.m_fEmission_Interval -= fDT;
            };

            tgFX__Update__Emitter_Update_Particle( psEmitter, fDT, vdT );
        };

        psEmitter->m_uiRender__NotVisible = psEmitter->m_sExtend.m_nuiParticle ? 0 : 1u;
        tiActive = psEmitter->m_tiNext[ETgFX_NEXT__UPDATE];
    };
}


/* ---- tgFX__Update__Emitter_Process_Update_Command ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Emitter_Process_Update_Command( ETgFX_COMMAND_C enCommand, TgVOID_CP pData, TgFX_DATA_INST_ID_C tiData )
{
    tgFX__Update__Emitter_Process_Update_Command_Default( enCommand, pData, tiData );

#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    if (ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL == enCommand)
    {
        tgFX__Update__Emitter_Free_Particle_Buffer( g_asFX__Emitter + tiData.m_uiI );
    };
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Update__Emitter_Reserve_Particle_Buffer ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
static TgBOOL tgFX__Update__Emitter_Reserve_Particle_Buffer( STg2_FX__Emitter_P psEmitter )
{
    TgRSIZE_C                           uiPage_Size = tgMM_Page_Size();

    TgRSIZE                             uiMemory_Current;
    TgRSIZE                             uiMemory_New;
    TgRSIZE                             nuiMin_Particle;
    TgRSIZE                             uiMax_Commit;
    TgRSIZE                             uiMin_Commit;
    TgUINT_F32                          uiIndex;

    psEmitter->m_sExtend.m_nuiParticle_Commit = 0;
    psEmitter->m_sExtend.m_psParticle_Active = nullptr;
    psEmitter->m_sExtend.m_psParticle_Free = nullptr;
    psEmitter->m_sExtend.m_psParticle_Memory = nullptr;

    /* Determine if the emitter max allocation fits into max memory limit for the module / system */
    nuiMin_Particle = tgCM_MAX_UMAX( 1, tgCM_MIN_UMAX( (TgUINT_MAX)psEmitter->m_sExtend.m_fEmission_Quantity, psEmitter->m_sExtend.m_nuiParticle_Max ) );
    uiMax_Commit = 1 + (psEmitter->m_sExtend.m_nuiParticle_Max * sizeof( STg2_FX__Emitter__Particle ) / uiPage_Size);
    uiMin_Commit = 1 + (nuiMin_Particle * sizeof( STg2_FX__Emitter__Particle ) / uiPage_Size);
    TgERROR( uiMin_Commit <= uiMax_Commit );
    uiMemory_Current = atomic_load( &g_xuiFX__Emitter__Memory_Current );
    do
    {
        uiMemory_New = uiMemory_Current + uiMax_Commit * uiPage_Size;
        if (uiMemory_New > g_uiFX_Emitter_Memory_Max)
        {
            return (false);
        };
    }
    while (!atomic_compare_exchange_weak( &g_xuiFX__Emitter__Memory_Current, &uiMemory_Current, uiMemory_New ));

    /* Reserve enough memory for max number of particles */
    psEmitter->m_sExtend.m_psParticle_Memory = (STg2_FX__Emitter__Particle_P)TgRESERVE_VIRTUAL( uiMax_Commit * uiPage_Size );
    if (nullptr == psEmitter->m_sExtend.m_psParticle_Memory)
    {
        uiMemory_Current = atomic_load( &g_xuiFX__Emitter__Memory_Current );
        do
        {
            uiMemory_New = uiMemory_Current - uiMax_Commit * uiPage_Size;
        }
        while (!atomic_compare_exchange_weak( &g_xuiFX__Emitter__Memory_Current, &uiMemory_Current, uiMemory_New ));
        return (false);
    };

    /* Commit enough memory for one memory page, or one particle */
    if (nullptr == TgCOMMIT_VIRTUAL( psEmitter->m_sExtend.m_psParticle_Memory, uiMin_Commit ))
    {
        uiMemory_Current = atomic_load( &g_xuiFX__Emitter__Memory_Current );
        do
        {
            uiMemory_New = uiMemory_Current - uiMax_Commit * uiPage_Size;
        }
        while (!atomic_compare_exchange_weak( &g_xuiFX__Emitter__Memory_Current, &uiMemory_Current, uiMemory_New ));
        return (false);
    };

    /* Initialize the linked list of free particles and record the number of particles on committed memory pages */
    psEmitter->m_sExtend.m_nuiParticle_Commit = uiMin_Commit * uiPage_Size / sizeof( STg2_FX__Emitter__Particle );
    for (uiIndex = 0; uiIndex + 1 < psEmitter->m_sExtend.m_nuiParticle_Commit; ++uiIndex)
    {
        psEmitter->m_sExtend.m_psParticle_Memory[uiIndex].m_psNext = psEmitter->m_sExtend.m_psParticle_Memory + uiIndex + 1;
    };
    psEmitter->m_sExtend.m_psParticle_Memory[uiIndex].m_psNext = nullptr;
    psEmitter->m_sExtend.m_psParticle_Free = psEmitter->m_sExtend.m_psParticle_Memory;
    psEmitter->m_sExtend.m_psParticle_Active = nullptr;

    return (true);
}
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif


/* ---- tgFX__Update__Emitter_Free_Particle_Buffer ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
static TgVOID tgFX__Update__Emitter_Free_Particle_Buffer( STg2_FX__Emitter_P psEmitter )
{
    TgRSIZE                             uiMemory_Current;
    TgRSIZE                             uiMemory_New;
    TgRSIZE                             uiMax_Commit;

    uiMax_Commit = 1 + ((TgRSIZE)psEmitter->m_sExtend.m_nuiParticle_Max * sizeof( STg2_FX__Emitter__Particle ) / tgMM_Page_Size());

    if (nullptr != psEmitter->m_sExtend.m_psParticle_Memory)
    {
        uiMemory_Current = atomic_load( &g_xuiFX__Emitter__Memory_Current );
        do
        {
            uiMemory_New = uiMemory_Current - uiMax_Commit * tgMM_Page_Size();
        }
        while (!atomic_compare_exchange_weak( &g_xuiFX__Emitter__Memory_Current, &uiMemory_Current, uiMemory_New ));
    };

    TgFREE_VIRTUAL( psEmitter->m_sExtend.m_psParticle_Memory );

    psEmitter->m_sExtend.m_nuiParticle_Commit = 0;
    psEmitter->m_sExtend.m_psParticle_Active = nullptr;
    psEmitter->m_sExtend.m_psParticle_Free = nullptr;
    psEmitter->m_sExtend.m_psParticle_Memory = nullptr;
}
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
