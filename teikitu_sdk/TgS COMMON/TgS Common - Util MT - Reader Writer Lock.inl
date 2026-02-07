/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Reader Writer Lock.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_MT_READER_WRITER_LOCK_INL)
#define TGS_COMMON_UTIL_MT_READER_WRITER_LOCK_INL

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgINLINE TgVOID
tgCM_UT_MT__RW_DATA__Init(
    STg2_UT_ST__RW_DATA_PCU );

TgINLINE TgVOID
tgCM_UT_MT__RW_DATA__Free(
    STg2_UT_ST__RW_DATA_PCU );

TgEXTN TgVOID
tgCM_UT_MT__RW_DATA__Update(
    STg2_UT_ST__RW_DATA_PCU );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Internal Functions ------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- tgCM_UT_MT__RW_DATA__Init ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_MT__RW_DATA__Init( STg2_UT_ST__RW_DATA_PCU psRW_DATA )
{
    tgMM_Set_U08_0x00( psRW_DATA, sizeof( STg2_UT_ST__RW_DATA ) );
    tgMM_Set_U08_0xFF( psRW_DATA->m_asThread, sizeof( psRW_DATA->m_asThread ) );
}


/* ---- tgCM_UT_MT__RW_DATA__Free ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_MT__RW_DATA__Free( TgATTRIBUTE_UNUSED_PARAM_CHECK STg2_UT_ST__RW_DATA_PCU psRW_DATA )
{
#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK
    TgSINT_E32                          iIndex;

    TgERROR(0 == psRW_DATA->m_nuiThread);
    for (iIndex = 0; iIndex < KTgMP_MAX_READ_WRITER_LOCK; ++iIndex)
    {
        TgERROR(nullptr == psRW_DATA->m_psExecute[iIndex]);
    }
/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK */
#endif
}


/* ---- FIFO Atomic Reader Writer Lock ------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- tgCM_UT_LF__RW__Init ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__RW__Init( STg2_UT_LF__RW_PCU psRW )
{
    TgSTD_ATOMIC(store)( &psRW->m_uiRW_REQ, 0 );
    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__RW__Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW__Free( TgATTRIBUTE_UNUSED_PARAM_CHECK STg2_UT_LF__RW_PCU psRW )
{
#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK
    STg2_UT_ST__RW_REQ                  sRW_REQ;

    sRW_REQ.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    TgERROR(sRW_REQ.m_uiRead == sRW_REQ.m_uiRequest);
    TgERROR(sRW_REQ.m_uiRead == sRW_REQ.m_uiWrite);
/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK */
#endif
}


/* ---- tgCM_UT_LF__RW__Enter_Read_Yield_Block ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW__Enter_Read_Yield_Block( STg2_UT_LF__RW_PCU psRW )
{
    STg2_UT_ST__RW_REQ                  sOrig, sNew;

    sOrig.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        sNew.m_uiRW_REQ = sOrig.m_uiRW_REQ;
        sNew.m_uiRequest = sOrig.m_uiRequest + 1u;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak_explicit)( &psRW->m_uiRW_REQ, &sOrig.m_uiRW_REQ, sNew.m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed), TgSTD_MEMORY_ORDER(relaxed) ));

    while (sNew.m_uiRead != sOrig.m_uiRequest)
    {
        tgTR_Yield();
        sNew.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    };

    do
    {
        sOrig.m_uiRW_REQ = sNew.m_uiRW_REQ;
        sOrig.m_uiRead = sNew.m_uiRead + 1u;
    }
    while (!TgSTD_ATOMIC(compare_exchange_weak_explicit)( &psRW->m_uiRW_REQ, &sNew.m_uiRW_REQ, sOrig.m_uiRW_REQ, TgSTD_MEMORY_ORDER(seq_cst), TgSTD_MEMORY_ORDER(relaxed) ));
}


/* ---- tgCM_UT_LF__RW__Enter_Read_Spin_Block ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW__Enter_Read_Spin_Block( STg2_UT_LF__RW_PCU psRW )
{
    STg2_UT_ST__RW_REQ                  sOrig, sNew;

    sOrig.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        sNew.m_uiRW_REQ = sOrig.m_uiRW_REQ;
        sNew.m_uiRequest = sOrig.m_uiRequest + 1u;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak_explicit)( &psRW->m_uiRW_REQ, &sOrig.m_uiRW_REQ, sNew.m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed), TgSTD_MEMORY_ORDER(relaxed) ));

    while (sNew.m_uiRead != sOrig.m_uiRequest)
    {
        tgTR_Pause();
        sNew.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    };

    do
    {
        sOrig.m_uiRW_REQ = sNew.m_uiRW_REQ;
        sOrig.m_uiRead = sNew.m_uiRead + 1u;
    }
    while (!TgSTD_ATOMIC(compare_exchange_weak_explicit)( &psRW->m_uiRW_REQ, &sNew.m_uiRW_REQ, sOrig.m_uiRW_REQ, TgSTD_MEMORY_ORDER(seq_cst), TgSTD_MEMORY_ORDER(relaxed) ));
}


/* ---- tgCM_UT_LF__RW__Enter_Read ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__RW__Enter_Read( STg2_UT_LF__RW_PCU psRW )
{
    STg2_UT_ST__RW_REQ                  sOrig, sTest, sNew, sCurrent;

    sOrig.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );

    sTest.m_uiRW_REQ = sOrig.m_uiRW_REQ;
    sTest.m_uiRead = sOrig.m_uiRequest;

    sNew.m_uiRW_REQ = sTest.m_uiRW_REQ;
    sNew.m_uiRequest = sOrig.m_uiRequest + 1u;

    if (!TgSTD_ATOMIC(compare_exchange_strong_explicit)( &psRW->m_uiRW_REQ, &sTest.m_uiRW_REQ, sNew.m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed), TgSTD_MEMORY_ORDER(relaxed) ))
    {
        return (KTgE_FAIL);
    }
    sCurrent.m_uiRW_REQ = sNew.m_uiRW_REQ;

    do
    {   /* Avoid using TgSTD_ATOMIC(fetch_add) due to overflow during addition */
        sNew.m_uiRW_REQ = sCurrent.m_uiRW_REQ;
        sNew.m_uiRead = sCurrent.m_uiRead + 1u;
    }
    while (!TgSTD_ATOMIC(compare_exchange_weak_explicit)( &psRW->m_uiRW_REQ, &sCurrent.m_uiRW_REQ, sNew.m_uiRW_REQ, TgSTD_MEMORY_ORDER(seq_cst), TgSTD_MEMORY_ORDER(relaxed) ));

    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__RW__Exit_Read ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW__Exit_Read( STg2_UT_LF__RW_PCU psRW )
{
    STg2_UT_ST__RW_REQ                  sOrig, sNew;

    sOrig.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        sNew.m_uiRW_REQ = sOrig.m_uiRW_REQ;
        sNew.m_uiWrite = sOrig.m_uiWrite + 1u;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak_explicit)( &psRW->m_uiRW_REQ, &sOrig.m_uiRW_REQ, sNew.m_uiRW_REQ, TgSTD_MEMORY_ORDER(seq_cst), TgSTD_MEMORY_ORDER(relaxed) ));
}


/* ---- tgCM_UT_LF__RW__Enter_Write_Yield_Block ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW__Enter_Write_Yield_Block( STg2_UT_LF__RW_PCU psRW )
{
    STg2_UT_ST__RW_REQ                  sOrig, sNew;

    sOrig.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {   /* Avoid using TgSTD_ATOMIC(fetch_add) due to overflow during addition */
        sNew.m_uiRW_REQ = sOrig.m_uiRW_REQ;
        sNew.m_uiRequest = sOrig.m_uiRequest + 1u;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak_explicit)( &psRW->m_uiRW_REQ, &sOrig.m_uiRW_REQ, sNew.m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed), TgSTD_MEMORY_ORDER(relaxed) ));

    while (sNew.m_uiWrite != sOrig.m_uiRequest)
    {
        tgTR_Yield();
        sNew.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    };

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
}


/* ---- tgCM_UT_LF__RW__Enter_Write_Spin_Block ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW__Enter_Write_Spin_Block( STg2_UT_LF__RW_PCU psRW )
{
    STg2_UT_ST__RW_REQ                  sOrig, sNew;

    sOrig.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {   /* Avoid using TgSTD_ATOMIC(fetch_add) due to overflow during addition */
        sNew.m_uiRW_REQ = sOrig.m_uiRW_REQ;
        sNew.m_uiRequest = sOrig.m_uiRequest + 1u;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak_explicit)( &psRW->m_uiRW_REQ, &sOrig.m_uiRW_REQ, sNew.m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed), TgSTD_MEMORY_ORDER(relaxed) ));

    while (sNew.m_uiWrite != sOrig.m_uiRequest)
    {
        tgTR_Pause();
        sNew.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    };

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
}


/* ---- tgCM_UT_LF__RW__Enter_Write ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__RW__Enter_Write( STg2_UT_LF__RW_PCU psRW )
{
    STg2_UT_ST__RW_REQ                  sOrig, sTest, sNew;

    sOrig.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );

    sTest.m_uiWrite = sOrig.m_uiRequest;
    sTest.m_uiRead = sOrig.m_uiRequest;
    sTest.m_uiRequest = sOrig.m_uiRequest;
    sTest.m_uiUnused = sOrig.m_uiUnused;

    sNew.m_uiRW_REQ = sTest.m_uiRW_REQ;
    sNew.m_uiRequest = sOrig.m_uiRequest + 1u;

    if (!TgSTD_ATOMIC(compare_exchange_strong_explicit)( &psRW->m_uiRW_REQ, &sTest.m_uiRW_REQ, sNew.m_uiRW_REQ, TgSTD_MEMORY_ORDER(seq_cst), TgSTD_MEMORY_ORDER(relaxed) ))
    {
        return (KTgE_FAIL);
    }

    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__RW__Test_Write ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCM_UT_LF__RW__Test_Write( STg2_UT_LF__RW_PCU psRW )
{
    STg2_UT_ST__RW_REQ                  sTest;

    sTest.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    return (sTest.m_uiWrite >= sTest.m_uiRead);
}


/* ---- tgCM_UT_LF__RW__Exit_Write ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW__Exit_Write( STg2_UT_LF__RW_PCU psRW )
{
    STg2_UT_ST__RW_REQ                  sOrig, sNew;

    sOrig.m_uiRW_REQ = TgSTD_ATOMIC(load_explicit)( &psRW->m_uiRW_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {   /* Avoid using TgSTD_ATOMIC(fetch_add) due to overflow during addition */
        sNew.m_uiRW_REQ = sOrig.m_uiRW_REQ;
        sNew.m_uiRead = sOrig.m_uiRead + 1u;
        sNew.m_uiWrite = sOrig.m_uiWrite + 1u;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak_explicit)( &psRW->m_uiRW_REQ, &sOrig.m_uiRW_REQ, sNew.m_uiRW_REQ, TgSTD_MEMORY_ORDER(seq_cst), TgSTD_MEMORY_ORDER(relaxed) ));
}


/* ---- FIFO Spin Lock Reader Writer Lock ---------------------------------------------------------------------------------------------------------------------------------------- */

#if TgCOMPILE__THREAD

/* ---- tgCM_UT_LF__RW_SN__Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__RW_SN__Init( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    TgVERIFY( KTgS_OK == tgCM_UT_LF__SN__Init( &psRW_SN->m_sLock.m_sLock ) );
    tgCM_UT_MT__RW_DATA__Init( &psRW_SN->m_sData );
    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__RW_SN__Free -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW_SN__Free( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__RW_SN__Enter_Write_Spin_Block( psRW_SN );
    tgCM_UT_MT__RW_DATA__Free( &psRW_SN->m_sData );
    tgCM_UT_LF__SN__Free_Unsafe( &psRW_SN->m_sLock.m_sLock );
}


/* ---- tgCM_UT_LF__RW_SN__Enter_Read_Yield_Block -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW_SN__Enter_Read_Yield_Block( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__SN__Lock_Yield( &psRW_SN->m_sLock.m_sLock );

    if (ETgUTM_RW_STATE__Writing != psRW_SN->m_sData.m_enState)
    {
        psRW_SN->m_sData.m_enState = ETgUTM_RW_STATE__Reading;
        ++psRW_SN->m_sData.m_nuiReader;
        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
    }
    else
    {
        STg1_MT_SM                          sExecute;
        TgUINT_E32                          iIndex;

        TgERROR(psRW_SN->m_sData.m_nuiThread < KTgMP_MAX_READ_WRITER_LOCK);

        TgVERIFY(KTgS_OK == tgPM_MT_SM_Init( &sExecute, nullptr, 0, 1 ));

        iIndex = (psRW_SN->m_sData.m_uiIndex + psRW_SN->m_sData.m_nuiThread) % KTgMP_MAX_READ_WRITER_LOCK;
        psRW_SN->m_sData.m_asThread[iIndex] = tgTR_Query_Id();
        psRW_SN->m_sData.m_abReader[iIndex] = true;
        psRW_SN->m_sData.m_psExecute[iIndex] = &sExecute;
        ++psRW_SN->m_sData.m_nuiThread;

        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );

        tgPM_MT_SM_Wait_Block( &sExecute );
        tgPM_MT_SM_Free( &sExecute );
    };
}


/* ---- tgCM_UT_LF__RW_SN__Enter_Read_Spin_Block --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW_SN__Enter_Read_Spin_Block( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__SN__Lock_Spin( &psRW_SN->m_sLock.m_sLock );

    if (ETgUTM_RW_STATE__Writing != psRW_SN->m_sData.m_enState)
    {
        psRW_SN->m_sData.m_enState = ETgUTM_RW_STATE__Reading;
        ++psRW_SN->m_sData.m_nuiReader;
        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
    }
    else
    {
        STg1_MT_SM                          sExecute;
        TgUINT_E32                          iIndex;

        TgERROR(psRW_SN->m_sData.m_nuiThread < KTgMP_MAX_READ_WRITER_LOCK);

        TgVERIFY(KTgS_OK == tgPM_MT_SM_Init( &sExecute, nullptr, 0, 1 ));

        iIndex = (psRW_SN->m_sData.m_uiIndex + psRW_SN->m_sData.m_nuiThread) % KTgMP_MAX_READ_WRITER_LOCK;
        psRW_SN->m_sData.m_asThread[iIndex] = tgTR_Query_Id();
        psRW_SN->m_sData.m_abReader[iIndex] = true;
        psRW_SN->m_sData.m_psExecute[iIndex] = &sExecute;
        ++psRW_SN->m_sData.m_nuiThread;

        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );

        tgPM_MT_SM_Wait_Block( &sExecute );
        tgPM_MT_SM_Free( &sExecute );
    };
}


/* ---- tgCM_UT_LF__RW_SN__Enter_Read_Yield -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__RW_SN__Enter_Read_Yield( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__SN__Lock_Yield( &psRW_SN->m_sLock.m_sLock );

    if (ETgUTM_RW_STATE__Writing != psRW_SN->m_sData.m_enState)
    {
        psRW_SN->m_sData.m_enState = ETgUTM_RW_STATE__Reading;
        ++psRW_SN->m_sData.m_nuiReader;
        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
        return (KTgS_OK);
    }
    else
    {
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
        return (KTgE_FAIL);
    };
}


/* ---- tgCM_UT_LF__RW_SN__Enter_Read_Spin --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__RW_SN__Enter_Read_Spin( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__SN__Lock_Spin( &psRW_SN->m_sLock.m_sLock );

    if (ETgUTM_RW_STATE__Writing != psRW_SN->m_sData.m_enState)
    {
        psRW_SN->m_sData.m_enState = ETgUTM_RW_STATE__Reading;
        ++psRW_SN->m_sData.m_nuiReader;
        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
        return (KTgS_OK);
    }
    else
    {
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
        return (KTgE_FAIL);
    };
}


/* ---- tgCM_UT_LF__RW_SN__Exit_Read_Yield --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW_SN__Exit_Read_Yield( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__SN__Lock_Yield( &psRW_SN->m_sLock.m_sLock );
    TgERROR(psRW_SN->m_sData.m_enState == ETgUTM_RW_STATE__Reading);
    TgERROR(psRW_SN->m_sData.m_nuiReader > 0);

    --psRW_SN->m_sData.m_nuiReader;

    if (0 == psRW_SN->m_sData.m_nuiReader)
    {
        psRW_SN->m_sData.m_enState = ETgUTM_RW_STATE__Waiting;
    };

    if (psRW_SN->m_sData.m_nuiThread > 0)
    {
        tgCM_UT_MT__RW_DATA__Update( &psRW_SN->m_sData );
    };

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
    tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
}


/* ---- tgCM_UT_LF__RW_SN__Exit_Read_Spin ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW_SN__Exit_Read_Spin( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__SN__Lock_Spin( &psRW_SN->m_sLock.m_sLock );
    TgERROR(psRW_SN->m_sData.m_enState == ETgUTM_RW_STATE__Reading);
    TgERROR(psRW_SN->m_sData.m_nuiReader > 0);

    --psRW_SN->m_sData.m_nuiReader;

    if (0 == psRW_SN->m_sData.m_nuiReader)
    {
        psRW_SN->m_sData.m_enState = ETgUTM_RW_STATE__Waiting;
    };

    if (psRW_SN->m_sData.m_nuiThread > 0)
    {
        tgCM_UT_MT__RW_DATA__Update( &psRW_SN->m_sData );
    };

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
    tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
}


/* ---- tgCM_UT_LF__RW_SN__Enter_Write_Yield_Block ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW_SN__Enter_Write_Yield_Block( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__SN__Lock_Yield( &psRW_SN->m_sLock.m_sLock );

    if (ETgUTM_RW_STATE__Waiting == psRW_SN->m_sData.m_enState)
    {
        psRW_SN->m_sData.m_enState = ETgUTM_RW_STATE__Writing;
        TgERROR(psRW_SN->m_sData.m_nuiReader == 0);
        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
    }
    else
    {
        STg1_MT_SM                          sExecute;
        TgUINT_E32                          iIndex;

        TgERROR(psRW_SN->m_sData.m_nuiThread < KTgMP_MAX_READ_WRITER_LOCK);

        TgVERIFY(KTgS_OK == tgPM_MT_SM_Init( &sExecute, nullptr, 0, 1 ));

        iIndex = (psRW_SN->m_sData.m_uiIndex + psRW_SN->m_sData.m_nuiThread) % KTgMP_MAX_READ_WRITER_LOCK;
        psRW_SN->m_sData.m_asThread[iIndex] = tgTR_Query_Id();
        psRW_SN->m_sData.m_abReader[iIndex] = false;
        psRW_SN->m_sData.m_psExecute[iIndex] = &sExecute;
        ++psRW_SN->m_sData.m_nuiThread;

        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );

        tgPM_MT_SM_Wait_Block( &sExecute );
        tgPM_MT_SM_Free( &sExecute );
    };
}


/* ---- tgCM_UT_LF__RW_SN__Enter_Write_Spin_Block -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW_SN__Enter_Write_Spin_Block( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__SN__Lock_Spin( &psRW_SN->m_sLock.m_sLock );

    if (ETgUTM_RW_STATE__Waiting == psRW_SN->m_sData.m_enState)
    {
        psRW_SN->m_sData.m_enState = ETgUTM_RW_STATE__Writing;
        TgERROR(psRW_SN->m_sData.m_nuiReader == 0);
        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
    }
    else
    {
        STg1_MT_SM                          sExecute;
        TgUINT_E32                          iIndex;

        TgERROR(psRW_SN->m_sData.m_nuiThread < KTgMP_MAX_READ_WRITER_LOCK);

        TgVERIFY(KTgS_OK == tgPM_MT_SM_Init( &sExecute, nullptr, 0, 1 ));

        iIndex = (psRW_SN->m_sData.m_uiIndex + psRW_SN->m_sData.m_nuiThread) % KTgMP_MAX_READ_WRITER_LOCK;
        psRW_SN->m_sData.m_asThread[iIndex] = tgTR_Query_Id();
        psRW_SN->m_sData.m_abReader[iIndex] = false;
        psRW_SN->m_sData.m_psExecute[iIndex] = &sExecute;
        ++psRW_SN->m_sData.m_nuiThread;

        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );

        tgPM_MT_SM_Wait_Block( &sExecute );
        tgPM_MT_SM_Free( &sExecute );
    };
}


/* ---- tgCM_UT_LF__RW_SN__Enter_Write_Yield ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__RW_SN__Enter_Write_Yield( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__SN__Lock_Yield( &psRW_SN->m_sLock.m_sLock );

    if (ETgUTM_RW_STATE__Waiting == psRW_SN->m_sData.m_enState)
    {
        psRW_SN->m_sData.m_enState = ETgUTM_RW_STATE__Writing;
        TgERROR(psRW_SN->m_sData.m_nuiReader == 0);
        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
        return (KTgS_OK);
    }
    else
    {
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
        return (KTgE_FAIL);
    };
}


/* ---- tgCM_UT_LF__RW_SN__Enter_Write_Spin -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__RW_SN__Enter_Write_Spin( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__SN__Lock_Spin( &psRW_SN->m_sLock.m_sLock );

    if (ETgUTM_RW_STATE__Waiting == psRW_SN->m_sData.m_enState)
    {
        psRW_SN->m_sData.m_enState = ETgUTM_RW_STATE__Writing;
        TgERROR(psRW_SN->m_sData.m_nuiReader == 0);
        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
        return (KTgS_OK);
    }
    else
    {
        tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
        return (KTgE_FAIL);
    };
}


/* ---- tgCM_UT_LF__RW_SN__Exit_Write_Yield -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW_SN__Exit_Write_Yield( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__SN__Lock_Yield( &psRW_SN->m_sLock.m_sLock );
    TgERROR(psRW_SN->m_sData.m_enState == ETgUTM_RW_STATE__Writing);

    psRW_SN->m_sData.m_enState = ETgUTM_RW_STATE__Waiting;
    if (psRW_SN->m_sData.m_nuiThread > 0)
    {
        tgCM_UT_MT__RW_DATA__Update( &psRW_SN->m_sData );
    };

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
    tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
}


/* ---- tgCM_UT_LF__RW_SN__Exit_Write_Spin --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__RW_SN__Exit_Write_Spin( STg2_UT_LF_ISO__RW_SN_PCU psRW_SN )
{
    tgCM_UT_LF__SN__Lock_Spin( &psRW_SN->m_sLock.m_sLock );
    TgERROR(psRW_SN->m_sData.m_enState == ETgUTM_RW_STATE__Writing);

    psRW_SN->m_sData.m_enState = ETgUTM_RW_STATE__Waiting;
    if (psRW_SN->m_sData.m_nuiThread > 0)
    {
        tgCM_UT_MT__RW_DATA__Update( &psRW_SN->m_sData );
    };

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
    tgCM_UT_LF__SN__Signal( &psRW_SN->m_sLock.m_sLock );
}

/*# TgCOMPILE__THREAD */
#endif


/* ---- FIFO Queuing Reader Writer Lock ------------------------------------------------------------------------------------------------------------------------------------------ */

#if TgCOMPILE__THREAD

/* ---- tgCM_UT_MT__RW_MX__Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_MT__RW_MX__Init( STg2_UT_MT__RW_MX_PCU psRW_MX )
{
    TgVERIFY( KTgS_OK == tgPM_MT_MX_Init( &psRW_MX->m_sLock, nullptr ) );
    tgCM_UT_MT__RW_DATA__Init( &psRW_MX->m_sData );
    return (KTgS_OK);
}


/* ---- tgCM_UT_MT__RW_MX__Free -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_MT__RW_MX__Free( STg2_UT_MT__RW_MX_PCU psRW_MX )
{
    tgCM_UT_MT__RW_DATA__Free( &psRW_MX->m_sData );
    tgPM_MT_MX_Free( &psRW_MX->m_sLock );
}


/* ---- tgCM_UT_MT__RW_MX__Enter_Read_Block -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_MT__RW_MX__Enter_Read_Block( STg2_UT_MT__RW_MX_PCU psRW_MX )
{
    tgPM_MT_MX_Wait_Block( &psRW_MX->m_sLock );

    if (ETgUTM_RW_STATE__Writing != psRW_MX->m_sData.m_enState)
    {
        psRW_MX->m_sData.m_enState = ETgUTM_RW_STATE__Reading;
        ++psRW_MX->m_sData.m_nuiReader;
        tgPM_MT_MX_Release( &psRW_MX->m_sLock );
    }
    else
    {
        STg1_MT_SM                          sExecute;
        TgUINT_E32                          iIndex;

        TgERROR(psRW_MX->m_sData.m_nuiThread < KTgMP_MAX_READ_WRITER_LOCK);

        TgVERIFY(KTgS_OK == tgPM_MT_SM_Init( &sExecute, nullptr, 0, 1 ));

        iIndex = (psRW_MX->m_sData.m_uiIndex + psRW_MX->m_sData.m_nuiThread) % KTgMP_MAX_READ_WRITER_LOCK;
        psRW_MX->m_sData.m_asThread[iIndex] = tgTR_Query_Id();
        psRW_MX->m_sData.m_abReader[iIndex] = true;
        psRW_MX->m_sData.m_psExecute[iIndex] = &sExecute;
        ++psRW_MX->m_sData.m_nuiThread;

        tgPM_MT_MX_Release( &psRW_MX->m_sLock );

        tgPM_MT_SM_Wait_Block( &sExecute );
        tgPM_MT_SM_Free( &sExecute );
    };
}


/* ---- tgCM_UT_MT__RW_MX__Enter_Read -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_MT__RW_MX__Enter_Read( STg2_UT_MT__RW_MX_PCU psRW_MX )
{
    tgPM_MT_MX_Wait_Block( &psRW_MX->m_sLock );

    if (ETgUTM_RW_STATE__Writing != psRW_MX->m_sData.m_enState)
    {
        psRW_MX->m_sData.m_enState = ETgUTM_RW_STATE__Reading;
        ++psRW_MX->m_sData.m_nuiReader;
        tgPM_MT_MX_Release( &psRW_MX->m_sLock );
        return (KTgS_OK);
    }
    else
    {
        tgPM_MT_MX_Release( &psRW_MX->m_sLock );
        return (KTgE_FAIL);
    };
}


/* ---- tgCM_UT_MT__RW_MX__Exit_Read --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_MT__RW_MX__Exit_Read( STg2_UT_MT__RW_MX_PCU psRW_MX )
{
    tgPM_MT_MX_Wait_Block( &psRW_MX->m_sLock );
    TgERROR(psRW_MX->m_sData.m_enState == ETgUTM_RW_STATE__Reading);
    TgERROR(psRW_MX->m_sData.m_nuiReader > 0);

    --psRW_MX->m_sData.m_nuiReader;

    if (0 == psRW_MX->m_sData.m_nuiReader)
    {
        psRW_MX->m_sData.m_enState = ETgUTM_RW_STATE__Waiting;
    };

    if (psRW_MX->m_sData.m_nuiThread > 0)
    {
        tgCM_UT_MT__RW_DATA__Update( &psRW_MX->m_sData );
    };

    tgPM_MT_MX_Release( &psRW_MX->m_sLock );
}


/* ---- tgCM_UT_MT__RW_MX__Enter_Write_Block ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_MT__RW_MX__Enter_Write_Block( STg2_UT_MT__RW_MX_PCU psRW_MX )
{
    tgPM_MT_MX_Wait_Block( &psRW_MX->m_sLock );

    if (ETgUTM_RW_STATE__Waiting == psRW_MX->m_sData.m_enState)
    {
        psRW_MX->m_sData.m_enState = ETgUTM_RW_STATE__Writing;
        TgERROR(psRW_MX->m_sData.m_nuiReader == 0);
        tgPM_MT_MX_Release( &psRW_MX->m_sLock );
    }
    else
    {
        STg1_MT_SM                          sExecute;
        TgUINT_E32                          iIndex;

        TgERROR(psRW_MX->m_sData.m_nuiThread < KTgMP_MAX_READ_WRITER_LOCK);

        TgVERIFY(KTgS_OK == tgPM_MT_SM_Init( &sExecute, nullptr, 0, 1 ));

        iIndex = (psRW_MX->m_sData.m_uiIndex + psRW_MX->m_sData.m_nuiThread) % KTgMP_MAX_READ_WRITER_LOCK;
        psRW_MX->m_sData.m_asThread[iIndex] = tgTR_Query_Id();
        psRW_MX->m_sData.m_abReader[iIndex] = false;
        psRW_MX->m_sData.m_psExecute[iIndex] = &sExecute;
        ++psRW_MX->m_sData.m_nuiThread;

        tgPM_MT_MX_Release( &psRW_MX->m_sLock );

        tgPM_MT_SM_Wait_Block( &sExecute );
        tgPM_MT_SM_Free( &sExecute );
    };
}


/* ---- tgCM_UT_MT__RW_MX__Enter_Write ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_MT__RW_MX__Enter_Write( STg2_UT_MT__RW_MX_PCU psRW_MX )
{
    tgPM_MT_MX_Wait_Block( &psRW_MX->m_sLock );

    if (ETgUTM_RW_STATE__Waiting == psRW_MX->m_sData.m_enState)
    {
        psRW_MX->m_sData.m_enState = ETgUTM_RW_STATE__Writing;
        TgERROR(psRW_MX->m_sData.m_nuiReader == 0);
        tgPM_MT_MX_Release( &psRW_MX->m_sLock );
        return (KTgS_OK);
    }
    else
    {
        tgPM_MT_MX_Release( &psRW_MX->m_sLock );
        return (KTgE_FAIL);
    };
}


/* ---- tgCM_UT_MT__RW_MX__Exit_Write -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_MT__RW_MX__Exit_Write( STg2_UT_MT__RW_MX_PCU psRW_MX )
{
    tgPM_MT_MX_Wait_Block( &psRW_MX->m_sLock );
    TgERROR(psRW_MX->m_sData.m_enState == ETgUTM_RW_STATE__Writing);

    psRW_MX->m_sData.m_enState = ETgUTM_RW_STATE__Waiting;
    if (psRW_MX->m_sData.m_nuiThread > 0)
    {
        tgCM_UT_MT__RW_DATA__Update( &psRW_MX->m_sData );
    };

    tgPM_MT_MX_Release( &psRW_MX->m_sLock );
}

/*# TgCOMPILE__THREAD */
#endif

/* =============================================================================================================================================================================== */
#endif
