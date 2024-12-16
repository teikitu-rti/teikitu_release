/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Profile Sample.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_MT_PROFILE_SAMPLE_INL)
#define TGS_COMMON_UTIL_MT_PROFILE_SAMPLE_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgProfile_Sample_Reset --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgProfile_Sample_Reset( STg2_Profile_Record_PCU NONULL psMonitor )
{
    atomic_store( &psMonitor->m_iRecord_DepthAndStart, 0 );
    atomic_store( &psMonitor->m_iRecord_Idle_Total, 0 );
    atomic_store( &psMonitor->m_iRecord_Sample_Total, 0 );

    psMonitor->m_fReport_Sample = 0.0F;
    psMonitor->m_fReport_Idle = 0.0F;
    psMonitor->m_fReport_Total = 0.0F;
}


/* ---- tgProfile_Sample_Start --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgSINT_F64 tgProfile_Sample_Start( STg2_Profile_Record_PCU NONULL psMonitor )
{
    TgSINT_F64                          iDepthAndStart, iNewDepthAndStart;
    TgSINT_F64                          iDepth;
    TgSINT_F64                          iSampleTick;
    TgSINT_F64                          iCurrent;

    iDepthAndStart = atomic_load( &psMonitor->m_iRecord_DepthAndStart );
    do
    {
        iCurrent = tgTM_Query_Counter_Tick();
        iDepth = (iDepthAndStart >> 48) & KTgMAX_U16;
        TgPARAM_CHECK( iDepth < KTgMAX_U16 ); /* Max 16 bits of start depth */
        TgPARAM_CHECK( iCurrent < ((1LL << 48) - 1) ); /* Make sure that time does not overflow */
        iNewDepthAndStart = ((iDepth + 1) << 48) + iCurrent;
    }
    while (!atomic_compare_exchange_weak( &psMonitor->m_iRecord_DepthAndStart, &iDepthAndStart, iNewDepthAndStart ));

    atomic_thread_fence( cxx__memory_order_seq_cst );

    /* Not guaranteed to execute in the same frame as above but pragmatically safe for profiling */
    if (iDepth <= 0)
    {
        iSampleTick = (TgSINT_F64 )(iCurrent - (iDepthAndStart & ((1LL << 48) - 1)));
        atomic_fetch_add( &psMonitor->m_iRecord_Idle_Total, iSampleTick );
    }
    else
    {
        iSampleTick = (TgSINT_F64 )(iDepth * (iCurrent - (iDepthAndStart & ((1LL << 48) - 1))));
        atomic_fetch_add( &psMonitor->m_iRecord_Sample_Total, iSampleTick );
    }

    return iCurrent;
}


/* ---- tgProfile_Sample_Stop ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgSINT_F64 tgProfile_Sample_Stop( STg2_Profile_Record_PCU NONULL psMonitor )
{
    TgSINT_F64                          iDepthAndStart, iNewDepthAndStart;
    TgSINT_F64                          iDepth;
    TgSINT_F64                          iSampleTick;
    TgSINT_F64                          iCurrent;

    iDepthAndStart = atomic_load( &psMonitor->m_iRecord_DepthAndStart );
    do
    {
        iCurrent = tgTM_Query_Counter_Tick();
        iDepth = (iDepthAndStart >> 48) & KTgMAX_U16;
        TgPARAM_CHECK( iDepth > 0 ); /* Max 16 bits of start depth */
        TgPARAM_CHECK( iCurrent < ((1LL << 48) - 1) ); /* Make sure that time does not overflow */
        iNewDepthAndStart = ((iDepth - 1) << 48) + iCurrent;
    }
    while (!atomic_compare_exchange_weak( &psMonitor->m_iRecord_DepthAndStart, &iDepthAndStart, iNewDepthAndStart ));

    atomic_thread_fence( cxx__memory_order_seq_cst );

    /* Not guaranteed to execute in the same frame as above but pragmatically safe for profiling */
    iSampleTick = (TgSINT_F64 )(iDepth * (iCurrent - (iDepthAndStart & ((1LL << 48) - 1))));
    atomic_fetch_add( &psMonitor->m_iRecord_Sample_Total, iSampleTick );

    return iCurrent;
}


/* ---- tgProfile_Sample_Report -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgProfile_Sample_Report( STg2_Profile_Record_PCU NONULL psMonitor )
{
    TgSINT_F64                          iDepthAndStart, iNewDepthAndStart;
    TgSINT_F64                          iDepth;
    TgSINT_F64                          iCurrent;
    TgSINT_F64                          iSampleTotal;
    TgSINT_F64                          iIdleTotal;

    iSampleTotal = 0;
    iIdleTotal = 0;

    iDepthAndStart = atomic_load( &psMonitor->m_iRecord_DepthAndStart );
    do
    {
        iCurrent = tgTM_Query_Counter_Tick();
        iDepth = (iDepthAndStart >> 48) & KTgMAX_U16;
        TgPARAM_CHECK( iCurrent < ((1LL << 48) - 1) ); /* Make sure that time does not overflow */
        iNewDepthAndStart = (iDepth << 48) + iCurrent;
        iSampleTotal += atomic_exchange( &psMonitor->m_iRecord_Sample_Total, 0 );
        iIdleTotal += atomic_exchange( &psMonitor->m_iRecord_Idle_Total, 0 );
    }
    while (!atomic_compare_exchange_weak( &psMonitor->m_iRecord_DepthAndStart, &iDepthAndStart, iNewDepthAndStart ));

    atomic_thread_fence( cxx__memory_order_seq_cst );

    /* Not guaranteed to execute in the same frame as above but pragmatically safe for profiling */
    if (iDepth <= 0)
    {
        iIdleTotal += iCurrent - (iDepthAndStart & ((1LL << 48) - 1));
    }
    else
    {
        iSampleTotal += iDepth * (iCurrent - (iDepthAndStart & ((1LL << 48) - 1)));
    }

    psMonitor->m_fReport_Sample = tgTM_Counter_Tick_To_MilliSeconds( iSampleTotal );
    psMonitor->m_fReport_Idle = tgTM_Counter_Tick_To_MilliSeconds( iIdleTotal );
    psMonitor->m_fReport_Total = tgTM_Counter_Tick_To_MilliSeconds( iSampleTotal + iIdleTotal );
}


/* =============================================================================================================================================================================== */
#endif
