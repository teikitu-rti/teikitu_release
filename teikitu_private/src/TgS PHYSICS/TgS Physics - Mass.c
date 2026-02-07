/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Mass.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Physics - Internal.inl"


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Mass_Reset ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Mass_Reset( STg2_PH_Mass_PCU psMS )
{
    tgPH_Mass_Set_Mass( psMS, 0.0F, ETgPM_UNKNOWN, nullptr );
}


/* ---- tgPH_Mass_Set_Mass ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Mass_Set_Mass( STg2_PH_Mass_PC psMS, TgFLOAT32_C fMass, ETgPM_SHORT enPM, UTg2_CO_Primitive_F32_04_P puPM )
{
    if (!(fMass > 0.0F))
    {
        tgMM_Set_U08_0x00( &psMS->m_mMOI, sizeof(psMS->m_mMOI) );
        tgMM_Set_U08_0x00( &psMS->m_mInv_MOI, sizeof(psMS->m_mInv_MOI) );
        psMS->m_vCG = KTgUNIT_W_F32_04_1;
        psMS->m_uMass.m_vF32_04_1 = KTgZERO_F32_04_1;
        psMS->m_uInv_Mass.m_vF32_04_1 = KTgZERO_F32_04_1;
        return (KTgS_OK);
    };

    psMS->m_uMass.m_vF32_04_1 = tgMH_SET1_F32_04_1( fMass );
    psMS->m_uInv_Mass.m_vF32_04_1 = tgMH_SET1_F32_04_1( 1.0F / fMass );

    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
    switch (enPM) {
    case ETgPM_BX: { /* Width = x, Height = y, Depth =z */
        TgVEC_UN_F32_04_1_C                 uExtent = { .m_vF32_04_1 = puPM->m_sBX.m_vExtent };
        TgFLOAT32_C                         fMass_Coeff = (1.0F / 12.0F) * fMass;
        TgVEC_UN_F32_04_3                   uM0;

        tgMM_Set_U08_0x00( &uM0, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = fMass_Coeff * (uExtent.m_vS_F32_04_1.y*uExtent.m_vS_F32_04_1.y + uExtent.m_vS_F32_04_1.z*uExtent.m_vS_F32_04_1.z);
        uM0.m_mS_F32_04_3._22 = fMass_Coeff * (uExtent.m_vS_F32_04_1.x*uExtent.m_vS_F32_04_1.x + uExtent.m_vS_F32_04_1.z*uExtent.m_vS_F32_04_1.z);
        uM0.m_mS_F32_04_3._33 = fMass_Coeff * (uExtent.m_vS_F32_04_1.x*uExtent.m_vS_F32_04_1.x + uExtent.m_vS_F32_04_1.y*uExtent.m_vS_F32_04_1.y);
        tgMM_Copy( &psMS->m_mMOI, sizeof(psMS->m_mMOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = 1.0F / uM0.m_mS_F32_04_3._11;
        uM0.m_mS_F32_04_3._22 = 1.0F / uM0.m_mS_F32_04_3._22;
        uM0.m_mS_F32_04_3._33 = 1.0F / uM0.m_mS_F32_04_3._33;
        tgMM_Copy( &psMS->m_mInv_MOI, sizeof(psMS->m_mInv_MOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        psMS->m_vCG = KTgUNIT_W_F32_04_1;
        tgPH_Mass_Rotate_Mat( psMS, &puPM->m_sBX.m_mReference_Frame );
    } break;

    case ETgPM_SP: {
        TgVEC_UN_F32_04_1_C                 uRadius = { .m_vF32_04_1 = puPM->m_sSP.m_vRadius };
        TgFLOAT32_C                         fVal = 0.4F * fMass * uRadius.m_vS_F32_04_1.x;
        TgFLOAT32_C                         fInv_Val = 1.0F / fVal;
        TgVEC_UN_F32_04_3                   uM0;

        tgMM_Set_U08_0x00( &uM0, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = fVal;
        uM0.m_mS_F32_04_3._22 = fVal;
        uM0.m_mS_F32_04_3._33 = fVal;
        tgMM_Copy( &psMS->m_mMOI, sizeof(psMS->m_mMOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = fInv_Val;
        uM0.m_mS_F32_04_3._22 = fInv_Val;
        uM0.m_mS_F32_04_3._33 = fInv_Val;
        tgMM_Copy( &psMS->m_mInv_MOI, sizeof(psMS->m_mInv_MOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        psMS->m_vCG = KTgUNIT_W_F32_04_1;
    } break;

    case ETgPM_TB: TgATTRIBUTE_FALLTHROUGH
    case ETgPM_CY: {
        TgVEC_UN_F32_04_1_C                 uRadius = { .m_vF32_04_1 = puPM->m_sTB.m_vRadius };
        TgFLOAT32_C                         fRadius = uRadius.m_vS_F32_04_1.x;
        TgVEC_UN_F32_04_1_C                 uExtent = { .m_vF32_04_1 = puPM->m_sTB.m_vExtent };
        TgFLOAT32_C                         fTB_Length = uExtent.m_vS_F32_04_1.x*2.0F;

        TgFLOAT32_C                         fIA = fMass*(0.25f*fRadius*fRadius + (1.0F/12.0F)*fTB_Length*fTB_Length);
        TgFLOAT32_C                         fIB = fMass*0.5F*fRadius*fRadius;
        TgVEC_UN_F32_04_3                   uM0;

        tgMM_Set_U08_0x00( &uM0, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = fIA;
        uM0.m_mS_F32_04_3._22 = fIB;
        uM0.m_mS_F32_04_3._33 = fIA;
        tgMM_Copy( &psMS->m_mMOI, sizeof(psMS->m_mMOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        psMS->m_vCG = KTgUNIT_W_F32_04_1;
        tgPH_Mass_Rotate_Mat( psMS, &puPM->m_sTB.m_mReference_Frame );
    } break;

    case ETgPM_CP: {
        TgVEC_UN_F32_04_1_C                 uRadius = { .m_vF32_04_1 = puPM->m_sTB.m_vRadius };
        TgFLOAT32_C                         fRadius = uRadius.m_vS_F32_04_1.x;
        TgVEC_UN_F32_04_1_C                 uExtent = { .m_vF32_04_1 = puPM->m_sTB.m_vExtent };
        TgFLOAT32_C                         fTB_Length = uExtent.m_vS_F32_04_1.x*2.0F;

        TgFLOAT32_C                         fSP_Vol = (4.0F / 3.0F)*KTgPI_F32*fRadius*fRadius*fRadius; /* Volume for a sphere */
        TgFLOAT32_C                         fTB_Vol = KTgPI_F32*fRadius*fRadius*fTB_Length;
        TgFLOAT32_C                         fSP_Mass = (fSP_Vol / (fSP_Vol + fTB_Vol))*fMass;
        TgFLOAT32_C                         fTB_Mass = (fTB_Vol / (fSP_Vol + fTB_Vol))*fMass;
        TgFLOAT32_C                         fIA = fTB_Mass*(0.25f*fRadius*fRadius + (1.0F/12.0F)*fTB_Length*fTB_Length)
                                                + fSP_Mass*(0.40f*fRadius*fRadius + 0.375F*fRadius*fTB_Length + 0.25F*fTB_Length*fTB_Length);
        TgFLOAT32_C                         fIB = (fTB_Mass*0.5F + fSP_Mass*0.40f)*fRadius*fRadius;
        TgVEC_UN_F32_04_3                   uM0;

        tgMM_Set_U08_0x00( &uM0, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = fIA;
        uM0.m_mS_F32_04_3._22 = fIB;
        uM0.m_mS_F32_04_3._33 = fIA;
        tgMM_Copy( &psMS->m_mMOI, sizeof(psMS->m_mMOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        psMS->m_vCG = KTgUNIT_W_F32_04_1;
        tgPH_Mass_Rotate_Mat( psMS, &puPM->m_sTB.m_mReference_Frame );
    } break;

    default: {
        TgVEC_UN_F32_04_3                   uM0;
        TgFLOAT32_C                         fInv_Mass = 1.0F / fMass;

        tgMM_Set_U08_0x00( &uM0, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = fMass;
        uM0.m_mS_F32_04_3._22 = fMass;
        uM0.m_mS_F32_04_3._33 = fMass;
        tgMM_Copy( &psMS->m_mMOI, sizeof(psMS->m_mMOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = fInv_Mass;
        uM0.m_mS_F32_04_3._22 = fInv_Mass;
        uM0.m_mS_F32_04_3._33 = fInv_Mass;
        tgMM_Copy( &psMS->m_mInv_MOI, sizeof(psMS->m_mInv_MOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        psMS->m_vCG = KTgUNIT_W_F32_04_1;
    } break;
    };
    TgWARN_DISABLE_POP()
    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Private Functions                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Mass_Move ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Mass_Move( STg2_PH_Mass_PC psMass, TgVEC_F32_04_1_C vDS )
{
    TgUN_V128                           u00, u01, u02, u03, u04;
    TgUN_V128                           u10, u11, u12, u13, u14;
    TgUN_V128                           u20, u21, u22;
    TgVEC_F32_04_4                      m44;

    u00.m_vF32_04_1 = tgMH_Init_Vector_F32_04_1( psMass->m_vCG );
    u01.m_vF32_04_1 = tgMH_NEG_F32_04_1( u00.m_vF32_04_1 );
    u10.m_vF32_04_1 = tgMH_ADD_F32_04_1( u00.m_vF32_04_1, vDS );
    u11.m_vF32_04_1 = tgMH_SUB_F32_04_1( u10.m_vF32_04_1, vDS );

    u02.m_vS_F32_04_1.x = u01.m_vS_F32_04_1.z * u00.m_vS_F32_04_1.z + u00.m_vS_F32_04_1.y * u01.m_vS_F32_04_1.y;
    u02.m_vS_F32_04_1.y = u00.m_vS_F32_04_1.y * u00.m_vS_F32_04_1.x;
    u02.m_vS_F32_04_1.z = u01.m_vS_F32_04_1.z * u01.m_vS_F32_04_1.x;
    u02.m_vS_F32_04_1.w = 0.0F;

    u03.m_vS_F32_04_1.x = u02.m_vS_F32_04_1.y;
    u03.m_vS_F32_04_1.y = u01.m_vS_F32_04_1.z * u00.m_vS_F32_04_1.z + u01.m_vS_F32_04_1.x * u00.m_vS_F32_04_1.x;
    u03.m_vS_F32_04_1.z = u00.m_vS_F32_04_1.y * u00.m_vS_F32_04_1.z;
    u03.m_vS_F32_04_1.w = 0.0F;

    u04.m_vS_F32_04_1.x = u02.m_vS_F32_04_1.z;
    u04.m_vS_F32_04_1.y = u03.m_vS_F32_04_1.z;
    u04.m_vS_F32_04_1.z = u00.m_vS_F32_04_1.y * u01.m_vS_F32_04_1.y + u00.m_vS_F32_04_1.x * u01.m_vS_F32_04_1.x;
    u04.m_vS_F32_04_1.w = 0.0F;

    u12.m_vS_F32_04_1.x = u11.m_vS_F32_04_1.z * u10.m_vS_F32_04_1.z + u10.m_vS_F32_04_1.y * u11.m_vS_F32_04_1.y;
    u12.m_vS_F32_04_1.y = u10.m_vS_F32_04_1.y * u10.m_vS_F32_04_1.x;
    u12.m_vS_F32_04_1.z = u11.m_vS_F32_04_1.z * u11.m_vS_F32_04_1.x;
    u12.m_vS_F32_04_1.w = 0.0F;

    u13.m_vS_F32_04_1.x = u12.m_vS_F32_04_1.y;
    u13.m_vS_F32_04_1.y = u11.m_vS_F32_04_1.z * u10.m_vS_F32_04_1.z + u11.m_vS_F32_04_1.x * u10.m_vS_F32_04_1.x;
    u13.m_vS_F32_04_1.z = u10.m_vS_F32_04_1.y * u10.m_vS_F32_04_1.z;
    u13.m_vS_F32_04_1.w = 0.0F;

    u14.m_vS_F32_04_1.x = u12.m_vS_F32_04_1.z;
    u14.m_vS_F32_04_1.y = u13.m_vS_F32_04_1.z;
    u14.m_vS_F32_04_1.z = u10.m_vS_F32_04_1.y * u11.m_vS_F32_04_1.y + u10.m_vS_F32_04_1.x * u11.m_vS_F32_04_1.x;
    u14.m_vS_F32_04_1.w = 0.0F;

    u20.m_vF32_04_1 = tgMH_SUB_F32_04_1( u02.m_vF32_04_1, u12.m_vF32_04_1 );
    u21.m_vF32_04_1 = tgMH_SUB_F32_04_1( u03.m_vF32_04_1, u13.m_vF32_04_1 );
    u22.m_vF32_04_1 = tgMH_SUB_F32_04_1( u04.m_vF32_04_1, u14.m_vF32_04_1 );

    psMass->m_mMOI.m_avCol[0] = tgMH_MAD_F32_04_1( u20.m_vF32_04_1, psMass->m_uMass.m_vF32_04_1, psMass->m_mMOI.m_avCol[0] );
    psMass->m_mMOI.m_avCol[1] = tgMH_MAD_F32_04_1( u21.m_vF32_04_1, psMass->m_uMass.m_vF32_04_1, psMass->m_mMOI.m_avCol[1] );
    psMass->m_mMOI.m_avCol[2] = tgMH_MAD_F32_04_1( u22.m_vF32_04_1, psMass->m_uMass.m_vF32_04_1, psMass->m_mMOI.m_avCol[2] );

    psMass->m_vCG = tgMH_ADD_F32_04_1( psMass->m_vCG, vDS );

    tgMH_INV_F32_04_3( &m44, &psMass->m_mMOI );

    psMass->m_mInv_MOI.m_vC0 = m44.m_vC0;
    psMass->m_mInv_MOI.m_vC1 = m44.m_vC1;
    psMass->m_mInv_MOI.m_vC2 = m44.m_vC2;

    return (KTgS_OK);
}


/* ---- tgPH_Mass_Rotate_Mat ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Reference: https://ocw.mit.edu/courses/16-07-dynamics-fall-2009/dd277ec654440f4c2b5b07d6c286c3fd_MIT16_07F09_Lec26.pdf                                                          */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Mass_Rotate_Mat( STg2_PH_Mass_PC psMass, TgVEC_F32_04_3_CPCU pmR0 )
{
    TgVEC_F32_04_4                      mR0_TR, mMoI, mMoI_INV;
    TgVEC_F32_04_3                      mTMP;

    /* I = [T][I][T] T */

    tgMH_CAT_F32_04_3( &mTMP, pmR0, &psMass->m_mMOI );
    tgMH_TR_F32_04_3( &mR0_TR, pmR0 );
    tgMH_CAT_34_44_F32_04_4( &mMoI, &mTMP, &mR0_TR );
    tgMH_INV_F32_04_4( &mMoI_INV, &mMoI );

    psMass->m_mMOI.m_avCol[0] = mMoI.m_vC0;
    psMass->m_mMOI.m_avCol[1] = mMoI.m_vC1;
    psMass->m_mMOI.m_avCol[2] = mMoI.m_vC2;

    psMass->m_vCG = tgMH_TX_F32_04_3( psMass->m_vCG, pmR0 );

    psMass->m_mInv_MOI.m_vC0 = mMoI_INV.m_vC0;
    psMass->m_mInv_MOI.m_vC1 = mMoI_INV.m_vC1;
    psMass->m_mInv_MOI.m_vC2 = mMoI_INV.m_vC2;

    return (KTgS_OK);
}
