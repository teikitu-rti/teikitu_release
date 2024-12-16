/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (POSIX) Common - STg1_MT_SM.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_CTG1_MP_SM_INL) && TgCOMPILE__THREAD
#define TGS_COMMON_CTG1_MP_SM_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgPM_MT_SM_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgPM_MT_SM_Init( STg1_MT_SM_PCU NONULL psSM, TgCHAR_U8_CPCU OKNULL mbzName, TgUINT_F32_C uiInit, TgUINT_F32_C uiMax )
{
    if (nullptr == mbzName)
    {
        tgMM_Set_U08_0x00( psSM->m_mbzName, sizeof( psSM->m_mbzName ) );

        while (TgSUCCEEDED(tgCM_Random_Name( psSM->m_mbzName, KTgMAX_SEMAPHORE_NAME )))
        {
            psSM->m_hSemaphore = sem_open( psSM->m_mbzName, O_CREAT | O_EXCL, 0644, uiInit );

            if (SEM_FAILED != psSM->m_hSemaphore)
            {
                return (KTgS_OK);
            };
        };
        return (KTgE_FAIL);
    };

    if (tgUSZ_Length_U08(mbzName, KTgMAX_RSIZE) >= KTgMAX_SEMAPHORE_NAME)
    {
        return (KTgE_FAIL);
    };

    tgUSZ_Copy( psSM->m_mbzName, KTgMAX_SEMAPHORE_NAME, mbzName, KTgMAX_RSIZE );
    psSM->m_hSemaphore = sem_open( psSM->m_mbzName, O_CREAT | O_EXCL, 0644, uiInit );

    TgCRITICAL(SEM_FAILED != psSM->m_hSemaphore);
    return (SEM_FAILED == psSM->m_hSemaphore ? KTgE_FAIL : KTgS_OK);
}


/* ---- tgPM_MT_SM_Free ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgPM_MT_SM_Free( STg1_MT_SM_PCU NONULL psSM )
{
    TgSINT_F32                          iRet;

    if (0 != psSM->m_hSemaphore)
    {
        iRet = sem_close( psSM->m_hSemaphore );
        TgVERIFY(0 == iRet);
        iRet = sem_unlink( psSM->m_mbzName );
        TgVERIFY(0 == iRet);
        psSM->m_hSemaphore = SEM_FAILED;
    };
}


/* ---- tgPM_MT_SM_Wait_Block ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgPM_MT_SM_Wait_Block( STg1_MT_SM_PCU NONULL psSM )
{
    TgVERIFY(0 == sem_wait( psSM->m_hSemaphore ));
}


/* ---- tgPM_MT_SM_Wait ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgPM_MT_SM_Wait( STg1_MT_SM_PCU NONULL psSM )
{
    TgSINT_F32                          iRet;
    iRet = sem_trywait( psSM->m_hSemaphore );
    return (0 != iRet ? KTgE_FAIL : KTgS_OK);
}


/* ---- tgPM_MT_SM_Signal -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgPM_MT_SM_Signal( STg1_MT_SM_PCU NONULL psSM, TgUINT_F32_C nuiSignal )
{
    TgSINT_F32                          iRet;

    for (TgRSIZE uiIndex = 0; uiIndex < nuiSignal; ++uiIndex)
    {
        iRet = sem_post( psSM->m_hSemaphore );
        TgVERIFY(0 == iRet);
    };
}


/* =============================================================================================================================================================================== */
#endif
