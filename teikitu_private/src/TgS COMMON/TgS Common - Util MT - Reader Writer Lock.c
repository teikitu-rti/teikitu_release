/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Reader Writer Lock.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_UT_MT__RW_DATA__Update ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_UT_MT__RW_DATA__Update( STg2_UT_ST__RW_DATA_PCU psRW_DATA )
{
    TgUINT_E32                          uiCount;

    TgUINT_E32_C    uiIndex = psRW_DATA->m_uiIndex;
    TgUINT_E32_C    uiMax = psRW_DATA->m_nuiThread;

    for (uiCount = 0; uiCount < uiMax; ++uiCount)
    {
        STg1_MT_SM_P                        psExecute;

        TgUINT_E32_C    uiThread_Index = (uiIndex + uiCount) % KTgMP_MAX_READ_WRITER_LOCK;

        if (psRW_DATA->m_abReader[uiThread_Index])
        {
            TgERROR(psRW_DATA->m_enState != ETgUTM_RW_STATE__Writing);
            TgERROR(nullptr != psRW_DATA->m_psExecute[uiThread_Index]);

            psRW_DATA->m_enState = ETgUTM_RW_STATE__Reading;
            ++psRW_DATA->m_nuiReader;
            ++psRW_DATA->m_uiIndex;
            --psRW_DATA->m_nuiThread;
            psExecute = psRW_DATA->m_psExecute[uiThread_Index];
            psRW_DATA->m_psExecute[uiThread_Index] = nullptr;
            tgPM_MT_SM_Signal( psExecute, 1 );
            continue;
        }
        else
        {
            if (0 == psRW_DATA->m_nuiReader)
            {
                TgERROR(psRW_DATA->m_enState == ETgUTM_RW_STATE__Waiting);
                TgERROR(nullptr != psRW_DATA->m_psExecute[uiThread_Index]);

                psRW_DATA->m_enState = ETgUTM_RW_STATE__Writing;
                ++psRW_DATA->m_uiIndex;
                --psRW_DATA->m_nuiThread;
                psExecute = psRW_DATA->m_psExecute[uiThread_Index];
                psRW_DATA->m_psExecute[uiThread_Index] = nullptr;
                tgPM_MT_SM_Signal( psExecute, 1 );
            };

            return;
        };
    };
}
