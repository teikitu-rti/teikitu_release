/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Emitter - Scene.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Effect ===================================================================================================================================================================== */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Parent File Local Functions                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Emitter__Update_BA -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX_Emitter__Update_BA( TgFX_DATA_INST_ID tiData )
{
    STg2_FX__Emitter_P                  psEmitter;
    STg2_FX__Emitter__Particle_P        psParticle;
    TgVEC_F32_04_1                    vBA_Radius;

    psEmitter = g_asFX__Emitter + tiData.m_uiI;

    if (psEmitter->m_sExtend.m_psFile_Data__Particle->m_enOrientation == ETgFX_PARTICLE_ORIENTATION__SCREEN_SPACE)
    {
        return;
    };

    /* Effect will not render, generate an approximate bounding box for client thread */
    psEmitter->m_vBA_Max_W = tgMH_SET1_F32_04_1( -FLT_MAX );
    psEmitter->m_vBA_Min_W = tgMH_SET1_F32_04_1( FLT_MAX );
    psParticle = psEmitter->m_sExtend.m_psParticle_Active;
    while (psParticle)
    {
        vBA_Radius = tgMH_MAX_F32_04_1( psParticle->m_vSize_X, psParticle->m_vSize_Y );
        psEmitter->m_vBA_Max_W = tgMH_MAX_F32_04_1( psEmitter->m_vBA_Max_W, tgMH_ADD_F32_04_1( psParticle->m_vPos_W, vBA_Radius ) );
        psEmitter->m_vBA_Min_W = tgMH_MIN_F32_04_1( psEmitter->m_vBA_Min_W, tgMH_SUB_F32_04_1( psParticle->m_vPos_W, vBA_Radius ) );
        psParticle = psParticle->m_psNext;
    };
}


/* ---- tgFX__Scene__Emitter_Cull__Insert_Frame_Mesh ----------------------------------------------------------------------------------------------------------------------------- */
/* Mesh emission requires adding a mesh for every "particle" into the scene context                                                                                                */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Scene__Emitter_Cull__Insert_Frame_Mesh( STg2_SE_Context_PC psSE_Context, TgRSIZE_C uiView_Index, TgFX_DATA_INST_ID tiActive )
{
    STg2_FX__Emitter_P                  psEmitter;
    TgUINT_E32                          uiEmitter_Frame_Mesh_Set__LOD_Index;
    TgVEC_F32_04_1                      vEmitter_Frame_Mesh_Set__Scale;
    TgVEC_F32_04_1                      vEmitter_Frame_Mesh_Set__Ambient;
    TgRSIZE_P                           auiEmitter_Frame_Mesh_Set__Light_List;
    TgRSIZE                             nuiEmitter_Frame_Mesh_Set__Light;
    TgUINT_E32                          uiEmitter_Frame_Mesh__Flag;
    STg2_FX__Emitter__Particle_P        psParticle;
    TgRSIZE                             uiIndex_In_SE_Context;
    TgRSIZE                             uiMax_Index_In_SE_Context;
    TgRSIZE                             uiView_Inst_Index;
    TgRSIZE                             uiView_Inst_Max_Index;
    TgRSIZE_P                           puiFrame_Mesh_Inst;

    psEmitter = g_asFX__Emitter + tiActive.m_uiI;

    uiIndex_In_SE_Context = TgSTD_ATOMIC(fetch_add)( &psSE_Context->m_xnuiFrame_Mesh, psEmitter->m_sExtend.m_nuiParticle );
    if (uiIndex_In_SE_Context + psEmitter->m_sExtend.m_nuiParticle >= psSE_Context->m_nuiFrame_Mesh_Max)
    {
        TgSTD_ATOMIC(fetch_sub)( &psSE_Context->m_xnuiFrame_Mesh, psEmitter->m_sExtend.m_nuiParticle );
        return;
    }

    uiMax_Index_In_SE_Context = uiIndex_In_SE_Context + psEmitter->m_sExtend.m_nuiParticle;

    if (tgRN_Material__Is_Opaque( psEmitter->m_tiMaterial ))
    {
        uiView_Inst_Index = TgSTD_ATOMIC(fetch_add)( psSE_Context->m_asView[uiView_Index].m_axnuiFrame_Mesh_Inst + ETgSE_DRAW_TYPE__OPAQUE, 1 );
        uiView_Inst_Max_Index = psSE_Context->m_asView[uiView_Index].m_anuiFrame_Mesh_Inst_Max[ETgSE_DRAW_TYPE__OPAQUE];
        puiFrame_Mesh_Inst = psSE_Context->m_asView[uiView_Index].m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__OPAQUE];
    }
    else
    {
        uiView_Inst_Index = TgSTD_ATOMIC(fetch_add)( psSE_Context->m_asView[uiView_Index].m_axnuiFrame_Mesh_Inst + ETgSE_DRAW_TYPE__TRANSPARENT, 1 );
        uiView_Inst_Max_Index = psSE_Context->m_asView[uiView_Index].m_anuiFrame_Mesh_Inst_Max[ETgSE_DRAW_TYPE__TRANSPARENT];
        puiFrame_Mesh_Inst = psSE_Context->m_asView[uiView_Index].m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__TRANSPARENT];
    };

    uiEmitter_Frame_Mesh_Set__LOD_Index = psSE_Context->m_asFrame_Mesh[psEmitter->m_uiIndex_In_SE_Context].m_uiLOD_Index;
    vEmitter_Frame_Mesh_Set__Scale = psSE_Context->m_asFrame_Mesh[psEmitter->m_uiIndex_In_SE_Context].m_vScale;
    vEmitter_Frame_Mesh_Set__Ambient = psSE_Context->m_asFrame_Mesh[psEmitter->m_uiIndex_In_SE_Context].m_vAmbient;
    auiEmitter_Frame_Mesh_Set__Light_List = psSE_Context->m_asFrame_Mesh[psEmitter->m_uiIndex_In_SE_Context].m_auiLight;
    nuiEmitter_Frame_Mesh_Set__Light = psSE_Context->m_asFrame_Mesh[psEmitter->m_uiIndex_In_SE_Context].m_nuiLight;
    uiEmitter_Frame_Mesh__Flag = psSE_Context->m_asFrame_Mesh[psEmitter->m_uiIndex_In_SE_Context].m_uiFlags;

    psParticle = psEmitter->m_sExtend.m_psParticle_Active;

    while (uiIndex_In_SE_Context < uiMax_Index_In_SE_Context)
    {
        TgVEC_F32_04_1                    vPos_W;
        TgVEC_F32_04_1                    qRot_W;
        STg2_RN_Cxt_Mesh_P                  pRN_Cxt_Mesh;

        pRN_Cxt_Mesh = psSE_Context->m_asFrame_Mesh + uiIndex_In_SE_Context;
        pRN_Cxt_Mesh->m_tiMesh_Set = psEmitter->m_tiMesh_Set;
        pRN_Cxt_Mesh->m_uiLOD_Index = uiEmitter_Frame_Mesh_Set__LOD_Index;
        pRN_Cxt_Mesh->m_uiFlags = uiEmitter_Frame_Mesh__Flag;

        pRN_Cxt_Mesh->m_vScale = vEmitter_Frame_Mesh_Set__Scale;
        vPos_W = psParticle->m_vPos_W;
        qRot_W = psParticle->m_qRot_N2W;
        tgMH_Init_Quat_F32_04_3( &pRN_Cxt_Mesh->m_xTX, qRot_W );
        tgMH_Set_T_F32_04_3( &pRN_Cxt_Mesh->m_xTX, vPos_W );

        pRN_Cxt_Mesh->m_vLast_Scale = KTgONE_V128.m_vF32_04_1;
        pRN_Cxt_Mesh->m_xLast_TX.m_avCol[0] = KTgIDENT_F32_04_3.m_avCol[0];
        pRN_Cxt_Mesh->m_xLast_TX.m_avCol[1] = KTgIDENT_F32_04_3.m_avCol[1];
        pRN_Cxt_Mesh->m_xLast_TX.m_avCol[2] = KTgIDENT_F32_04_3.m_avCol[2];

        pRN_Cxt_Mesh->m_vBA_Max_W = psEmitter->m_vBA_Max_W;
        pRN_Cxt_Mesh->m_vBA_Min_W = psEmitter->m_vBA_Min_W;

        pRN_Cxt_Mesh->m_vAmbient = vEmitter_Frame_Mesh_Set__Ambient;
        pRN_Cxt_Mesh->m_vLM = KTgZERO_V128.m_vF32_04_1;
        pRN_Cxt_Mesh->m_tiLM.m_uiKI = KTgID__INVALID_VALUE;
        pRN_Cxt_Mesh->m_tiMaterial = psEmitter->m_tiMaterial;
        tgMM_Copy( pRN_Cxt_Mesh->m_auiLight, sizeof( pRN_Cxt_Mesh->m_auiLight ), auiEmitter_Frame_Mesh_Set__Light_List, KTgRN_CXT_MAX_LIGHT_PER_INSTANCE * sizeof( TgUINT_E32  ) );
        pRN_Cxt_Mesh->m_nuiLight = nuiEmitter_Frame_Mesh_Set__Light;

        pRN_Cxt_Mesh->m_uiSkeleton_0 = KTgMAX_U32;
        pRN_Cxt_Mesh->m_uiSkeleton_1 = KTgMAX_U32;

        pRN_Cxt_Mesh->m_fOpacity = 1.0F;

        if (uiView_Inst_Index < uiView_Inst_Max_Index)
        {
            puiFrame_Mesh_Inst[uiView_Inst_Index] = uiIndex_In_SE_Context;
            ++uiView_Inst_Index;
        };

        ++uiIndex_In_SE_Context;

        psParticle = psParticle->m_psNext;
    };

    /* Invalidate the emitter in the SE Context */
    psSE_Context->m_asFrame_Mesh[psEmitter->m_uiIndex_In_SE_Context].m_tiMesh_Set = KTgRN_MESH_SET_ID__INVALID;
    psSE_Context->m_asFrame_Mesh[psEmitter->m_uiIndex_In_SE_Context].m_tiMaterial = KTgRN_MATERIAL_ID__INVALID;
}


/* == Effect ===================================================================================================================================================================== */

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
