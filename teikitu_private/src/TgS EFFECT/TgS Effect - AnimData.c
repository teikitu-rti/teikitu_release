/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - AnimData.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Integrate_AnimData_F32_04 ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgFX_Integrate_AnimData_F32_04_1( TgVEC_F32_04_1_P pvOUT, STg2_FX_AnimData_P psAnimData, TgVEC_F32_04_1_C vT, TgATTRIBUTE_UNUSED TgVEC_F32_04_1_C vDT )
{
    UTg2_FX_AnimData_C                  uAnimData = { .psAnimData = psAnimData };

    *pvOUT = KTgZERO_V128.m_vF32_04_1;

    if (ETgFX_ANIM_DATA__KEY_FRAME_F32_01 <= psAnimData->m_enType && psAnimData->m_enType <= ETgFX_ANIM_DATA__KEY_FRAME_F32_04)
    {
        TgUN_V128                           uT = { .m_vF32_04_1 = vT };

        TgUN_V128                           uRet;
        TgFLOAT32                           fT;
        TgRSIZE                             uiKey, uiKey_Next;
        TgFLOAT32                           fRange;
        TgFLOAT32                           fRelative_Position_In_Range;
        TgFLOAT32                           fFraction_Of_Range;
        TgFLOAT32                           fInt;
        TgVEC_F32_04_1                      vFraction_Of_Range;

        fT = uT.m_vS_F32_04_1.x;
        uRet.m_vF32_04_1 = KTgZERO_F32_04_1;

        if (uAnimData.psKey_Frame->m_nuiKey_Frame < 1)
            return (KTgE_FAIL);

        for (uiKey = 0; uiKey + 1u < uAnimData.psKey_Frame->m_nuiKey_Frame; ++uiKey)
        {
            uiKey_Next = tgCM_MIN_UMAX( uiKey + 1, uAnimData.psKey_Frame->m_nuiKey_Frame - 1 );
            fRange = uAnimData.psKey_Frame->m_pfTime[uiKey_Next] - uAnimData.psKey_Frame->m_pfTime[uiKey];
            if (tgCM_NR0_F32( fRange ))
                continue;
            fRelative_Position_In_Range = tgCM_CLP_F32( fT - uAnimData.psKey_Frame->m_pfTime[uiKey], 0.0F, fRange );
            fFraction_Of_Range = fRelative_Position_In_Range / fRange;
            vFraction_Of_Range = tgMH_SET1_F32_04_1( fFraction_Of_Range );
            TgVERIFY(fFraction_Of_Range >= 0.0F && fFraction_Of_Range <= 1.0F);
            fInt = 0.5F * fRelative_Position_In_Range;

            switch (psAnimData->m_enType) {
            case ETgFX_ANIM_DATA__KEY_FRAME_F32_01:
                TgVERIFY(sizeof(STg2_FX_AnimData__Key_Frame_F32_01) == psAnimData->m_uiSize);
                uRet.m_vS_F32_04_1.x = fInt * tgCM_LRP_F32( uAnimData.psKey_Frame_F32_01->m_pfVal[uiKey], uAnimData.psKey_Frame_F32_01->m_pfVal[uiKey_Next], fFraction_Of_Range );
                uRet.m_vS_F32_04_1.y = 0.0F;
                uRet.m_vS_F32_04_1.z = 0.0F;
                uRet.m_vS_F32_04_1.w = 0.0F;
                break;
            case ETgFX_ANIM_DATA__KEY_FRAME_F32_02:
                TgVERIFY(sizeof(STg2_FX_AnimData__Key_Frame_F32_02) == psAnimData->m_uiSize);
                uRet.m_vS_F32_04_1.x = fInt * tgCM_LRP_F32( uAnimData.psKey_Frame_F32_02->m_pfVal[uiKey*2+0], uAnimData.psKey_Frame_F32_02->m_pfVal[uiKey_Next*2+0], fFraction_Of_Range );
                uRet.m_vS_F32_04_1.y = fInt * tgCM_LRP_F32( uAnimData.psKey_Frame_F32_02->m_pfVal[uiKey*2+1], uAnimData.psKey_Frame_F32_02->m_pfVal[uiKey_Next*2+1], fFraction_Of_Range );
                uRet.m_vS_F32_04_1.z = 0.0F;
                uRet.m_vS_F32_04_1.w = 0.0F;
                break;
            case ETgFX_ANIM_DATA__KEY_FRAME_F32_03:
                TgVERIFY(sizeof(STg2_FX_AnimData__Key_Frame_F32_03) == psAnimData->m_uiSize);
                uRet.m_vS_F32_04_1.x = fInt * tgCM_LRP_F32( uAnimData.psKey_Frame_F32_03->m_pfVal[uiKey*3+0], uAnimData.psKey_Frame_F32_03->m_pfVal[uiKey_Next*3+0], fFraction_Of_Range );
                uRet.m_vS_F32_04_1.y = fInt * tgCM_LRP_F32( uAnimData.psKey_Frame_F32_03->m_pfVal[uiKey*3+1], uAnimData.psKey_Frame_F32_03->m_pfVal[uiKey_Next*3+1], fFraction_Of_Range );
                uRet.m_vS_F32_04_1.z = fInt * tgCM_LRP_F32( uAnimData.psKey_Frame_F32_03->m_pfVal[uiKey*3+2], uAnimData.psKey_Frame_F32_03->m_pfVal[uiKey_Next*3+2], fFraction_Of_Range );
                uRet.m_vS_F32_04_1.w = 0.0F;
                break;
            case ETgFX_ANIM_DATA__KEY_FRAME_F32_04:
                TgVERIFY(sizeof(STg2_FX_AnimData__Key_Frame_F32_04) == psAnimData->m_uiSize);
                uRet.m_vF32_04_1 = tgMH_MAD_F32_04_1( uAnimData.psKey_Frame_F32_04->m_pvVal[uiKey_Next], vFraction_Of_Range, uAnimData.psKey_Frame_F32_04->m_pvVal[uiKey] );
                uRet.m_vF32_04_1 = tgMH_NMS_F32_04_1( vFraction_Of_Range, uAnimData.psKey_Frame_F32_04->m_pvVal[uiKey], uRet.m_vF32_04_1 );
                uRet.m_vF32_04_1 = tgMH_MUL_F32_04_1( uRet.m_vF32_04_1, tgMH_SET1_F32_04_1( fInt ) );
                break;

            case ETgFX_ANIM_DATA__INVALID: TgATTRIBUTE_FALLTHROUGH
            case ETgFX_ANIM_DATA__CONSTANT_F32_04: TgATTRIBUTE_FALLTHROUGH
            case ETgFX_ANIM_DATA__SIN_F32: TgATTRIBUTE_FALLTHROUGH
            case ETgFX_ANIM_DATA__SQUARE_F32: TgATTRIBUTE_FALLTHROUGH
            case ETgFX_ANIM_DATA__SPLINE_F32: TgATTRIBUTE_FALLTHROUGH
            case ETgFX_ANIM_DATA__FLICKER_F32: TgATTRIBUTE_FALLTHROUGH
            case ETgFX_ANIM_DATA__CONSTANT_UXX: TgATTRIBUTE_FALLTHROUGH
            case ETgFX_ANIM_DATA__MAX:
                TgS_NO_DEFAULT(return (KTgE_FAIL));
            };

            if (uAnimData.psKey_Frame->m_pfTime[uiKey + 1] >= fT)
                break;
        };
        *pvOUT = uRet.m_vF32_04_1;
        return (KTgS_OK);
    };

    switch (psAnimData->m_enType) {
    case ETgFX_ANIM_DATA__CONSTANT_UXX:
    case ETgFX_ANIM_DATA__KEY_FRAME_F32_01:
    case ETgFX_ANIM_DATA__KEY_FRAME_F32_02:
    case ETgFX_ANIM_DATA__KEY_FRAME_F32_03:
    case ETgFX_ANIM_DATA__KEY_FRAME_F32_04:
        TgERROR(false);
        break;
    case ETgFX_ANIM_DATA__CONSTANT_F32_04:
        TgVERIFY(sizeof(STg2_FX_AnimData__Constant_F32_04) == psAnimData->m_uiSize);
        *pvOUT = tgMH_MUL_F32_04_1( uAnimData.psConstant_F32_04->m_vParam, vT );
        return (KTgS_OK);
    case ETgFX_ANIM_DATA__SIN_F32:
        TgVERIFY(sizeof(STg2_FX_AnimData__Sinusoidal_F32) == psAnimData->m_uiSize);
        break;
    case ETgFX_ANIM_DATA__SQUARE_F32:
        TgVERIFY(sizeof(STg2_FX_AnimData__Square_F32) == psAnimData->m_uiSize);
        break;
    case ETgFX_ANIM_DATA__SPLINE_F32:
        TgVERIFY(sizeof(STg2_FX_AnimData__Spline_F32) == psAnimData->m_uiSize);
        break;
    case ETgFX_ANIM_DATA__FLICKER_F32:
        TgVERIFY(sizeof(STg2_FX_AnimData__Flicker_F32) == psAnimData->m_uiSize);
        break;
    case ETgFX_ANIM_DATA__INVALID: TgATTRIBUTE_FALLTHROUGH
    case ETgFX_ANIM_DATA__MAX:
        TgS_NO_DEFAULT(return (KTgE_FAIL));
    }
    return (KTgE_FAIL);
}


/* ---- tgFX_Evaluate_AnimData_F32_04 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgFX_Evaluate_AnimData_F32_04_1( TgVEC_F32_04_1_P pvOUT, STg2_FX_AnimData_P psAnimData, TgVEC_F32_04_1_C vT )
{
    UTg2_FX_AnimData_C                  uAnimData = { .psAnimData = psAnimData };

    *pvOUT = KTgZERO_V128.m_vF32_04_1;

    if (ETgFX_ANIM_DATA__KEY_FRAME_F32_01 <= psAnimData->m_enType && psAnimData->m_enType <= ETgFX_ANIM_DATA__KEY_FRAME_F32_04)
    {
        TgUN_V128                           uDT = { .m_vF32_04_1 = vT };

        TgUN_V128                           uRet;
        TgFLOAT32                           fDT;
        TgRSIZE                             uiKey, uiKey_Next;
        TgFLOAT32                           fRange;
        TgFLOAT32                           fRelative_Position_In_Range;
        TgFLOAT32                           fFraction_Of_Range;
        TgVEC_F32_04_1                      vFraction_Of_Range;

        fDT = uDT.m_vS_F32_04_1.x;

        if (uAnimData.psKey_Frame->m_nuiKey_Frame < 1)
            return (KTgE_FAIL);

        for (uiKey = 0; uiKey + 1u < uAnimData.psKey_Frame->m_nuiKey_Frame && uAnimData.psKey_Frame->m_pfTime[uiKey + 1] < fDT; ++uiKey) {};

        uiKey_Next = tgCM_MIN_UMAX( uiKey + 1, uAnimData.psKey_Frame->m_nuiKey_Frame - 1 );
        fRange = uAnimData.psKey_Frame->m_pfTime[uiKey_Next] - uAnimData.psKey_Frame->m_pfTime[uiKey];
        fRelative_Position_In_Range = fDT - uAnimData.psKey_Frame->m_pfTime[uiKey];
        fFraction_Of_Range = (!tgCM_NR0_F32( fRange )) ? fRelative_Position_In_Range / fRange : 0.0F;
        vFraction_Of_Range = tgMH_SET1_F32_04_1( fFraction_Of_Range );
        TgVERIFY(fFraction_Of_Range >= 0.0F && fFraction_Of_Range <= 1.0F);
        uRet.m_vF32_04_1 = KTgZERO_F32_04_1;

        switch (psAnimData->m_enType) {
        case ETgFX_ANIM_DATA__KEY_FRAME_F32_01:
            TgVERIFY(sizeof(STg2_FX_AnimData__Key_Frame_F32_01) == psAnimData->m_uiSize);
            uRet.m_vS_F32_04_1.x = tgCM_LRP_F32( uAnimData.psKey_Frame_F32_01->m_pfVal[uiKey], uAnimData.psKey_Frame_F32_01->m_pfVal[uiKey_Next], fFraction_Of_Range );
            uRet.m_vS_F32_04_1.y = 0.0F;
            uRet.m_vS_F32_04_1.z = 0.0F;
            uRet.m_vS_F32_04_1.w = 0.0F;
            break;
        case ETgFX_ANIM_DATA__KEY_FRAME_F32_02:
            TgVERIFY(sizeof(STg2_FX_AnimData__Key_Frame_F32_02) == psAnimData->m_uiSize);
            uRet.m_vS_F32_04_1.x = tgCM_LRP_F32( uAnimData.psKey_Frame_F32_02->m_pfVal[uiKey*2+0], uAnimData.psKey_Frame_F32_02->m_pfVal[uiKey_Next*2+0], fFraction_Of_Range );
            uRet.m_vS_F32_04_1.y = tgCM_LRP_F32( uAnimData.psKey_Frame_F32_02->m_pfVal[uiKey*2+1], uAnimData.psKey_Frame_F32_02->m_pfVal[uiKey_Next*2+1], fFraction_Of_Range );
            uRet.m_vS_F32_04_1.z = 0.0F;
            uRet.m_vS_F32_04_1.w = 0.0F;
            break;
        case ETgFX_ANIM_DATA__KEY_FRAME_F32_03:
            TgVERIFY(sizeof(STg2_FX_AnimData__Key_Frame_F32_03) == psAnimData->m_uiSize);
            uRet.m_vS_F32_04_1.x = tgCM_LRP_F32( uAnimData.psKey_Frame_F32_03->m_pfVal[uiKey*3+0], uAnimData.psKey_Frame_F32_03->m_pfVal[uiKey_Next*3+0], fFraction_Of_Range );
            uRet.m_vS_F32_04_1.y = tgCM_LRP_F32( uAnimData.psKey_Frame_F32_03->m_pfVal[uiKey*3+1], uAnimData.psKey_Frame_F32_03->m_pfVal[uiKey_Next*3+1], fFraction_Of_Range );
            uRet.m_vS_F32_04_1.z = tgCM_LRP_F32( uAnimData.psKey_Frame_F32_03->m_pfVal[uiKey*3+2], uAnimData.psKey_Frame_F32_03->m_pfVal[uiKey_Next*3+2], fFraction_Of_Range );
            uRet.m_vS_F32_04_1.w = 0.0F;
            break;
        case ETgFX_ANIM_DATA__KEY_FRAME_F32_04:
            TgVERIFY(sizeof(STg2_FX_AnimData__Key_Frame_F32_04) == psAnimData->m_uiSize);
            uRet.m_vF32_04_1 = tgMH_MAD_F32_04_1( uAnimData.psKey_Frame_F32_04->m_pvVal[uiKey_Next], vFraction_Of_Range, uAnimData.psKey_Frame_F32_04->m_pvVal[uiKey] );
            uRet.m_vF32_04_1 = tgMH_NMS_F32_04_1( vFraction_Of_Range, uAnimData.psKey_Frame_F32_04->m_pvVal[uiKey], uRet.m_vF32_04_1 );
            break;

        case ETgFX_ANIM_DATA__INVALID: TgATTRIBUTE_FALLTHROUGH
        case ETgFX_ANIM_DATA__CONSTANT_F32_04: TgATTRIBUTE_FALLTHROUGH
        case ETgFX_ANIM_DATA__SIN_F32: TgATTRIBUTE_FALLTHROUGH
        case ETgFX_ANIM_DATA__SQUARE_F32: TgATTRIBUTE_FALLTHROUGH
        case ETgFX_ANIM_DATA__SPLINE_F32: TgATTRIBUTE_FALLTHROUGH
        case ETgFX_ANIM_DATA__FLICKER_F32: TgATTRIBUTE_FALLTHROUGH
        case ETgFX_ANIM_DATA__CONSTANT_UXX: TgATTRIBUTE_FALLTHROUGH
        case ETgFX_ANIM_DATA__MAX:
            TgS_NO_DEFAULT(return (KTgE_FAIL));
        };
        *pvOUT = uRet.m_vF32_04_1;
        return (KTgS_OK);
    };

    switch (psAnimData->m_enType) {
    case ETgFX_ANIM_DATA__CONSTANT_UXX:
    case ETgFX_ANIM_DATA__KEY_FRAME_F32_01:
    case ETgFX_ANIM_DATA__KEY_FRAME_F32_02:
    case ETgFX_ANIM_DATA__KEY_FRAME_F32_03:
    case ETgFX_ANIM_DATA__KEY_FRAME_F32_04:
        TgERROR(false);
        break;
    case ETgFX_ANIM_DATA__CONSTANT_F32_04:
        TgVERIFY(sizeof(STg2_FX_AnimData__Constant_F32_04) == psAnimData->m_uiSize);
        *pvOUT = uAnimData.psConstant_F32_04->m_vParam;
        return (KTgS_OK);
    case ETgFX_ANIM_DATA__SIN_F32:
        TgVERIFY(sizeof(STg2_FX_AnimData__Sinusoidal_F32) == psAnimData->m_uiSize);
        break;
    case ETgFX_ANIM_DATA__SQUARE_F32:
        TgVERIFY(sizeof(STg2_FX_AnimData__Square_F32) == psAnimData->m_uiSize);
        break;
    case ETgFX_ANIM_DATA__SPLINE_F32:
        TgVERIFY(sizeof(STg2_FX_AnimData__Spline_F32) == psAnimData->m_uiSize);
        break;
    case ETgFX_ANIM_DATA__FLICKER_F32:
        TgVERIFY(sizeof(STg2_FX_AnimData__Flicker_F32) == psAnimData->m_uiSize);
        break;
    case ETgFX_ANIM_DATA__INVALID: TgATTRIBUTE_FALLTHROUGH
    case ETgFX_ANIM_DATA__MAX:
        TgS_NO_DEFAULT(return (KTgE_FAIL));
    }
    return (KTgE_FAIL);
}


/* ---- tgFX_Evaluate_Single_AnimData_UXX ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgFX_Evaluate_Single_AnimData_UXX( TgUINT_MAX_P puiOUT, STg2_FX_AnimData_P psAnimData, TgATTRIBUTE_UNUSED TgFLOAT32_C fT )
{
    UTg2_FX_AnimData_C                  uAnimData = { .psAnimData = psAnimData };

    switch (psAnimData->m_enType) {
    case ETgFX_ANIM_DATA__CONSTANT_UXX:
        TgVERIFY(sizeof(STg2_FX_AnimData__Constant_UXX) == psAnimData->m_uiSize);
        *puiOUT = uAnimData.psConstant_UXX->m_uiVal;
        return (KTgS_OK);

    case ETgFX_ANIM_DATA__INVALID: TgATTRIBUTE_FALLTHROUGH
    case ETgFX_ANIM_DATA__CONSTANT_F32_04: TgATTRIBUTE_FALLTHROUGH
    case ETgFX_ANIM_DATA__KEY_FRAME_F32_01: TgATTRIBUTE_FALLTHROUGH
    case ETgFX_ANIM_DATA__KEY_FRAME_F32_02: TgATTRIBUTE_FALLTHROUGH
    case ETgFX_ANIM_DATA__KEY_FRAME_F32_03: TgATTRIBUTE_FALLTHROUGH
    case ETgFX_ANIM_DATA__KEY_FRAME_F32_04: TgATTRIBUTE_FALLTHROUGH
    case ETgFX_ANIM_DATA__SIN_F32: TgATTRIBUTE_FALLTHROUGH
    case ETgFX_ANIM_DATA__SQUARE_F32: TgATTRIBUTE_FALLTHROUGH
    case ETgFX_ANIM_DATA__SPLINE_F32: TgATTRIBUTE_FALLTHROUGH
    case ETgFX_ANIM_DATA__FLICKER_F32: TgATTRIBUTE_FALLTHROUGH
    case ETgFX_ANIM_DATA__MAX:
        TgS_NO_DEFAULT(return (KTgE_FAIL));
    }
    return (KTgE_FAIL);
}
