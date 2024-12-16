/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Spin Lock.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_MT_SPIN_LOCK_INL)
#define TGS_COMMON_UTIL_MT_SPIN_LOCK_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_UT_LF__SN__Init ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN__Init( STg2_UT_LF__SN_PCU psMP_SN )
{
    TgSTD_ATOMIC(store)( &psMP_SN->m_uiSRV_REQ, 0 );
    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN__Free_Unsafe ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN__Free_Unsafe( TgATTRIBUTE_UNUSED_PARAM_CHECK STg2_UT_LF__SN_PCU psMP_SN )
{
#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK
    STg2_UT_ST__SRV_REQ                 sSRV_REQ;

    sSRV_REQ.m_uiSRV_REQ = TgSTD_ATOMIC(load)( &psMP_SN->m_uiSRV_REQ );
    TgERROR(sSRV_REQ.m_nuiServed == sSRV_REQ.m_uiRequest);
/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK */
#endif
}


/* ---- tgCM_UT_LF__SN__Lock_Yield ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN__Lock_Yield( STg2_UT_LF__SN_PCU psMP_SN )
{
    STg2_UT_ST__SRV_REQ                 sOrig, sNew, sCurrent;

    sOrig.m_uiSRV_REQ = TgSTD_ATOMIC(load_explicit)( &psMP_SN->m_uiSRV_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {   /* Avoid using TgSTD_ATOMIC(fetch_add) due to overflow during addition */
        sNew.m_nuiServed = sOrig.m_nuiServed;
        sNew.m_uiRequest = sOrig.m_uiRequest + 1;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN->m_uiSRV_REQ, &sOrig.m_uiSRV_REQ, sNew.m_uiSRV_REQ ));

    sCurrent.m_nuiServed = sNew.m_nuiServed;

    while (sCurrent.m_nuiServed != sOrig.m_uiRequest)
    {
        tgTR_Yield();
        sCurrent.m_uiSRV_REQ = TgSTD_ATOMIC(load)( &psMP_SN->m_uiSRV_REQ );
    };

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
}


/* ---- tgCM_UT_LF__SN__Lock_Spin ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN__Lock_Spin( STg2_UT_LF__SN_PCU psMP_SN )
{
    STg2_UT_ST__SRV_REQ                 sOrig, sNew, sCurrent;

    sOrig.m_uiSRV_REQ = TgSTD_ATOMIC(load_explicit)( &psMP_SN->m_uiSRV_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {   /* Avoid using TgSTD_ATOMIC(fetch_add) due to overflow during addition */
        sNew.m_nuiServed = sOrig.m_nuiServed;
        sNew.m_uiRequest = sOrig.m_uiRequest + 1;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN->m_uiSRV_REQ, &sOrig.m_uiSRV_REQ, sNew.m_uiSRV_REQ ));

    sCurrent.m_nuiServed = sNew.m_nuiServed;

    while (sCurrent.m_nuiServed != sOrig.m_uiRequest)
    {
        tgTR_Pause();
        sCurrent.m_uiSRV_REQ = TgSTD_ATOMIC(load)( &psMP_SN->m_uiSRV_REQ );
    };

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
}


/* ---- tgCM_UT_LF__SN__Lock_Test ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN__Lock_Test( STg2_UT_LF__SN_PCU psMP_SN )
{
    STg2_UT_ST__SRV_REQ                 sOrig, sTest, sNew;

    sOrig.m_uiSRV_REQ = TgSTD_ATOMIC(load)( &psMP_SN->m_uiSRV_REQ );

    sTest.m_nuiServed = sOrig.m_uiRequest;
    sTest.m_uiRequest = sOrig.m_uiRequest;
    sNew.m_nuiServed = sOrig.m_uiRequest;
    sNew.m_uiRequest = sOrig.m_uiRequest + 1;

    if (TgSTD_ATOMIC(compare_exchange_strong)( &psMP_SN->m_uiSRV_REQ, &sTest.m_uiSRV_REQ, sNew.m_uiSRV_REQ ))
    {
        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        return (KTgS_OK);
    }
    return (KTgE_FAIL);
}


/* ---- tgCM_UT_LF__SN__Signal --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN__Signal( STg2_UT_LF__SN_PCU psMP_SN )
{
    STg2_UT_ST__SRV_REQ                 sOrig, sNew;

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );

    sOrig.m_uiSRV_REQ = TgSTD_ATOMIC(load_explicit)( &psMP_SN->m_uiSRV_REQ, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {   /* Avoid using TgSTD_ATOMIC(fetch_add) due to overflow during addition */
        sNew.m_nuiServed = sOrig.m_nuiServed + 1;
        sNew.m_uiRequest = sOrig.m_uiRequest;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN->m_uiSRV_REQ, &sOrig.m_uiSRV_REQ, sNew.m_uiSRV_REQ ));

    TgERROR( sNew.m_nuiServed <= sNew.m_uiRequest );
}




/* ---- tgCM_UT_LF__SN_CNT__Init ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_CNT__Init( STg2_UT_LF__SN_CNT_PCU psMP_SN_CNT )
{
    TgSTD_ATOMIC(store)( &psMP_SN_CNT->m_uiSRV_REQ_CNT, 0 );
    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN_CNT__Free_Unsafe ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN_CNT__Free_Unsafe( TgATTRIBUTE_UNUSED_PARAM_CHECK STg2_UT_LF__SN_CNT_PCU psMP_SN_CNT )
{
#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK
    STg2_UT_ST__SRV_REQ_CNT             sSRV_REQ_CNT;

    sSRV_REQ_CNT.m_uiSRV_REQ_CNT = TgSTD_ATOMIC(load)( &psMP_SN_CNT->m_uiSRV_REQ_CNT );
    TgERROR(sSRV_REQ_CNT.m_nuiServed == sSRV_REQ_CNT.m_uiRequest);
/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK */
#endif
}


/* ---- tgCM_UT_LF__SN_CNT__Lock_Or_Increment_Count ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_CNT__Lock_Or_Increment_Count( STg2_UT_LF__SN_CNT_PCU psMP_SN_CNT )
{
    STg2_UT_ST__SRV_REQ_CNT             sOrig, sNew;

    sOrig.m_uiSRV_REQ_CNT = TgSTD_ATOMIC(load_explicit)( &psMP_SN_CNT->m_uiSRV_REQ_CNT, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        if (0 != sOrig.m_nuiTested || (sOrig.m_uiRequest != sOrig.m_nuiServed))
        {
            sNew.m_nuiServed = sOrig.m_nuiServed;
            sNew.m_uiRequest = sOrig.m_uiRequest;
            sNew.m_nuiTested = sOrig.m_nuiTested + 1u;
        }
        else
        {
            sNew.m_nuiServed = sOrig.m_uiRequest;
            sNew.m_uiRequest = sOrig.m_uiRequest + 1u;
            sNew.m_nuiTested = 0;
        };
    }
    while (!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN_CNT->m_uiSRV_REQ_CNT, &sOrig.m_uiSRV_REQ_CNT, sNew.m_uiSRV_REQ_CNT ));

    if (0 == sNew.m_nuiTested)
    {
        return (KTgS_OK);
    }
    else
    {
        return (KTgE_FAIL);
    }
}


/* ---- tgCM_UT_LF__SN_CNT__Signal_Or_Reset_Count -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgUINT_E32 tgCM_UT_LF__SN_CNT__Signal_Or_Reset_Count( STg2_UT_LF__SN_CNT_PCU psMP_SN_CNT )
{
    STg2_UT_ST__SRV_REQ_CNT             sOrig, sNew;
    TgUINT_E32                          nuiTested;

    sOrig.m_uiSRV_REQ_CNT = TgSTD_ATOMIC(load_explicit)( &psMP_SN_CNT->m_uiSRV_REQ_CNT, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        sNew.m_nuiServed = sOrig.m_nuiServed + (0 == sOrig.m_nuiTested ? 1u : 0);
        sNew.m_uiRequest = sOrig.m_uiRequest;
        sNew.m_nuiTested = 0;

        nuiTested = sOrig.m_nuiTested;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN_CNT->m_uiSRV_REQ_CNT, &sOrig.m_uiSRV_REQ_CNT, sNew.m_uiSRV_REQ_CNT ));

    return (nuiTested);
}




/* ---- tgCM_UT_LF__SN_ID__Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_ID__Init( STg2_UT_LF__SN_ID_PCU psMP_SN_ID, TgUINT_E64_C uiKI )
{
    STg2_UT_ST__SRV_REQ_ID              sSRV_REQ_ID;

    if (KTgID__INVALID_VALUE == uiKI)
    {
        return (KTgE_FAIL);
    };

    sSRV_REQ_ID.m_uiSRV_REQ = 0;
    sSRV_REQ_ID.m_uiKI = uiKI;

    TgSTD_ATOMIC(store)( &psMP_SN_ID->m_sSRV_REQ_ID, sSRV_REQ_ID );
    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN_ID__Free_Yield -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN_ID__Free_Yield( STg2_UT_LF__SN_ID_PCU psMP_SN_ID )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew, sTest;

    /* Invalidate the ID so that all future attempts to acquire the lock will fail */
    sOrig = TgSTD_ATOMIC(load_explicit)( &psMP_SN_ID->m_sSRV_REQ_ID, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        sNew.m_uiSRV_REQ = sOrig.m_uiSRV_REQ;
        sNew.m_uiKI = KTgID__INVALID_VALUE;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    /* Acquire the lock after the last existing attempt in the queue */
    sTest.m_uiRequest = sNew.m_uiRequest;
    while(1)
    {
        sTest.m_nuiServed = sTest.m_uiRequest;
        sTest.m_uiKI = KTgID__INVALID_VALUE;

        sNew.m_nuiServed = sTest.m_uiRequest;
        sNew.m_uiRequest = sTest.m_uiRequest + KTgMAX_U16;
        sNew.m_uiKI = KTgID__INVALID_VALUE;

        if (TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN_ID->m_sSRV_REQ_ID, &sTest, sNew ))
        {
            break;
        };

        tgTR_Yield();
    };

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
}

/* ---- tgCM_UT_LF__SN_ID__Free_Spin --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN_ID__Free_Spin( STg2_UT_LF__SN_ID_PCU psMP_SN_ID )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew, sTest;

    /* Invalidate the ID so that all future attempts to acquire the lock will fail */
    sOrig = TgSTD_ATOMIC(load_explicit)( &psMP_SN_ID->m_sSRV_REQ_ID, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        sNew.m_uiSRV_REQ = sOrig.m_uiSRV_REQ;
        sNew.m_uiKI = KTgID__INVALID_VALUE;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    /* Acquire the lock after the last existing attempt in the queue */
    sTest.m_uiRequest = sNew.m_uiRequest;
    while(1)
    {
        sTest.m_nuiServed = sTest.m_uiRequest;
        sTest.m_uiKI = KTgID__INVALID_VALUE;

        sNew.m_nuiServed = sTest.m_uiRequest;
        sNew.m_uiRequest = sTest.m_uiRequest + KTgMAX_U16;
        sNew.m_uiKI = KTgID__INVALID_VALUE;

        if (TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN_ID->m_sSRV_REQ_ID, &sTest, sNew ))
        {
            break;
        };

        tgTR_Pause();
    };

    sTest = sNew;
    sNew.m_uiSRV_REQ = 0;
    while (!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN_ID->m_sSRV_REQ_ID, &sTest, sNew ));

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
}


/* ---- tgCM_UT_LF__SN_ID__Free_Unsafe ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN_ID__Free_Unsafe( STg2_UT_LF__SN_ID_PCU psMP_SN_ID )
{
    STg2_UT_ST__SRV_REQ_ID              sSRV_REQ_ID;
    
#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK
    sSRV_REQ_ID = TgSTD_ATOMIC(load)( &psMP_SN_ID->m_sSRV_REQ_ID );
    TgERROR(sSRV_REQ_ID.m_nuiServed == sSRV_REQ_ID.m_uiRequest);

/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__PARAM_CHECK */
#endif

    sSRV_REQ_ID.m_uiSRV_REQ = 0;
    sSRV_REQ_ID.m_uiKI = KTgID__INVALID_VALUE;

    TgSTD_ATOMIC(store)( &psMP_SN_ID->m_sSRV_REQ_ID, sSRV_REQ_ID );
}


/* ---- tgCM_UT_LF__SN_ID__Lock_Yield -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_ID__Lock_Yield( STg2_UT_LF__SN_ID_PCU psMP_SN_ID, TgUINT_E64_C uiKI )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew, sCurrent;

    sOrig = TgSTD_ATOMIC(load_explicit)( &psMP_SN_ID->m_sSRV_REQ_ID, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {   /* Avoid using TgSTD_ATOMIC(fetch_add) due to overflow during addition */
        TgERROR(sOrig.m_uiSRV_REQ != 0 || sOrig.m_uiKI != KTgID__INVALID_VALUE);
        if (uiKI != sOrig.m_uiKI)
        {
            return (KTgE_SN_INVALID_ID);
        };
        sNew.m_nuiServed = sOrig.m_nuiServed;
        sNew.m_uiRequest = sOrig.m_uiRequest + 1;
        sNew.m_uiKI = sOrig.m_uiKI;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    TgERROR( sNew.m_nuiServed < sNew.m_uiRequest );
    sCurrent = sNew;

    while (sCurrent.m_nuiServed != sOrig.m_uiRequest)
    {
        tgTR_Yield();
        sCurrent = TgSTD_ATOMIC(load)( &psMP_SN_ID->m_sSRV_REQ_ID );
        TgERROR(sCurrent.m_uiSRV_REQ != 0 || sCurrent.m_uiKI != KTgID__INVALID_VALUE);
    };

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
    TgERROR( uiKI == sOrig.m_uiKI );

    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN_ID__Lock_Spin --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_ID__Lock_Spin( STg2_UT_LF__SN_ID_PCU psMP_SN_ID, TgUINT_E64_C uiKI )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew, sCurrent;

    sOrig = TgSTD_ATOMIC(load_explicit)( &psMP_SN_ID->m_sSRV_REQ_ID, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {   /* Avoid using TgSTD_ATOMIC(fetch_add) due to overflow during addition */
        TgERROR(sOrig.m_uiSRV_REQ != 0 || sOrig.m_uiKI != KTgID__INVALID_VALUE);
        if (uiKI != sOrig.m_uiKI)
        {
            return (KTgE_SN_INVALID_ID);
        };
        sNew.m_nuiServed = sOrig.m_nuiServed;
        sNew.m_uiRequest = sOrig.m_uiRequest + 1;
        sNew.m_uiKI = sOrig.m_uiKI;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    TgERROR( sNew.m_nuiServed < sNew.m_uiRequest );
    sCurrent = sNew;

    while (sCurrent.m_nuiServed != sOrig.m_uiRequest)
    {
        tgTR_Pause();
        sCurrent = TgSTD_ATOMIC(load)( &psMP_SN_ID->m_sSRV_REQ_ID );
    };

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
    TgERROR( uiKI == sOrig.m_uiKI );

    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN_ID__Lock_Test --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_ID__Lock_Test( STg2_UT_LF__SN_ID_PCU psMP_SN_ID, TgUINT_E64_C uiKI )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew, sTest;

    sOrig = TgSTD_ATOMIC(load)( &psMP_SN_ID->m_sSRV_REQ_ID );
    TgERROR(sOrig.m_uiSRV_REQ != 0 || sOrig.m_uiKI != KTgID__INVALID_VALUE);

    if (uiKI != sOrig.m_uiKI)
    {
        return (KTgE_SN_INVALID_ID);
    };

    sTest.m_nuiServed = sOrig.m_uiRequest;
    sTest.m_uiRequest = sOrig.m_uiRequest;
    sTest.m_uiKI = sOrig.m_uiKI;

    sNew.m_nuiServed = sOrig.m_uiRequest;
    sNew.m_uiRequest = sOrig.m_uiRequest + 1;
    sNew.m_uiKI = sOrig.m_uiKI;

    if (TgSTD_ATOMIC(compare_exchange_strong)( &psMP_SN_ID->m_sSRV_REQ_ID, &sTest, sNew ))
    {
        TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );
        TgERROR( sNew.m_nuiServed < sNew.m_uiRequest );
        TgERROR( uiKI == sOrig.m_uiKI );
        return (KTgS_OK);
    };

    return (KTgE_FAIL);
}


/* ---- tgCM_UT_LF__SN_ID__Invalidate_Index_Yield -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_ID__Invalidate_Index_Yield( STg2_UT_LF__SN_ID_PCU psMP_SN_ID, TgUINT_E64_C uiKI )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew;
    TgRESULT                            iResult;

    if (TgFAILED(iResult = tgCM_UT_LF__SN_ID__Lock_Yield( psMP_SN_ID, uiKI )))
    {
        return (iResult);
    };

    sOrig = TgSTD_ATOMIC(load_explicit)( &psMP_SN_ID->m_sSRV_REQ_ID, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        sNew.m_uiSRV_REQ = sOrig.m_uiSRV_REQ;
        sNew.m_uiI = KTgMAX_U32;
        sNew.m_uiK = sOrig.m_uiK;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    tgCM_UT_LF__SN_ID__Signal( psMP_SN_ID );

    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN_ID__Invalidate_Index_Spin --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_ID__Invalidate_Index_Spin( STg2_UT_LF__SN_ID_PCU psMP_SN_ID, TgUINT_E64_C uiKI )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew;
    TgRESULT                            iResult;

    if (TgFAILED(iResult = tgCM_UT_LF__SN_ID__Lock_Spin( psMP_SN_ID, uiKI )))
    {
        return (iResult);
    };

    sOrig = TgSTD_ATOMIC(load_explicit)( &psMP_SN_ID->m_sSRV_REQ_ID, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        sNew.m_uiSRV_REQ = sOrig.m_uiSRV_REQ;
        sNew.m_uiI = KTgMAX_U32;
        sNew.m_uiK = sOrig.m_uiK;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    tgCM_UT_LF__SN_ID__Signal( psMP_SN_ID );

    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN_ID__Signal ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN_ID__Signal( STg2_UT_LF__SN_ID_PCU psMP_SN_ID )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew;

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );

    sOrig = TgSTD_ATOMIC(load_explicit)( &psMP_SN_ID->m_sSRV_REQ_ID, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {   /* Avoid using TgSTD_ATOMIC(fetch_add) due to overflow during addition */
        sNew.m_nuiServed = sOrig.m_nuiServed + 1;
        sNew.m_uiRequest = sOrig.m_uiRequest;
        sNew.m_uiKI = sOrig.m_uiKI;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    TgERROR( sNew.m_nuiServed <= sNew.m_uiRequest );
}


/* =============================================================================================================================================================================== */
#endif
