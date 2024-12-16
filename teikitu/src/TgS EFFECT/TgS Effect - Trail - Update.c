/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Trail - Update.c
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

static TgVOID                               tgFX__Update__Trail_Add_Point( TgRSIZE_C , TgVEC_F32_04_1 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__File__Trail_Patch_File_Data ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__File__Trail_Patch_File_Data( STg2_FX_Trail__File_Data_P psData )
{
    TgUINT_PTR                          uiData_Top;

    uiData_Top = (TgUINT_PTR)psData;

    psData->m_sAnim.m_sData_Offset.m_uiColour += uiData_Top;
    psData->m_sAnim.m_sData_Offset.m_uiWidth += uiData_Top;
}


/* ---- tgFX__Update__Trail_Create_Command --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX__Update__Trail_Create_Command( STg2_FX_Instance_CP psInst, TgFX_DATA_INST_ID_C tiData, TgVOID_CP UNUSED_PARAM pData1 )
{
    STg2_FX__Trail_P                    psFX;

    psFX = g_asFX__Trail + tiData.m_uiI;

#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    {
        TgRN_MATERIAL_ID                    tiMaterial;
        ETgKN_GPU_DEFAULT_INPUT_LAYOUT      enVertex;

        tiMaterial = KTgRN_MATERIAL_ID__INVALID;
        enVertex = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_MAX;

        tgFX__Update__Set_Render_Data_From_Material_Hash( nullptr, &tiMaterial, &enVertex, psFX->m_psFile_Data->m_uiHash_Material );

        if (KTgID__INVALID_VALUE == tiMaterial.m_uiKI)
        {
            return (false);
        }

        psFX->m_tiMesh_Set = KTgRN_MESH_SET_ID__PARTICLE;
        tgRN_Calc_UV_Animation_F32_04_1( &psFX->m_sExtend.m_vUV_01_Constant, &psFX->m_sExtend.m_vUV_01_Scale, tiMaterial, KTgZERO_V128.m_vF32_04_1, KTgZERO_V128.m_vF32_04_1 );
    }
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif

    psFX->m_sExtend.m_vPos_N2W[0] = psInst->m_vPos_N2W;
    psFX->m_sExtend.m_vScaleFactor = tgMH_SPX_F32_04_1( psInst->m_vScale );
    psFX->m_sExtend.m_fU[0] = 0.0F;
    psFX->m_sExtend.m_uiPoint_Head = 0;
    psFX->m_sExtend.m_uiPoint_Tail = 0;
    psFX->m_sExtend.m_uiHead_Offset = 0;
    psFX->m_vLive_Time = tgMH_SET1_F32_04_1( 0.0F );
    tgFX_Evaluate_AnimData_F32_04_1( &psFX->m_sExtend.m_vColour, psFX->m_psFile_Data->m_sAnim.m_sParameter.m_psColour, tgMH_SET1_F32_04_1( 0.0F ) );
    tgFX_Evaluate_AnimData_F32_04_1( &psFX->m_sExtend.m_vWidth, psFX->m_psFile_Data->m_sAnim.m_sParameter.m_psWidth, tgMH_SET1_F32_04_1( 0.0F ) );
    psFX->m_fLife_Time = psFX->m_sTime.m_fTime_Total;

    if (psFX->m_sTime.m_fTime_End__Start < 0.0F)
        g_aenFX__Trail__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_INFINITE;
    else
        g_aenFX__Trail__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_FIRST;

    return (true);
}


/* ---- tgFX__Update__Trail_Update ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Trail_Update( TgVEC_F32_04_1 vdT, TgFLOAT32_C fDT, ETgFX_UPDATE_C enUpdate )
{
    TgFX_DATA_INST_ID                   tiActive;
    STg2_FX__Trail_P                    psTrail;
    STg2_FX_Trail__File_Data_CP         psFile_Data;

    tiActive = g_atiFX__Trail__Update__Head[enUpdate];

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        TgVEC_F32_04_1                      vRolling_Sum_Of_Pos_W_Delta;
        TgUN_V128                           uTrail_Length;
        TgVEC_F32_04_1                      vRolling_Sum_Of_Length[KTgFX_MAX_POINTS_IN_TRAIL];
        TgVEC_F32_04_1                      vFollow_Fraction;
        TgUINT_F32                          uiIndex;
        TgUINT_F32                          uiRead_Index;
        TgUINT_F32                          uiWrite_Index;
        TgFLOAT32                           fInv_Max_Trail_Length;

        tgFX__Update__Trail_Diag_Check_Effect( tiActive );

        psTrail = g_asFX__Trail + tiActive.m_uiI;
        psFile_Data = psTrail->m_psFile_Data;

        if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE_WAITING_TO_DIE == g_aenFX__Trail__Shared__State[tiActive.m_uiI])
        {
            if (psTrail->m_sExtend.m_uiPoint_Tail == psTrail->m_sExtend.m_uiPoint_Head)
            {
                tgFX__Update__Command__Trail_Kill_Self( psTrail->m_tiData );
                continue;
            }
            else
            {
                psTrail->m_sExtend.m_uiHead_Offset += 1;
                psTrail->m_sExtend.m_uiPoint_Tail = (psTrail->m_sExtend.m_uiPoint_Tail + 1) % KTgFX_MAX_POINTS_IN_TRAIL;
            };
        }
        else if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE == g_aenFX__Trail__Shared__State[tiActive.m_uiI])
        {
            if (psTrail->m_fLife_Time < fDT)
            {
                g_aenFX__Trail__Shared__State[tiActive.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_WAITING_TO_DIE;
            };
        }
        else if (ETgFX_EFFECT_STATE__UPDATE__ACTIVE_FIRST == g_aenFX__Trail__Shared__State[tiActive.m_uiI])
        {
            g_aenFX__Trail__Shared__State[tiActive.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE;
        };

        psTrail->m_vLive_Time = tgMH_ADD_F32_04_1( psTrail->m_vLive_Time, vdT );
        tgFX_Evaluate_AnimData_F32_04_1( &psTrail->m_sExtend.m_vColour, psFile_Data->m_sAnim.m_sParameter.m_psColour, psTrail->m_vLive_Time );
        tgFX_Evaluate_AnimData_F32_04_1( &psTrail->m_sExtend.m_vWidth, psFile_Data->m_sAnim.m_sParameter.m_psWidth, psTrail->m_vLive_Time );
        psTrail->m_fLife_Time -= fDT;

        if (psTrail->m_sExtend.m_uiPoint_Tail == psTrail->m_sExtend.m_uiPoint_Head)
            continue;

        /* Update Trail Points - Collapse any near positions and shrink the trail tail */
        vRolling_Sum_Of_Pos_W_Delta = tgMH_SET1_F32_04_1( 0.0F );
        uTrail_Length.m_vF32_04_1 = tgMH_SET1_F32_04_1( 0.0F );
        vFollow_Fraction = tgMH_SET1_F32_04_1( psFile_Data->m_fFollow_Fraction );
        TgERROR_INDEX( psTrail->m_sExtend.m_uiPoint_Head, vRolling_Sum_Of_Length );
        vRolling_Sum_Of_Length[psTrail->m_sExtend.m_uiPoint_Head] = tgMH_SET1_F32_04_1( 0.0F );

        uiRead_Index = psTrail->m_sExtend.m_uiPoint_Head;
        uiIndex = psTrail->m_sExtend.m_uiPoint_Head;
        uiWrite_Index = ((KTgFX_MAX_POINTS_IN_TRAIL + uiIndex - 1) % KTgFX_MAX_POINTS_IN_TRAIL);
        while (1)
        {
            TgUN_V128                           uDelta_Length;
            TgVEC_F32_04_1                      vNext_Pos_W;
            TgVEC_F32_04_1                      vDelta;
            TgVEC_F32_04_1                      vNew_Delta_Length;
            TgVEC_F32_04_1                      vNew_Delta;

            uiRead_Index = ((KTgFX_MAX_POINTS_IN_TRAIL + uiRead_Index - 1) % KTgFX_MAX_POINTS_IN_TRAIL);
            if (uiRead_Index == psTrail->m_sExtend.m_uiPoint_Tail)
            {
                break;
            }

            vNext_Pos_W = tgMH_ADD_F32_04_1( psTrail->m_sExtend.m_vPos_N2W[uiRead_Index], vRolling_Sum_Of_Pos_W_Delta );
            vDelta = tgMH_SUB_F32_04_1( vNext_Pos_W, psTrail->m_sExtend.m_vPos_N2W[uiIndex] );

            if (uDelta_Length.m_vF32_04_1.m_aData[0] < 0.001F)
            {
                continue;
            }

            vNew_Delta_Length = tgMH_MUL_F32_04_1( uDelta_Length.m_vF32_04_1, vFollow_Fraction );
            vNew_Delta = tgMH_MUL_F32_04_1( vDelta, vNew_Delta_Length );
            psTrail->m_sExtend.m_vPos_N2W[uiWrite_Index] = tgMH_ADD_F32_04_1( psTrail->m_sExtend.m_vPos_N2W[uiIndex], vNew_Delta );
            uTrail_Length.m_vF32_04_1 = tgMH_ADD_F32_04_1( uTrail_Length.m_vF32_04_1, vNew_Delta_Length );
            vRolling_Sum_Of_Length[uiWrite_Index] = uTrail_Length.m_vF32_04_1;
            vRolling_Sum_Of_Pos_W_Delta = tgMH_ADD_F32_04_1( vRolling_Sum_Of_Pos_W_Delta, tgMH_SUB_F32_04_1( vNew_Delta, vDelta ) );

            uiIndex = uiWrite_Index;
            uiWrite_Index = ((KTgFX_MAX_POINTS_IN_TRAIL + uiWrite_Index - 1) % KTgFX_MAX_POINTS_IN_TRAIL);
        }

        if (uiWrite_Index != ((KTgFX_MAX_POINTS_IN_TRAIL + psTrail->m_sExtend.m_uiPoint_Head - 1) % KTgFX_MAX_POINTS_IN_TRAIL))
        {
            psTrail->m_sExtend.m_uiPoint_Tail = uiWrite_Index;
        }

        /* Calculate the texel values */
        fInv_Max_Trail_Length = uTrail_Length.m_vF32_04_1.m_aData[0] > FLT_EPSILON ? 1.0F / uTrail_Length.m_vF32_04_1.m_aData[0] : 0.0F;
        for (uiIndex = psTrail->m_sExtend.m_uiPoint_Head; uiIndex != psTrail->m_sExtend.m_uiPoint_Tail;)
        {
            psTrail->m_sExtend.m_fU[uiIndex] = vRolling_Sum_Of_Length[uiIndex].m_aData[0] * fInv_Max_Trail_Length;
            uiIndex = ((KTgFX_MAX_POINTS_IN_TRAIL + uiIndex - 1) % KTgFX_MAX_POINTS_IN_TRAIL);
        }

        tiActive = psTrail->m_tiNext[ETgFX_NEXT__UPDATE];
    };
}


/* ---- tgFX__Update__Trail_Process_Update_Command ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Trail_Process_Update_Command( ETgFX_COMMAND_C enCommand, TgVOID_CP pData, TgFX_DATA_INST_ID_C tiData )
{
    TgPARAM_CHECK_INDEX( tiData.m_uiI, g_aenFX__Trail__Shared__State );

    switch (enCommand)
    {
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__NOTIFY: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__CREATE: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__SPIN: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__SCENE_TO_RENDER__BEGIN: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__UPDATE_TO_CLIENT__BEGIN: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__UPDATE_TO_CLIENT__NOTIFY: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__UPDATE_TO_CLIENT__FREE: /**< Fall Through - Invalid */
        case ETgFX_COMMAND__MAX: /**< Fall Through - Invalid */
        default: TgS_NO_DEFAULT( break );

        case ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL: /* Fall Through - Intentionally Blank */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__STOP: /* Fall Through - Intentionally Blank */
            break;

        case ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_SET: /* Fall Through - Treated as the same command */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_UPDATE_FROM_PARENT:
            TgERROR( g_aenFX__Trail__Shared__State[tiData.m_uiI] >= ETgFX_EFFECT_STATE__UPDATE__ACTIVE );
            tgFX__Update__Trail_Add_Point( tiData.m_uiI, tgMH_SETU_F32_04_1( (TgFLOAT32_CP)pData ) );
            break;
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_SET: /* Fall Through - Rotation is not conceptually valid */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_UPDATE_FROM_PARENT: /* Fall Through - Rotation is not conceptually valid */
        case ETgFX_COMMAND__CLIENT_TO_UPDATE__VISIBLE: /* Fall Through - Intentionally Blank */
            break;
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Update__Trail_Add_Point -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__Trail_Add_Point( TgRSIZE_C uiIndex, TgVEC_F32_04_1 vNewPoint )
{
    STg2_FX__Trail_P                    psTrail;
    STg2_FX_Trail__File_Data_CP         psFile_Data;
    TgUINT_F32                          nuiPoints;

    if (g_aenFX__Trail__Shared__State[uiIndex] < ETgFX_EFFECT_STATE__UPDATE__ACTIVE)
    {
        TgDIAG( ETgFX_EFFECT_STATE__UPDATE__ACTIVE_WAITING_TO_DIE == g_aenFX__Trail__Shared__State[uiIndex] );
        return;
    }

    psTrail = g_asFX__Trail + uiIndex;
    psFile_Data = psTrail->m_psFile_Data;

    if (tgMH_PRX3_CMP_EQ_F32_04_1( psTrail->m_sExtend.m_vPos_N2W[psTrail->m_sExtend.m_uiPoint_Head], vNewPoint ))
    {
        return;
    }

    nuiPoints = (KTgFX_MAX_POINTS_IN_TRAIL + psTrail->m_sExtend.m_uiPoint_Head - psTrail->m_sExtend.m_uiPoint_Tail) % KTgFX_MAX_POINTS_IN_TRAIL;

    if (nuiPoints >= psFile_Data->m_nuiMax_Points)
    {
        psTrail->m_sExtend.m_uiPoint_Tail = (psTrail->m_sExtend.m_uiPoint_Tail + 1) % KTgFX_MAX_POINTS_IN_TRAIL;
    }

    psTrail->m_sExtend.m_uiPoint_Head = (psTrail->m_sExtend.m_uiPoint_Head + 1) % KTgFX_MAX_POINTS_IN_TRAIL;
    psTrail->m_sExtend.m_vPos_N2W[psTrail->m_sExtend.m_uiPoint_Head] = vNewPoint;
}
