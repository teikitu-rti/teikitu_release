/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Spin Lock.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
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
TgINLINE TgRESULT tgCM_UT_LF__SN__Init( STg2_UT_LF__SN_PCU NONULL psMP_SN )
{
    atomic_store( &psMP_SN->m_uiSRV_REQ, 0 );
    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN__Free_Unsafe ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN__Free_Unsafe( STg2_UT_LF__SN_PCU NONULL psMP_SN )
{
#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__VERIFY
    STg2_UT_ST__SRV_REQ                 sSRV_REQ;

    sSRV_REQ.m_uiSRV_REQ = atomic_load( &psMP_SN->m_uiSRV_REQ );
    TgERROR(sSRV_REQ.m_nuiServed == sSRV_REQ.m_uiRequest);
/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__VERIFY */
#endif
}


/* ---- tgCM_UT_LF__SN__Lock_Yield ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN__Lock_Yield( STg2_UT_LF__SN_PCU NONULL psMP_SN )
{
    STg2_UT_ST__SRV_REQ                 sOrig, sNew, sCurrent;

    sOrig.m_uiSRV_REQ = atomic_load( &psMP_SN->m_uiSRV_REQ );
    do
    {   /* Avoid using atomic_fetch_add due to overflow during addition */
        sNew.m_nuiServed = sOrig.m_nuiServed;
        sNew.m_uiRequest = sOrig.m_uiRequest + 1;
    }
    while(!atomic_compare_exchange_weak( &psMP_SN->m_uiSRV_REQ, &sOrig.m_uiSRV_REQ, sNew.m_uiSRV_REQ ));

    sCurrent.m_nuiServed = sNew.m_nuiServed;

    while (sCurrent.m_nuiServed != sOrig.m_uiRequest)
    {
        tgTR_Yield();
        sCurrent.m_uiSRV_REQ = atomic_load( &psMP_SN->m_uiSRV_REQ );
    };

    atomic_thread_fence( cxx__memory_order_seq_cst );
}


/* ---- tgCM_UT_LF__SN__Lock_Spin ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN__Lock_Spin( STg2_UT_LF__SN_PCU NONULL psMP_SN )
{
    STg2_UT_ST__SRV_REQ                 sOrig, sNew, sCurrent;

    sOrig.m_uiSRV_REQ = atomic_load( &psMP_SN->m_uiSRV_REQ );
    do
    {   /* Avoid using atomic_fetch_add due to overflow during addition */
        sNew.m_nuiServed = sOrig.m_nuiServed;
        sNew.m_uiRequest = sOrig.m_uiRequest + 1;
    }
    while(!atomic_compare_exchange_weak( &psMP_SN->m_uiSRV_REQ, &sOrig.m_uiSRV_REQ, sNew.m_uiSRV_REQ ));

    sCurrent.m_nuiServed = sNew.m_nuiServed;

    while (sCurrent.m_nuiServed != sOrig.m_uiRequest)
    {
        tgTR_Pause();
        sCurrent.m_uiSRV_REQ = atomic_load( &psMP_SN->m_uiSRV_REQ );
    };

    atomic_thread_fence( cxx__memory_order_seq_cst );
}


/* ---- tgCM_UT_LF__SN__Lock_Test ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN__Lock_Test( STg2_UT_LF__SN_PCU NONULL psMP_SN )
{
    STg2_UT_ST__SRV_REQ                 sOrig, sTest, sNew;

    sOrig.m_uiSRV_REQ = atomic_load( &psMP_SN->m_uiSRV_REQ );

    sTest.m_nuiServed = sOrig.m_uiRequest;
    sTest.m_uiRequest = sOrig.m_uiRequest;
    sNew.m_nuiServed = sOrig.m_uiRequest;
    sNew.m_uiRequest = sOrig.m_uiRequest + 1;

    if (atomic_compare_exchange_strong( &psMP_SN->m_uiSRV_REQ, &sTest.m_uiSRV_REQ, sNew.m_uiSRV_REQ ))
    {
        atomic_thread_fence( cxx__memory_order_seq_cst );
        return (KTgS_OK);
    }
    return (KTgE_FAIL);
}


/* ---- tgCM_UT_LF__SN__Signal --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN__Signal( STg2_UT_LF__SN_PCU NONULL psMP_SN )
{
    STg2_UT_ST__SRV_REQ                 sOrig, sNew;

    atomic_thread_fence( cxx__memory_order_seq_cst );

    sOrig.m_uiSRV_REQ = atomic_load( &psMP_SN->m_uiSRV_REQ );
    do
    {   /* Avoid using atomic_fetch_add due to overflow during addition */
        sNew.m_nuiServed = sOrig.m_nuiServed + 1;
        sNew.m_uiRequest = sOrig.m_uiRequest;
    }
    while(!atomic_compare_exchange_weak( &psMP_SN->m_uiSRV_REQ, &sOrig.m_uiSRV_REQ, sNew.m_uiSRV_REQ ));

    TgERROR( sNew.m_nuiServed <= sNew.m_uiRequest );
}




/* ---- tgCM_UT_LF__SN_CNT__Init ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_CNT__Init( STg2_UT_LF__SN_CNT_PCU NONULL psMP_SN_CNT )
{
    atomic_store( &psMP_SN_CNT->m_uiSRV_REQ_CNT, 0 );
    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN_CNT__Free_Unsafe ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN_CNT__Free_Unsafe( STg2_UT_LF__SN_CNT_PCU NONULL psMP_SN_CNT )
{
#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__VERIFY
    STg2_UT_ST__SRV_REQ_CNT             sSRV_REQ_CNT;

    sSRV_REQ_CNT.m_uiSRV_REQ_CNT = atomic_load( &psMP_SN_CNT->m_uiSRV_REQ_CNT );
    TgERROR(sSRV_REQ_CNT.m_nuiServed == sSRV_REQ_CNT.m_uiRequest);
/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__VERIFY */
#endif
}


/* ---- tgCM_UT_LF__SN_CNT__Lock_Or_Increment_Count ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_CNT__Lock_Or_Increment_Count( STg2_UT_LF__SN_CNT_PCU NONULL psMP_SN_CNT )
{
    STg2_UT_ST__SRV_REQ_CNT             sOrig, sNew;

    sOrig.m_uiSRV_REQ_CNT = atomic_load( &psMP_SN_CNT->m_uiSRV_REQ_CNT );
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
    while (!atomic_compare_exchange_weak( &psMP_SN_CNT->m_uiSRV_REQ_CNT, &sOrig.m_uiSRV_REQ_CNT, sNew.m_uiSRV_REQ_CNT ));

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
TgINLINE TgUINT_F32 tgCM_UT_LF__SN_CNT__Signal_Or_Reset_Count( STg2_UT_LF__SN_CNT_PCU NONULL psMP_SN_CNT )
{
    STg2_UT_ST__SRV_REQ_CNT             sOrig, sNew;
    TgUINT_F32                          nuiTested;

    sOrig.m_uiSRV_REQ_CNT = atomic_load( &psMP_SN_CNT->m_uiSRV_REQ_CNT );
    do
    {
        sNew.m_nuiServed = sOrig.m_nuiServed + (0 == sOrig.m_nuiTested ? 1u : 0);
        sNew.m_uiRequest = sOrig.m_uiRequest;
        sNew.m_nuiTested = 0;

        nuiTested = sOrig.m_nuiTested;
    }
    while(!atomic_compare_exchange_weak( &psMP_SN_CNT->m_uiSRV_REQ_CNT, &sOrig.m_uiSRV_REQ_CNT, sNew.m_uiSRV_REQ_CNT ));

    return (nuiTested);
}




/* ---- tgCM_UT_LF__SN_ID__Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_ID__Init( STg2_UT_LF__SN_ID_PCU NONULL psMP_SN_ID, TgUINT_E64_C uiKI )
{
    STg2_UT_ST__SRV_REQ_ID              sSRV_REQ_ID;

    if (KTgID__INVALID_VALUE == uiKI)
    {
        return (KTgE_FAIL);
    };

    sSRV_REQ_ID.m_uiSRV_REQ = 0;
    sSRV_REQ_ID.m_uiKI = uiKI;

    atomic_store( &psMP_SN_ID->m_sSRV_REQ_ID, sSRV_REQ_ID );
    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN_ID__Free_Yield -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN_ID__Free_Yield( STg2_UT_LF__SN_ID_PCU NONULL psMP_SN_ID )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew, sTest;

    /* Invalidate the ID so that all future attempts to acquire the lock will fail */
    sOrig = atomic_load( &psMP_SN_ID->m_sSRV_REQ_ID );
    do
    {
        sNew.m_uiSRV_REQ = sOrig.m_uiSRV_REQ;
        sNew.m_uiKI = KTgID__INVALID_VALUE;
    }
    while(!atomic_compare_exchange_weak( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    /* Acquire the lock after the last existing attempt in the queue */
    sTest.m_uiRequest = sNew.m_uiRequest;
    while(1)
    {
        sTest.m_nuiServed = sTest.m_uiRequest;
        sTest.m_uiKI = KTgID__INVALID_VALUE;

        sNew.m_nuiServed = sTest.m_uiRequest;
        sNew.m_uiRequest = sTest.m_uiRequest + KTgMAX_U16;
        sNew.m_uiKI = KTgID__INVALID_VALUE;

        if (atomic_compare_exchange_weak( &psMP_SN_ID->m_sSRV_REQ_ID, &sTest, sNew ))
        {
            break;
        };

        tgTR_Yield();
    };

    atomic_thread_fence( cxx__memory_order_seq_cst );
}

/* ---- tgCM_UT_LF__SN_ID__Free_Spin --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN_ID__Free_Spin( STg2_UT_LF__SN_ID_PCU NONULL psMP_SN_ID )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew, sTest;

    /* Invalidate the ID so that all future attempts to acquire the lock will fail */
    sOrig = atomic_load( &psMP_SN_ID->m_sSRV_REQ_ID );
    do
    {
        sNew.m_uiSRV_REQ = sOrig.m_uiSRV_REQ;
        sNew.m_uiKI = KTgID__INVALID_VALUE;
    }
    while(!atomic_compare_exchange_weak( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    /* Acquire the lock after the last existing attempt in the queue */
    sTest.m_uiRequest = sNew.m_uiRequest;
    while(1)
    {
        sTest.m_nuiServed = sTest.m_uiRequest;
        sTest.m_uiKI = KTgID__INVALID_VALUE;

        sNew.m_nuiServed = sTest.m_uiRequest;
        sNew.m_uiRequest = sTest.m_uiRequest + KTgMAX_U16;
        sNew.m_uiKI = KTgID__INVALID_VALUE;

        if (atomic_compare_exchange_weak( &psMP_SN_ID->m_sSRV_REQ_ID, &sTest, sNew ))
        {
            break;
        };

        tgTR_Pause();
    };

    sTest = sNew;
    sNew.m_uiSRV_REQ = 0;
    while (!atomic_compare_exchange_weak( &psMP_SN_ID->m_sSRV_REQ_ID, &sTest, sNew ));

    atomic_thread_fence( cxx__memory_order_seq_cst );
}


/* ---- tgCM_UT_LF__SN_ID__Free_Unsafe ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN_ID__Free_Unsafe( STg2_UT_LF__SN_ID_PCU NONULL psMP_SN_ID )
{
    STg2_UT_ST__SRV_REQ_ID              sSRV_REQ_ID;
    
#if TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__VERIFY
    sSRV_REQ_ID = atomic_load( &psMP_SN_ID->m_sSRV_REQ_ID );
    TgERROR(sSRV_REQ_ID.m_nuiServed == sSRV_REQ_ID.m_uiRequest);

/*# TgCOMPILE_ASSERT && TgCOMPILE_ASSERT__VERIFY */
#endif

    sSRV_REQ_ID.m_uiSRV_REQ = 0;
    sSRV_REQ_ID.m_uiKI = KTgID__INVALID_VALUE;

    atomic_store( &psMP_SN_ID->m_sSRV_REQ_ID, sSRV_REQ_ID );
}


/* ---- tgCM_UT_LF__SN_ID__Lock_Yield -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_ID__Lock_Yield( STg2_UT_LF__SN_ID_PCU NONULL psMP_SN_ID, TgUINT_F64_C uiKI )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew, sCurrent;

    sOrig = atomic_load( &psMP_SN_ID->m_sSRV_REQ_ID );
    do
    {   /* Avoid using atomic_fetch_add due to overflow during addition */
        TgERROR(sOrig.m_uiSRV_REQ != 0 || sOrig.m_uiKI != KTgID__INVALID_VALUE);
        if (uiKI != sOrig.m_uiKI)
        {
            return (KTgE_SN_INVALID_ID);
        };
        sNew.m_nuiServed = sOrig.m_nuiServed;
        sNew.m_uiRequest = sOrig.m_uiRequest + 1;
        sNew.m_uiKI = sOrig.m_uiKI;
    }
    while(!atomic_compare_exchange_weak( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    TgERROR( sNew.m_nuiServed < sNew.m_uiRequest );
    sCurrent = sNew;

    while (sCurrent.m_nuiServed != sOrig.m_uiRequest)
    {
        tgTR_Yield();
        sCurrent = atomic_load( &psMP_SN_ID->m_sSRV_REQ_ID );
        TgERROR(sCurrent.m_uiSRV_REQ != 0 || sCurrent.m_uiKI != KTgID__INVALID_VALUE);
    };

    atomic_thread_fence( cxx__memory_order_seq_cst );

    if (uiKI != sOrig.m_uiKI)
    {
        tgCM_UT_LF__SN_ID__Signal( psMP_SN_ID );
        return (KTgE_SN_INVALID_ID);
    };

    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN_ID__Lock_Spin --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_ID__Lock_Spin( STg2_UT_LF__SN_ID_PCU NONULL psMP_SN_ID, TgUINT_F64_C uiKI )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew, sCurrent;

    sOrig = atomic_load( &psMP_SN_ID->m_sSRV_REQ_ID );
    do
    {   /* Avoid using atomic_fetch_add due to overflow during addition */
        if (uiKI != sOrig.m_uiKI)
        {
            return (KTgE_SN_INVALID_ID);
        };
        sNew.m_nuiServed = sOrig.m_nuiServed;
        sNew.m_uiRequest = sOrig.m_uiRequest + 1;
        sNew.m_uiKI = sOrig.m_uiKI;
    }
    while(!atomic_compare_exchange_weak( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    TgERROR( sNew.m_nuiServed < sNew.m_uiRequest );
    sCurrent = sNew;

    while (sCurrent.m_nuiServed != sOrig.m_uiRequest)
    {
        tgTR_Pause();
        sCurrent = atomic_load( &psMP_SN_ID->m_sSRV_REQ_ID );
    };

    atomic_thread_fence( cxx__memory_order_seq_cst );

    if (uiKI != sOrig.m_uiKI)
    {
        tgCM_UT_LF__SN_ID__Signal( psMP_SN_ID );
        return (KTgE_SN_INVALID_ID);
    };

    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN_ID__Lock_Test --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_ID__Lock_Test( STg2_UT_LF__SN_ID_PCU NONULL psMP_SN_ID, TgUINT_F64_C uiKI )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew, sTest;

    sOrig = atomic_load( &psMP_SN_ID->m_sSRV_REQ_ID );

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

    if (atomic_compare_exchange_strong( &psMP_SN_ID->m_sSRV_REQ_ID, &sTest, sNew ))
    {
        atomic_thread_fence( cxx__memory_order_seq_cst );

        if (uiKI != sOrig.m_uiKI)
        {
            tgCM_UT_LF__SN_ID__Signal( psMP_SN_ID );
            return (KTgE_SN_INVALID_ID);
        };

        TgERROR( sNew.m_nuiServed < sNew.m_uiRequest );
        return (KTgS_OK);
    };

    return (KTgE_FAIL);
}


/* ---- tgCM_UT_LF__SN_ID__Invalidate_Index_Yield -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_ID__Invalidate_Index_Yield( STg2_UT_LF__SN_ID_PCU NONULL psMP_SN_ID, TgUINT_F64_C uiKI )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew;
    TgRESULT                            iResult;

    if (TgFAILED(iResult = tgCM_UT_LF__SN_ID__Lock_Yield( psMP_SN_ID, uiKI )))
    {
        return (iResult);
    };

    sOrig = atomic_load( &psMP_SN_ID->m_sSRV_REQ_ID );
    do
    {
        sNew.m_uiSRV_REQ = sOrig.m_uiSRV_REQ;
        sNew.m_uiI = KTgMAX_U32;
        sNew.m_uiK = sOrig.m_uiK;
    }
    while(!atomic_compare_exchange_weak( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    tgCM_UT_LF__SN_ID__Signal( psMP_SN_ID );

    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN_ID__Invalidate_Index_Spin --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__SN_ID__Invalidate_Index_Spin( STg2_UT_LF__SN_ID_PCU NONULL psMP_SN_ID, TgUINT_F64_C uiKI )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew;
    TgRESULT                            iResult;

    if (TgFAILED(iResult = tgCM_UT_LF__SN_ID__Lock_Spin( psMP_SN_ID, uiKI )))
    {
        return (iResult);
    };

    sOrig = atomic_load( &psMP_SN_ID->m_sSRV_REQ_ID );
    do
    {
        sNew.m_uiSRV_REQ = sOrig.m_uiSRV_REQ;
        sNew.m_uiI = KTgMAX_U32;
        sNew.m_uiK = sOrig.m_uiK;
    }
    while(!atomic_compare_exchange_weak( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    tgCM_UT_LF__SN_ID__Signal( psMP_SN_ID );

    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__SN_ID__Signal ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__SN_ID__Signal( STg2_UT_LF__SN_ID_PCU NONULL psMP_SN_ID )
{
    STg2_UT_ST__SRV_REQ_ID              sOrig, sNew;

    atomic_thread_fence( cxx__memory_order_seq_cst );

    sOrig = atomic_load( &psMP_SN_ID->m_sSRV_REQ_ID );
    do
    {   /* Avoid using atomic_fetch_add due to overflow during addition */
        sNew.m_nuiServed = sOrig.m_nuiServed + 1;
        sNew.m_uiRequest = sOrig.m_uiRequest;
        sNew.m_uiKI = sOrig.m_uiKI;
    }
    while(!atomic_compare_exchange_weak( &psMP_SN_ID->m_sSRV_REQ_ID, &sOrig, sNew ));

    TgERROR( sNew.m_nuiServed <= sNew.m_uiRequest );
}


/* =============================================================================================================================================================================== */
#endif
