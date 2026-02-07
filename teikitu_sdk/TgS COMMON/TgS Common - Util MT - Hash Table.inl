/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Hash Table.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_MT_HASH_TABLE_INL)
#define TGS_COMMON_UTIL_MT_HASH_TABLE_INL

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Find_Internal(
    TgVOID_P, STg2_UT_LF__HT_RW_PCU, TgUINT_MAX_C );

TgEXTN TgRESULT
tgCM_UT_LF__HT_RW__Insert_Internal(
    STg2_UT_LF__HT_RW_PCU, TgUINT_MAX_C, TgVOID_CP );

TgEXTN TgRESULT
tgCM_UT_LF__HT_RW__Remove_Internal(
    STg2_UT_LF__HT_RW_PCU, TgUINT_MAX_C  );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_UT_LF__HT_RW__Free -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__HT_RW__Free( STg2_UT_LF__HT_RW_PCU psHash_Table )
{
    if (nullptr != psHash_Table->m_pReserved)
    {
        TgFREE_VIRTUAL( psHash_Table->m_pReserved );
    };
    psHash_Table->m_psHash_List = nullptr;
    psHash_Table->m_psNode_List = nullptr;
    psHash_Table->m_pReserved = nullptr;
    psHash_Table->m_psFree_Node_Head = nullptr;
    psHash_Table->m_nuiTop_Level_Node = 0;
    psHash_Table->m_nuiNode_Commit = 0;
    psHash_Table->m_nuiNode_Reserved = 0;

    tgCM_UT_LF__RW__Free( &psHash_Table->m_sLock.m_sLock );
}


/* ---- tgCM_UT_LF__HT_RW__Clear ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__HT_RW__Clear( STg2_UT_LF__HT_RW_PCU psHash_Table )
{
    tgMM_Set_U08_0x00( psHash_Table->m_psHash_List, psHash_Table->m_nuiTop_Level_Node * sizeof( STg2_UT_ST__HT_Node_P ) );

    if (psHash_Table->m_nuiNode_Commit > 0)
    {
        union
        {
            STg2_UT_ST__HT_Node_P               psNode;
            TgUINT_E08_P                        puiE08;
        }                                   uMem, uMem_Next;

        uMem.psNode = psHash_Table->m_psNode_List;
        psHash_Table->m_psFree_Node_Head = psHash_Table->m_psNode_List;

        for (TgRSIZE uiIndex = 0; uiIndex + 1 < psHash_Table->m_nuiNode_Commit; ++uiIndex)
        {
            uMem_Next.puiE08 = uMem.puiE08 + sizeof(STg2_UT_ST__HT_Node) + psHash_Table->m_nbyNode_Data;
            uMem.psNode->m_psNext = uMem_Next.psNode;
            uMem.psNode = uMem_Next.psNode;
        };
        uMem.psNode->m_psNext = nullptr;
    }
    else
    {
        psHash_Table->m_psFree_Node_Head = nullptr;
    }
}


/* ---- tgCM_UT_LF__HT_RW__Find_Internal ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Find_Internal( TgVOID_P pOutVal, STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash )
{
    TgRSIZE                             uiIndex;

    uiIndex = uiHash % psHash_Table->m_nuiTop_Level_Node;

    for (STg2_UT_ST__HT_Node_P psNode = psHash_Table->m_psHash_List[uiIndex]; nullptr != psNode; psNode = psNode->m_psNext)
    {
        if (psNode->m_uiHash == uiHash)
        {
            tgMM_Copy( pOutVal, psHash_Table->m_nbyNode_Data, psNode->m_auiData, psHash_Table->m_nbyNode_Data );
            return (KTgS_OK);
        };
    };

    return (KTgE_FAIL);
}


/* ---- tgCM_UT_LF__HT_RW__Find_Yield -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Find_Yield( TgVOID_P pOutVal, STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash )
{
    TgRESULT                            iResult;

    tgCM_UT_LF__RW__Enter_Read_Yield_Block( &psHash_Table->m_sLock.m_sLock );
    iResult = tgCM_UT_LF__HT_RW__Find_Internal( pOutVal, psHash_Table, uiHash );
    tgCM_UT_LF__RW__Exit_Read( &psHash_Table->m_sLock.m_sLock );
    return (iResult);
}


/* ---- tgCM_UT_LF__HT_RW__Find_Spin --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Find_Spin( TgVOID_P pOutVal, STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash )
{
    TgRESULT                            iResult;

    tgCM_UT_LF__RW__Enter_Read_Spin_Block( &psHash_Table->m_sLock.m_sLock );
    iResult = tgCM_UT_LF__HT_RW__Find_Internal( pOutVal, psHash_Table, uiHash );
    tgCM_UT_LF__RW__Exit_Read( &psHash_Table->m_sLock.m_sLock );
    return (iResult);
}


/* ---- tgCM_UT_LF__HT_RW__Find -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Find( TgVOID_P pOutVal, STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash )
{
    TgRESULT                            iResult;

    if (TgFAILED( tgCM_UT_LF__RW__Enter_Read( &psHash_Table->m_sLock.m_sLock ) ))
    {
        return (KTgE_FAIL);
    };
    iResult = tgCM_UT_LF__HT_RW__Find_Internal( pOutVal, psHash_Table, uiHash );
    tgCM_UT_LF__RW__Exit_Read( &psHash_Table->m_sLock.m_sLock );
    return (iResult);
}


/* ---- tgCM_UT_LF__HT_RW__Insert_Yield ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Insert_Yield( STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash, TgVOID_CP pValue )
{
    TgRESULT                            iResult;

    tgCM_UT_LF__RW__Enter_Write_Yield_Block( &psHash_Table->m_sLock.m_sLock );
    iResult = tgCM_UT_LF__HT_RW__Insert_Internal( psHash_Table, uiHash, pValue );
    tgCM_UT_LF__RW__Exit_Write( &psHash_Table->m_sLock.m_sLock );
    return (iResult);
}


/* ---- tgCM_UT_LF__HT_RW__Insert_Spin ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Insert_Spin( STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash, TgVOID_CP pValue )
{
    TgRESULT                            iResult;

    tgCM_UT_LF__RW__Enter_Write_Spin_Block( &psHash_Table->m_sLock.m_sLock );
    iResult = tgCM_UT_LF__HT_RW__Insert_Internal( psHash_Table, uiHash, pValue );
    tgCM_UT_LF__RW__Exit_Write( &psHash_Table->m_sLock.m_sLock );
    return (iResult);
}


/* ---- tgCM_UT_LF__HT_RW__Insert ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Insert( STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash, TgVOID_CP pValue )
{
    TgRESULT                            iResult;

    if (TgFAILED( tgCM_UT_LF__RW__Enter_Write( &psHash_Table->m_sLock.m_sLock ) ))
    {
        return (KTgE_FAIL);
    };
    iResult = tgCM_UT_LF__HT_RW__Insert_Internal( psHash_Table, uiHash, pValue );
    tgCM_UT_LF__RW__Exit_Write( &psHash_Table->m_sLock.m_sLock );
    return (iResult);
}


/* ---- tgCM_UT_LF__HT_RW__Update_Internal --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Update_Internal( STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash, TgVOID_CP pValue )
{
    TgRSIZE                             uiIndex;

    uiIndex = uiHash % psHash_Table->m_nuiTop_Level_Node;

    if (nullptr == pValue)
    {
        return (KTgE_FAIL);
    }

    for (STg2_UT_ST__HT_Node_P psNode = psHash_Table->m_psHash_List[uiIndex]; nullptr != psNode; psNode = psNode->m_psNext)
    {
        if (psNode->m_uiHash == uiHash)
        {
            tgMM_Copy( psNode->m_auiData, psHash_Table->m_nbyNode_Data, pValue, psHash_Table->m_nbyNode_Data );
            return (KTgS_OK);
        };
    };

    return (KTgE_FAIL);
}


/* ---- tgCM_UT_LF__HT_RW__Update_Yield ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Update_Yield( STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash, TgVOID_CP pValue )
{
    TgRESULT                            iResult;

    tgCM_UT_LF__RW__Enter_Write_Yield_Block( &psHash_Table->m_sLock.m_sLock );
    iResult = tgCM_UT_LF__HT_RW__Update_Internal( psHash_Table, uiHash, pValue );
    tgCM_UT_LF__RW__Exit_Write( &psHash_Table->m_sLock.m_sLock );
    return (iResult);
}


/* ---- tgCM_UT_LF__HT_RW__Update_Spin ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Update_Spin( STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash, TgVOID_CP pValue )
{
    TgRESULT                            iResult;

    tgCM_UT_LF__RW__Enter_Write_Spin_Block( &psHash_Table->m_sLock.m_sLock );
    iResult = tgCM_UT_LF__HT_RW__Update_Internal( psHash_Table, uiHash, pValue );
    tgCM_UT_LF__RW__Exit_Write( &psHash_Table->m_sLock.m_sLock );
    return (iResult);
}


/* ---- tgCM_UT_LF__HT_RW__Update ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Update( STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash, TgVOID_CP pValue )
{
    TgRESULT                            iResult;

    if (TgFAILED( tgCM_UT_LF__RW__Enter_Write( &psHash_Table->m_sLock.m_sLock ) ))
    {
        return (KTgE_FAIL);
    };
    iResult = tgCM_UT_LF__HT_RW__Update_Internal( psHash_Table, uiHash, pValue );
    tgCM_UT_LF__RW__Exit_Write( &psHash_Table->m_sLock.m_sLock );
    return (iResult);
}


/* ---- tgCM_UT_LF__HT_RW__Remove_Yield ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Remove_Yield( STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash )
{
    TgRESULT                            iResult;

    tgCM_UT_LF__RW__Enter_Write_Yield_Block( &psHash_Table->m_sLock.m_sLock );
    iResult = tgCM_UT_LF__HT_RW__Remove_Internal( psHash_Table, uiHash );
    tgCM_UT_LF__RW__Exit_Write( &psHash_Table->m_sLock.m_sLock );
    return (iResult);
}


/* ---- tgCM_UT_LF__HT_RW__Remove_Spin ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Remove_Spin( STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash )
{
    TgRESULT                            iResult;

    tgCM_UT_LF__RW__Enter_Write_Spin_Block( &psHash_Table->m_sLock.m_sLock );
    iResult = tgCM_UT_LF__HT_RW__Remove_Internal( psHash_Table, uiHash );
    tgCM_UT_LF__RW__Exit_Write( &psHash_Table->m_sLock.m_sLock );
    return (iResult);
}


/* ---- tgCM_UT_LF__HT_RW__Remove ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_LF__HT_RW__Remove( STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash )
{
    TgRESULT                            iResult;

    if (TgFAILED( tgCM_UT_LF__RW__Enter_Write( &psHash_Table->m_sLock.m_sLock ) ))
    {
        return (KTgE_FAIL);
    };
    iResult = tgCM_UT_LF__HT_RW__Remove_Internal( psHash_Table, uiHash );
    tgCM_UT_LF__RW__Exit_Write( &psHash_Table->m_sLock.m_sLock );
    return (iResult);
}


/* ---- tgCM_UT_LF__HT_RW__Output_List ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__HT_RW__Output_List( STg2_UT_LF__HT_RW_PCU psHash_Table, STg2_Output_PC psOUT, TgVOID(*pfnOutput)( STg2_Output_PC, TgUINT_E08_CPC ) )
{
    tgCM_UT_LF__RW__Enter_Read_Yield_Block( &psHash_Table->m_sLock.m_sLock );

    for (TgRSIZE uiTop_Level_Node = 0; uiTop_Level_Node < psHash_Table->m_nuiTop_Level_Node; ++uiTop_Level_Node)
    {
        for (STg2_UT_ST__HT_Node_P psNode = psHash_Table->m_psHash_List[uiTop_Level_Node]; nullptr != psNode; psNode = psNode->m_psNext)
        {
            pfnOutput( psOUT, psNode->m_auiData );
        };
    };

    tgCM_UT_LF__RW__Exit_Read( &psHash_Table->m_sLock.m_sLock );
}


/* =============================================================================================================================================================================== */
#endif
