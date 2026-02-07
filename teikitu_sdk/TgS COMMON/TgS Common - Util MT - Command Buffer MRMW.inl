/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Command Buffer MRMW.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_MT_COMMAND_BUFFER_MRMW_INL)
#define TGS_COMMON_UTIL_MT_COMMAND_BUFFER_MRMW_INL

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_UT__CMD_BUF__Init --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT__CMD_BUF__Init( STg2_UT__CMD_BUF_PCU psCMD_BUF, TgUINT_E32_C nbyMax )
{
    psCMD_BUF->m_pBuffer = TgRESERVE_VIRTUAL( nbyMax );
    if (nullptr == psCMD_BUF->m_pBuffer)
    {
        return (KTgE_FAIL);
    };

    psCMD_BUF->m_pBuffer = TgCOMMIT_VIRTUAL( psCMD_BUF->m_pBuffer, 0, nbyMax );
    if (nullptr == psCMD_BUF->m_pBuffer)
    {
        TgFREE_VIRTUAL( psCMD_BUF->m_pBuffer );
        return (KTgE_FAIL);
    };

    TgSTD_ATOMIC(store)( &psCMD_BUF->m_uiREQ_NBY, 0 );
    TgSTD_ATOMIC(store)( &psCMD_BUF->m_nuiCompleted, 0 );
    psCMD_BUF->m_nbyMax = nbyMax;

    return (KTgS_OK);
}


/* ---- tgCM_UT__CMD_BUF__Free --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT__CMD_BUF__Free( STg2_UT__CMD_BUF_PCU psCMD_BUF )
{
    if (nullptr != psCMD_BUF->m_pBuffer)
    {
        TgFREE_VIRTUAL( psCMD_BUF->m_pBuffer );
    };

    return (KTgS_OK);
}


/* ---- tgCM_UT__CMD_BUF__Query_Used_Size ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgCM_UT__CMD_BUF__Query_Used_Size( STg2_UT__CMD_BUF_PCU psCMD_BUF )
{
    STg2_UT__CMD_BUF__INDEX             sOrig;

    sOrig.m_uiREQ_NBY = TgSTD_ATOMIC(load)( &psCMD_BUF->m_uiREQ_NBY );

    return (sOrig.m_nbyUsed);
}


/* ---- tgCM_UT__CMD_BUF__Query_Free_Size ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgCM_UT__CMD_BUF__Query_Free_Size( STg2_UT__CMD_BUF_PCU psCMD_BUF )
{
    STg2_UT__CMD_BUF__INDEX             sOrig;

    sOrig.m_uiREQ_NBY = TgSTD_ATOMIC(load)( &psCMD_BUF->m_uiREQ_NBY );

    return (psCMD_BUF->m_nbyMax - sOrig.m_nbyUsed);
}


/* ---- tgCM_UT__CMD_BUF__Query_Max_Size ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgSIZE_ALL tgCM_UT__CMD_BUF__Query_Max_Size( STg2_UT__CMD_BUF_PCU psCMD_BUF )
{
    return (psCMD_BUF->m_nbyMax);
}


/* ---- tgCM_UT__CMD_BUF__Queue_Command ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT__CMD_BUF__Queue_Command( STg2_UT__CMD_BUF_PCU psCMD_BUF, TgFCN_CMD_FUNCTION pfnCommand, TgRSIZE_C nbyParam, TgVOID_CPC pParam )
{
    STg2_UT__CMD_BUF__INDEX             sOrig, sNew;
    TgUINT_E32                          nbyParam_16;
    union {
        TgVOID_P                            pVoid;
        TgUINT_E08_P                        puiE08;
        STg2_UT__CMD_BUF__CMD_P             pCMD;
    }                                   sCmd_Buffer = { .pVoid = psCMD_BUF->m_pBuffer };

    nbyParam_16 = tgCM_CEL_ALGN_PW2_U32( (TgUINT_E32)nbyParam, 16 );
    do
    {
        sOrig.m_uiREQ_NBY = TgSTD_ATOMIC(load)( &psCMD_BUF->m_uiREQ_NBY );
        sNew.m_nuiRequested = sOrig.m_nuiRequested + 1;
        if (psCMD_BUF->m_nbyMax - sOrig.m_nbyUsed < sizeof(STg2_UT__CMD_BUF__CMD) + nbyParam_16)
        {
            return (KTgE_FAIL);
        }
        sNew.m_nbyUsed = sOrig.m_nbyUsed + (TgUINT_E32)sizeof(STg2_UT__CMD_BUF__CMD) + nbyParam_16;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psCMD_BUF->m_uiREQ_NBY, &sOrig.m_uiREQ_NBY, sNew.m_uiREQ_NBY ));

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );

    sCmd_Buffer.puiE08 += sOrig.m_nbyUsed;
    sCmd_Buffer.pCMD->m_pfnCommand = pfnCommand;
    sCmd_Buffer.pCMD->m_nbyParam = nbyParam;
    sCmd_Buffer.puiE08 += sizeof(STg2_UT__CMD_BUF__CMD);

    tgMM_Copy( sCmd_Buffer.pVoid, nbyParam_16, pParam, nbyParam );

    TgSTD_ATOMIC(fetch_add)( &psCMD_BUF->m_nuiCompleted, 1 );
    return (KTgS_OK);
}


/* ---- tgCM_UT__CMD_BUF__Execute ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT__CMD_BUF__Execute( STg2_UT__CMD_BUF_PCU psCMD_BUF )
{
    STg2_UT__CMD_BUF__INDEX             sOrig;
    TgRSIZE                             nbyIndex, nbyMax, nuiServed;
    union {
        TgVOID_P                            pVoid;
        TgUINT_E08_P                        puiE08;
        STg2_UT__CMD_BUF__CMD_P             pCMD;
    }                                   sCmd_Buffer = { .pVoid = psCMD_BUF->m_pBuffer };

    sOrig.m_uiREQ_NBY = TgSTD_ATOMIC(load)( &psCMD_BUF->m_uiREQ_NBY );
    while(!TgSTD_ATOMIC(compare_exchange_weak)( &psCMD_BUF->m_nuiCompleted, &sOrig.m_nuiRequested, sOrig.m_nuiRequested ))
    {
        tgTR_Pause();
        sOrig.m_uiREQ_NBY = TgSTD_ATOMIC(load)( &psCMD_BUF->m_uiREQ_NBY );
    }

    TgSTD_ATOMIC(thread_fence)( TgSTD_MEMORY_ORDER(seq_cst) );

    nbyMax = sOrig.m_nbyUsed;
    for (nbyIndex = 0, nuiServed = 0; nbyIndex < nbyMax; ++nuiServed)
    {
        TgUINT_E32                          nbyParam_16;

        sCmd_Buffer.pCMD->m_pfnCommand( sCmd_Buffer.puiE08 + sizeof(STg2_UT__CMD_BUF__CMD), sCmd_Buffer.pCMD->m_nbyParam );
        nbyParam_16 = tgCM_CEL_ALGN_PW2_U32( (TgUINT_E32)sCmd_Buffer.pCMD->m_nbyParam, 16 );
        nbyIndex += nbyParam_16 + sizeof(STg2_UT__CMD_BUF__CMD);
        sCmd_Buffer.puiE08 += nbyParam_16 + sizeof(STg2_UT__CMD_BUF__CMD);
    }

    TgPARAM_CHECK( nuiServed == sOrig.m_nuiRequested );

    TgSTD_ATOMIC(store)( &psCMD_BUF->m_uiREQ_NBY, 0 );
    TgSTD_ATOMIC(store)( &psCMD_BUF->m_nuiCompleted, 0 );
}



/* =============================================================================================================================================================================== */
#endif
