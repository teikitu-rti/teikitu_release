/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Stack.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_MT_STACK_INL)
#define TGS_COMMON_UTIL_MT_STACK_INL

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Atomic Unordered Stack - Unaligned --------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- tgCM_UT_LF__ST_Unaligned__Init ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__ST_Unaligned__Init( STg2_UT_LF__ST_Unaligned_PCU psST )
{
    STg2_UT_ST__PTR_TKT_Unaligned       sPTR_TKT;

    sPTR_TKT.m_pHead = nullptr;
    sPTR_TKT.m_uiTicket = 0;

    TgSTD_ATOMIC(store)( &psST->m_sTop, sPTR_TKT );
}


/* ---- tgCM_UT_LF__ST_Unaligned__Init_PreLoad --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__ST_Unaligned__Init_PreLoad( STg2_UT_LF__ST_Unaligned_PCU psST, TgVOID_P pData, TgRSIZE_C uiStride, TgRSIZE_C nuiData )
{
    STg2_UT_ST__PTR_TKT_Unaligned       sPTR_TKT;
    TgUN_PTR                            sPTR;

    TgERROR( uiStride >= sizeof( STg2_UT_ST__ST_Node_Unaligned ));

    sPTR_TKT.m_pHead = (STg2_UT_ST__ST_Node_Unaligned_P)pData;
    sPTR_TKT.m_uiTicket = 0;

    sPTR.m_pVoid = pData;
    for (; sPTR_TKT.m_uiTicket + 1 < nuiData; ++sPTR_TKT.m_uiTicket)
    {
        *sPTR.m_puiPTR = sPTR.m_uiPTR + uiStride;
        sPTR.m_uiPTR += uiStride;
    };
    *sPTR.m_puiPTR = 0;
    
    TgSTD_ATOMIC(store)( &psST->m_sTop, sPTR_TKT );
}


/* ---- tgCM_UT_LF__ST_Unaligned__Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__ST_Unaligned__Free( TgATTRIBUTE_UNUSED STg2_UT_LF__ST_Unaligned_PCU psST )
{
}


/* ---- tgCM_UT_LF__ST_Unaligned__Push ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__ST_Unaligned__Push( STg2_UT_LF__ST_Unaligned_PCU psST, STg2_UT_ST__ST_Node_Unaligned_PCU psNode )
{
    STg2_UT_ST__PTR_TKT_Unaligned       sOrig, sNew;

    sOrig = TgSTD_ATOMIC(load_explicit)( &psST->m_sTop, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        sNew.m_pHead = psNode;
        sNew.m_uiTicket = sOrig.m_uiTicket + 1;
        psNode->m_pNext_Node = sOrig.m_pHead;
    }
    while (!TgSTD_ATOMIC(compare_exchange_weak_explicit)( &psST->m_sTop, &sOrig, sNew, TgSTD_MEMORY_ORDER(seq_cst), TgSTD_MEMORY_ORDER(relaxed) ));
}


/* ---- tgCM_UT_LF__ST_Unaligned__Pop ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__ST_Node_Unaligned_P tgCM_UT_LF__ST_Unaligned__Pop( STg2_UT_LF__ST_Unaligned_PCU psST )
{
    STg2_UT_ST__PTR_TKT_Unaligned       sOrig, sNew;

    sOrig = TgSTD_ATOMIC(load_explicit)( &psST->m_sTop, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        if (nullptr == sOrig.m_pHead)
        {
            return (nullptr);
        };
        sNew.m_pHead = (STg2_UT_ST__ST_Node_Unaligned_P)sOrig.m_pHead->m_pNext_Node;
        sNew.m_uiTicket = sOrig.m_uiTicket + 1;
    }
    while (!TgSTD_ATOMIC(compare_exchange_weak)( &psST->m_sTop, &sOrig, sNew ));
    
    return (sOrig.m_pHead);
}


/* ---- tgCM_UT_LF__ST_Unaligned__Release -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__ST_Node_Unaligned_P tgCM_UT_LF__ST_Unaligned__Release( STg2_UT_LF__ST_Unaligned_PCU psST )
{
    STg2_UT_ST__PTR_TKT_Unaligned       sOrig, sNew;

    sOrig = TgSTD_ATOMIC(load_explicit)( &psST->m_sTop, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        if (nullptr == sOrig.m_pHead)
        {
            return (nullptr);
        };
        sNew.m_pHead = nullptr;
        sNew.m_uiTicket = sOrig.m_uiTicket + 1;
    }
    while (!TgSTD_ATOMIC(compare_exchange_weak)( &psST->m_sTop, &sOrig, sNew ));
    
    return (sOrig.m_pHead);

}


/* ---- tgCM_UT_LF__ST_Unaligned__Merge ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__ST_Unaligned__Merge( STg2_UT_LF__ST_Unaligned_PCU psST, STg2_UT_ST__ST_Node_Unaligned_P psHead, STg2_UT_ST__ST_Node_Unaligned_P psTail )
{
    STg2_UT_ST__PTR_TKT_Unaligned       sOrig, sNew;

    sOrig = TgSTD_ATOMIC(load_explicit)( &psST->m_sTop, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        sNew.m_pHead = psHead;
        sNew.m_uiTicket = sOrig.m_uiTicket + 1;
        psTail->m_pNext_Node = sOrig.m_pHead;
    }
    while (!TgSTD_ATOMIC(compare_exchange_weak)( &psST->m_sTop, &sOrig, sNew ));
}


/* ---- tgCM_UT_LF__ST_Unaligned__Pop_Wait_Yield ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__ST_Node_Unaligned_P tgCM_UT_LF__ST_Unaligned__Pop_Wait_Yield( STg2_UT_LF__ST_Unaligned_PCU psST )
{
    STg2_UT_ST__ST_Node_Unaligned_P     pResult;

    while (1)
    {
        pResult = tgCM_UT_LF__ST_Unaligned__Pop( psST );
        if (nullptr != pResult)
        {
            break;
        };
        tgTR_Yield();
    }

    return (pResult);
}


/* ---- tgCM_UT_LF__ST_Unaligned__Pop_Wait_Spin -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__ST_Node_Unaligned_P tgCM_UT_LF__ST_Unaligned__Pop_Wait_Spin( STg2_UT_LF__ST_Unaligned_PCU psST )
{
    STg2_UT_ST__ST_Node_Unaligned_P     pResult;

    while (1)
    {
        pResult = tgCM_UT_LF__ST_Unaligned__Pop( psST );
        if (nullptr != pResult)
        {
            break;
        };
        tgTR_Pause();
    }

    return (pResult);

}


/* ---- tgCM_UT_LF__ST_Unaligned__Is_Empty ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCM_UT_LF__ST_Unaligned__Is_Empty( STg2_UT_LF__ST_Unaligned_PCU psST )
{
    STg2_UT_ST__PTR_TKT_Unaligned       sOrig;

    sOrig = TgSTD_ATOMIC(load)( &psST->m_sTop );

    return (nullptr == sOrig.m_pHead);
}


/* ---- Atomic Unordered Stack --------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- tgCM_UT_LF__ST__Init ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__ST__Init( STg2_UT_LF__ST_PCU psST )
{
    STg2_UT_ST__PTR_TKT                 sPTR_TKT;

    sPTR_TKT.m_pHead = nullptr;
    sPTR_TKT.m_uiTicket = 0;

    TgSTD_ATOMIC(store)( &psST->m_sTop, sPTR_TKT );
}


/* ---- tgCM_UT_LF__ST__Init_PreLoad --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__ST__Init_PreLoad( STg2_UT_LF__ST_PCU psST, TgVOID_P pData, TgRSIZE_C uiStride, TgRSIZE_C nuiData )
{
    STg2_UT_ST__PTR_TKT                 sPTR_TKT;
    TgUN_PTR                            sPTR;

    TgERROR( uiStride >= sizeof( STg2_UT_ST__ST_Node ));

    sPTR_TKT.m_pHead = (STg2_UT_ST__ST_Node_P)pData;
    sPTR_TKT.m_uiTicket = 0;

    sPTR.m_pVoid = pData;
    for (; sPTR_TKT.m_uiTicket + 1 < nuiData; ++sPTR_TKT.m_uiTicket)
    {
        *sPTR.m_puiPTR = sPTR.m_uiPTR + uiStride;
        sPTR.m_uiPTR += uiStride;
    };
    *sPTR.m_puiPTR = 0;
    
    TgSTD_ATOMIC(store)( &psST->m_sTop, sPTR_TKT );
}


/* ---- tgCM_UT_LF__ST__Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__ST__Free( TgATTRIBUTE_UNUSED STg2_UT_LF__ST_PCU psST )
{
}


/* ---- tgCM_UT_LF__ST__Push ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__ST__Push( STg2_UT_LF__ST_PCU psST, STg2_UT_ST__ST_Node_PCU psNode )
{
    STg2_UT_ST__PTR_TKT                 sOrig, sNew;
    
    sOrig = TgSTD_ATOMIC(load_explicit)( &psST->m_sTop, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        sNew.m_pHead = psNode;
        sNew.m_uiTicket = sOrig.m_uiTicket + 1;
        psNode->m_pNext_Node = sOrig.m_pHead;
    }
    while (!TgSTD_ATOMIC(compare_exchange_weak_explicit)( &psST->m_sTop, &sOrig, sNew, TgSTD_MEMORY_ORDER(seq_cst), TgSTD_MEMORY_ORDER(relaxed) ));
}


/* ---- tgCM_UT_LF__ST__Pop ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__ST_Node_P tgCM_UT_LF__ST__Pop( STg2_UT_LF__ST_PCU psST )
{
    STg2_UT_ST__PTR_TKT                 sOrig, sNew;
    
    sOrig = TgSTD_ATOMIC(load_explicit)( &psST->m_sTop, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        if (nullptr == sOrig.m_pHead)
        {
            return (nullptr);
        };
        sNew.m_pHead = (STg2_UT_ST__ST_Node_P)sOrig.m_pHead->m_pNext_Node;
        sNew.m_uiTicket = sOrig.m_uiTicket + 1;
    }
    while (!TgSTD_ATOMIC(compare_exchange_weak)( &psST->m_sTop, &sOrig, sNew ));
    
    return (sOrig.m_pHead);
}


/* ---- tgCM_UT_LF__ST__Release -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__ST_Node_P tgCM_UT_LF__ST__Release( STg2_UT_LF__ST_PCU psST )
{
    STg2_UT_ST__PTR_TKT                 sOrig, sNew;
    
    sOrig = TgSTD_ATOMIC(load_explicit)( &psST->m_sTop, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        if (nullptr == sOrig.m_pHead)
        {
            return (nullptr);
        };
        sNew.m_pHead = nullptr;
        sNew.m_uiTicket = sOrig.m_uiTicket + 1;
    }
    while (!TgSTD_ATOMIC(compare_exchange_weak)( &psST->m_sTop, &sOrig, sNew ));
    
    return (sOrig.m_pHead);

}


/* ---- tgCM_UT_LF__ST__Merge ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__ST__Merge( STg2_UT_LF__ST_PCU psST, STg2_UT_ST__ST_Node_P psHead, STg2_UT_ST__ST_Node_P psTail )
{
    STg2_UT_ST__PTR_TKT                 sOrig, sNew;
    
    sOrig = TgSTD_ATOMIC(load_explicit)( &psST->m_sTop, TgSTD_MEMORY_ORDER(relaxed) );
    do
    {
        sNew.m_pHead = psHead;
        sNew.m_uiTicket = sOrig.m_uiTicket + 1;
        psTail->m_pNext_Node = sOrig.m_pHead;
    }
    while (!TgSTD_ATOMIC(compare_exchange_weak)( &psST->m_sTop, &sOrig, sNew ));
}


/* ---- tgCM_UT_LF__ST__Pop_Wait_Yield ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__ST_Node_P tgCM_UT_LF__ST__Pop_Wait_Yield( STg2_UT_LF__ST_PCU psST )
{
    STg2_UT_ST__ST_Node_P               pResult;

    while (1)
    {
        pResult = tgCM_UT_LF__ST__Pop( psST );
        if (nullptr != pResult)
        {
            break;
        };
        tgTR_Yield();
    }

    return (pResult);
}


/* ---- tgCM_UT_LF__ST__Pop_Wait_Spin -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__ST_Node_P tgCM_UT_LF__ST__Pop_Wait_Spin( STg2_UT_LF__ST_PCU psST )
{
    STg2_UT_ST__ST_Node_P               pResult;

    while (1)
    {
        pResult = tgCM_UT_LF__ST__Pop( psST );
        if (nullptr != pResult)
        {
            break;
        };
        tgTR_Pause();
    }

    return (pResult);

}


/* ---- tgCM_UT_LF__ST__Is_Empty ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCM_UT_LF__ST__Is_Empty( STg2_UT_LF__ST_PCU psST )
{
    STg2_UT_ST__PTR_TKT                 sOrig;
    
    sOrig = TgSTD_ATOMIC(load)( &psST->m_sTop );

    return (nullptr == sOrig.m_pHead);
}


/* ---- Critical Section Stack --------------------------------------------------------------------------------------------------------------------------------------------------- */

#if TgCOMPILE__THREAD

/* ---- tgCM_UT_MT__ST_MX__Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_MT__ST_MX__Init( STg2_UT_MT__ST_MX_PCU psMP_ST, TgCHAR_U8_CPCU mbzName )
{
    TgVERIFY( KTgS_OK == tgPM_MT_MX_Init( &psMP_ST->m_sLock, nullptr ) );
    TgVERIFY( KTgS_OK == tgPM_MT_SM_Init( &psMP_ST->m_sStack_Count, mbzName, 0, KTgMAX_S32) );
    psMP_ST->m_psTop_Node = nullptr;
}


/* ---- tgCM_UT_MT__ST_MX__Free -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_MT__ST_MX__Free( STg2_UT_MT__ST_MX_PCU psMP_ST )
{
    TgERROR(nullptr == psMP_ST->m_psTop_Node);
    tgPM_MT_SM_Free( &psMP_ST->m_sStack_Count );
    tgPM_MT_MX_Free( &psMP_ST->m_sLock );
}


/* ---- tgCM_UT_MT__ST_MX__Push -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_MT__ST_MX__Push( STg2_UT_MT__ST_MX_PCU psMP_ST, STg2_UT_ST__ST_Node_PCU psMP_Node )
{
    tgPM_MT_MX_Wait_Block( &psMP_ST->m_sLock );

    psMP_Node->m_pNext_Node = (STg2_UT_ST__ST_Node_P)psMP_ST->m_psTop_Node;
    psMP_ST->m_psTop_Node = psMP_Node;

    tgPM_MT_MX_Release( &psMP_ST->m_sLock );

    tgPM_MT_SM_Signal( &psMP_ST->m_sStack_Count, 1 );
}


/* ---- tgCM_UT_MT__ST_MX__Pop --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__ST_Node_P tgCM_UT_MT__ST_MX__Pop( STg2_UT_MT__ST_MX_PCU psMP_ST )
{
    STg2_UT_ST__ST_Node_P               psTop_Node;

    if (TgFAILED( tgPM_MT_SM_Wait( &psMP_ST->m_sStack_Count ) ))
    {
        return (nullptr);
    };

    tgPM_MT_MX_Wait_Block( &psMP_ST->m_sLock );
    TgERROR(nullptr != psMP_ST->m_psTop_Node);

    psTop_Node = psMP_ST->m_psTop_Node;
    psMP_ST->m_psTop_Node = (STg2_UT_ST__ST_Node_P)psTop_Node->m_pNext_Node;

    tgPM_MT_MX_Release( &psMP_ST->m_sLock );

    return (psTop_Node);
}


/* ---- tgCM_UT_MT__ST_MX__Pop_Wait_Block ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__ST_Node_P tgCM_UT_MT__ST_MX__Pop_Wait_Block( STg2_UT_MT__ST_MX_PCU psMP_ST )
{
    STg2_UT_ST__ST_Node_P               psTop_Node;

    tgPM_MT_SM_Wait_Block( &psMP_ST->m_sStack_Count );

    tgPM_MT_MX_Wait_Block( &psMP_ST->m_sLock );
    TgERROR(nullptr != psMP_ST->m_psTop_Node);

    psTop_Node = psMP_ST->m_psTop_Node;
    psMP_ST->m_psTop_Node = (STg2_UT_ST__ST_Node_P)psTop_Node->m_pNext_Node;

    tgPM_MT_MX_Release( &psMP_ST->m_sLock );

    return (psTop_Node);
}


/* ---- tgCM_UT_MT__ST_MX__Is_Empty ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCM_UT_MT__ST_MX__Is_Empty( STg2_UT_MT__ST_MX_PCU psMP_ST )
{
    return (nullptr == psMP_ST->m_psTop_Node);
}

/*# TgCOMPILE__THREAD */
#endif


/* =============================================================================================================================================================================== */
#endif
