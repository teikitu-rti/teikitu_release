/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (POSIX) Common - STg1_MT_SM.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if TgCOMPILE__THREAD

#include <fcntl.h>


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgPM_MT_SM_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPM_MT_SM_Init( STg1_MT_SM_PCU psSM, TgCHAR_U8_CPCU TgANALYSIS_OK_NULL mbzName, TgUINT_E32_C uiInit, TgATTRIBUTE_UNUSED TgUINT_E32_C uiMax )
{
    if (nullptr == mbzName)
    {
        tgMM_Set_U08_0x00( psSM->m_mbzName, sizeof( psSM->m_mbzName ) );

        while (TgSUCCEEDED(tgCM_Random_Name( (char*)psSM->m_mbzName, KTgMAX_SEMAPHORE_NAME )))
        {
            psSM->m_hSemaphore = sem_open( (const char*)psSM->m_mbzName, O_CREAT | O_EXCL, 0644, uiInit );

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
    psSM->m_hSemaphore = sem_open( (const char*)psSM->m_mbzName, O_CREAT | O_EXCL, 0644, uiInit );

    TgCRITICAL(SEM_FAILED != psSM->m_hSemaphore);
    return (SEM_FAILED == psSM->m_hSemaphore ? KTgE_FAIL : KTgS_OK);
}


/* ---- tgPM_MT_SM_Free ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPM_MT_SM_Free( STg1_MT_SM_PCU psSM )
{
    TgSINT_E32                          iRet;

    if (0 != psSM->m_hSemaphore)
    {
        iRet = sem_close( psSM->m_hSemaphore );
        TgVERIFY(0 == iRet);
        iRet = sem_unlink( (const char*)psSM->m_mbzName );
        TgVERIFY(0 == iRet);
        psSM->m_hSemaphore = SEM_FAILED;
    };
}


/* ---- tgPM_MT_SM_Wait_Block ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPM_MT_SM_Wait_Block( STg1_MT_SM_PCU psSM )
{
    TgVERIFY(0 == sem_wait( psSM->m_hSemaphore ));
}


/* ---- tgPM_MT_SM_Wait ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPM_MT_SM_Wait( STg1_MT_SM_PCU psSM )
{
    TgSINT_E32                          iRet;
    iRet = sem_trywait( psSM->m_hSemaphore );
    return (0 != iRet ? KTgE_FAIL : KTgS_OK);
}


/* ---- tgPM_MT_SM_Signal -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPM_MT_SM_Signal( STg1_MT_SM_PCU psSM, TgUINT_E32_C nuiSignal )
{
    TgSINT_E32                          iRet;

    for (TgRSIZE uiIndex = 0; uiIndex < nuiSignal; ++uiIndex)
    {
        iRet = sem_post( psSM->m_hSemaphore );
        TgVERIFY(0 == iRet);
    };
}


/* =============================================================================================================================================================================== */
#endif
