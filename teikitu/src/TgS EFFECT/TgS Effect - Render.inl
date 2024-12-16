/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Render.inl
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_EFFECT_INTERNAL_INL)
#define TGS_EFFECT_INTERNAL_INL

/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Calc_Quad ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgFX_Calc_Quad( TgVEC_F32_04_1_P pvPos_W, TgVEC_F32_04_1_P pvBasis, TgFLOAT32_C fSpin, STg2_FX_Calc_Quad_CP psCalcData )
{
    TgFLOAT32                           fCos;
    TgFLOAT32                           fSin;

    tgPM_SINCOS_F32( &fCos, &fSin, fSpin );

    {
        TgVEC_F32_04_1_C                  vCos = tgMH_SET1_F32_04_1( fCos );
        TgVEC_F32_04_1_C                  vSin = tgMH_SET1_F32_04_1( fSin );
        TgVEC_F32_04_1_C                  vAxis_Right = tgMH_MAD_F32_04_1( vSin, psCalcData->m_vDir_Up, tgMH_MUL_F32_04_1( vCos, psCalcData->m_vDir_Right ) );
        TgVEC_F32_04_1_C                  vQuad_Right = tgMH_MUL_F32_04_1( psCalcData->m_vSize_X, vAxis_Right );
        TgVEC_F32_04_1_C                  vAxis_Up = tgMH_NMS_F32_04_1( vSin, psCalcData->m_vDir_Right, tgMH_MUL_F32_04_1( vCos, psCalcData->m_vDir_Up ) );
        TgVEC_F32_04_1_C                  vQuad_Up = tgMH_MUL_F32_04_1( psCalcData->m_vSize_Y, vAxis_Up );
        TgVEC_F32_04_1_C                  vOne = tgMH_SET1_F32_04_1( 1.0F );
        TgVEC_F32_04_1_C                  vX0 = tgMH_MUL_F32_04_1( vQuad_Right, tgMH_ADD_F32_04_1( vOne, psCalcData->m_vPivot_X ) );
        TgVEC_F32_04_1_C                  vX1 = tgMH_MUL_F32_04_1( vQuad_Right, tgMH_SUB_F32_04_1( vOne, psCalcData->m_vPivot_X ) );
        TgVEC_F32_04_1_C                  vY0 = tgMH_MUL_F32_04_1( vQuad_Up, tgMH_SUB_F32_04_1( vOne, psCalcData->m_vPivot_Y ) );
        TgVEC_F32_04_1_C                  vY1 = tgMH_MUL_F32_04_1( vQuad_Up, tgMH_ADD_F32_04_1( vOne, psCalcData->m_vPivot_Y ) );

        pvBasis[0] = tgMH_NORM_F32_04_1( vAxis_Right );
        pvBasis[1] = tgMH_NORM_F32_04_1( vAxis_Up );

        pvPos_W[0] = tgMH_ADD_F32_04_1( psCalcData->m_vPos_W, tgMH_SUB_F32_04_1( vY0, vX0 ) );
        pvPos_W[1] = tgMH_SUB_F32_04_1( psCalcData->m_vPos_W, tgMH_ADD_F32_04_1( vX0, vY1 ) );
        pvPos_W[2] = tgMH_ADD_F32_04_1( psCalcData->m_vPos_W, tgMH_SUB_F32_04_1( vX1, vY1 ) );
        pvPos_W[3] = tgMH_ADD_F32_04_1( psCalcData->m_vPos_W, tgMH_ADD_F32_04_1( vX1, vY0 ) );
    };
}

/* =============================================================================================================================================================================== */
#endif
