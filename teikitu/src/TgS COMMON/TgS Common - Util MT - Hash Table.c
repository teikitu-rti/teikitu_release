/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Hash Table.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/** The memory structure for the hash table is kept simple. The first level of hash nodes(nuiEntries) is an array of pointers at the start of the hash table. These pointers will
    reference hash nodes kept in the region of memory managed by the hash table. The first node contains a next node reference (linked list) for all entries that index to the same
    location in the hash table. Thus, while the number of first level entries controls the amount of overhead for the hash table, it also controls the likely depth of the table's
    linked lists for a particular index. */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Interface                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_UT_LF__HT_RW__Init_Virtual ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_UT_LF__HT_RW__Init_Virtual( STg2_UT_LF__HT_RW_P psHash_Table, TgRSIZE_C nbyNode_Data, TgRSIZE_C nuiEntries, TgRSIZE_C nuiTotal )
{
    TgRSIZE_C                           nbyNode_With_Data = sizeof( STg2_UT_ST__HT_Node ) + tgCM_CEL_ALGN_PW2_UMAX( nbyNode_Data, 8 );
    TgUN_PTR                            uMem;

    if ((nuiTotal <= 1) || (nuiTotal < nuiEntries + 1))
    {
        return (KTgE_FAIL);
    };

    uMem.m_pVoid = TgRESERVE_VIRTUAL( nuiEntries * sizeof( STg2_UT_ST__HT_Node_P ) + nuiTotal * nbyNode_With_Data );
    if (nullptr == uMem.m_pVoid)
    {
        return (KTgE_FAIL);
    };

    uMem.m_pVoid = TgCOMMIT_VIRTUAL( uMem.m_pVoid, nuiEntries * sizeof( STg2_UT_ST__HT_Node_P ) );
    if (nullptr == uMem.m_pVoid)
    {
        TgFREE_VIRTUAL( uMem.m_pVoid );
        return (KTgE_FAIL);
    };

    if (TgFAILED( tgCM_UT_LF__RW__Init( &psHash_Table->m_sLock.m_sLock ) ))
    {
        TgFREE_VIRTUAL( uMem.m_pVoid );
        return (KTgE_FAIL);
    };

    psHash_Table->m_psHash_List = (STg2_UT_ST__HT_Node_PP)uMem.m_pVoid;
    psHash_Table->m_pReserved = uMem.m_pVoid;
    uMem.m_uiPTR += nuiEntries * sizeof( STg2_UT_ST__HT_Node_P );
    psHash_Table->m_psNode_List = (STg2_UT_ST__HT_Node_P)uMem.m_pVoid;

    psHash_Table->m_psFree_Node_Head = nullptr;
    psHash_Table->m_nbyNode_Data = nbyNode_Data;
    psHash_Table->m_nbyNode = nbyNode_With_Data;
    psHash_Table->m_nuiTop_Level_Node = nuiEntries;
    psHash_Table->m_nuiNode_Active = 0;
    psHash_Table->m_nuiNode_Commit = (tgMM_Page_Size() - (uMem.m_uiPTR % tgMM_Page_Size())) / psHash_Table->m_nbyNode;
    psHash_Table->m_nuiNode_Commit = tgCM_MIN_UMAX( psHash_Table->m_nuiNode_Commit, nuiTotal );
    psHash_Table->m_nuiNode_Reserved = nuiTotal;

    tgCM_UT_LF__HT_RW__Clear( psHash_Table );
    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__HT_RW__Init_Fixed -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_UT_LF__HT_RW__Init_Fixed( STg2_UT_LF__HT_RW_PCU psHash_Table, TgRSIZE_C nbyNode_Data, TgRSIZE_C nuiEntries, TgRSIZE_C nuiBuffer_Size, TgVOID_P psBuffer )
{
    TgUN_PTR                            uMem;

    TgRSIZE_C                           nbyNode_With_Data = sizeof( STg2_UT_ST__HT_Node ) + tgCM_CEL_ALGN_PW2_UMAX( nbyNode_Data, 8 );
    TgRSIZE_C                           nbyOverhead = nuiEntries * sizeof( STg2_UT_ST__HT_Node_P );
    TgRSIZE_C                           nuiNode_Commit = (nuiBuffer_Size - nbyOverhead) / nbyNode_With_Data;

    if ((nuiBuffer_Size < nbyOverhead + nuiEntries * nbyNode_With_Data) || (nuiNode_Commit < 1))
    {
        return (KTgE_FAIL);
    };

    if (TgFAILED( tgCM_UT_LF__RW__Init( &psHash_Table->m_sLock.m_sLock ) ))
    {
        return (KTgE_FAIL);
    };

    uMem.m_pVoid = psBuffer;

    psHash_Table->m_psHash_List = (STg2_UT_ST__HT_Node_PP)uMem.m_pVoid;
    uMem.m_uiPTR += nuiEntries * sizeof( STg2_UT_ST__HT_Node_P );
    psHash_Table->m_psNode_List = (STg2_UT_ST__HT_Node_P)uMem.m_pVoid;
    psHash_Table->m_pReserved = nullptr;
    psHash_Table->m_psFree_Node_Head = nullptr;
    psHash_Table->m_nbyNode_Data = nbyNode_Data;
    psHash_Table->m_nbyNode = nbyNode_With_Data;
    psHash_Table->m_nuiTop_Level_Node = nuiEntries;
    psHash_Table->m_nuiNode_Active = 0;
    psHash_Table->m_nuiNode_Commit = nuiNode_Commit;
    psHash_Table->m_nuiNode_Reserved = nuiNode_Commit;

    tgCM_UT_LF__HT_RW__Clear( psHash_Table );
    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__HT_RW__Insert_Internal --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_UT_LF__HT_RW__Insert_Internal( STg2_UT_LF__HT_RW_PCU NONULL psHash_Table, TgUINT_MAX_C uiHash, TgVOID_CP pValue )
{
    TgRSIZE                             uiIndex;
    union
    {
        STg2_UT_ST__HT_Node_P               psNode;
        TgUINT_E08_P                        puiE08;
        TgVOID_P                            pVoid;
        TgUINT_PTR                          uiPTR;
    }                                   uMem, uMem_Next;

    if (nullptr == psHash_Table->m_psFree_Node_Head)
    {
        TgRSIZE                             nuiNode;

        if (psHash_Table->m_nuiNode_Commit >= psHash_Table->m_nuiNode_Reserved)
        {
            return (KTgE_FAIL);
        };

        uMem.psNode = psHash_Table->m_psNode_List;
        uMem.puiE08 += psHash_Table->m_nuiNode_Commit * psHash_Table->m_nbyNode;
        uMem.pVoid = TgCOMMIT_VIRTUAL( uMem.pVoid, psHash_Table->m_nbyNode );
        if (nullptr == uMem.pVoid)
        {
            return (KTgE_FAIL);
        };

        psHash_Table->m_psFree_Node_Head = uMem.psNode;
        ++psHash_Table->m_nuiNode_Commit;

        nuiNode = (tgMM_Page_Size() - (uMem.uiPTR % tgMM_Page_Size())) / psHash_Table->m_nbyNode;
        for (uiIndex = 1; uiIndex < nuiNode && psHash_Table->m_nuiNode_Commit < psHash_Table->m_nuiNode_Reserved; ++uiIndex)
        {
            uMem_Next.puiE08 = uMem.puiE08 + psHash_Table->m_nbyNode;
            uMem.psNode->m_psNext = uMem_Next.psNode;
            uMem.psNode = uMem_Next.psNode;
            ++psHash_Table->m_nuiNode_Commit;
        };
        uMem.psNode->m_psNext = 0;
    };

    uiIndex = uiHash % psHash_Table->m_nuiTop_Level_Node;
    uMem.psNode = psHash_Table->m_psFree_Node_Head;
    psHash_Table->m_psFree_Node_Head = uMem.psNode->m_psNext;

    uMem_Next.psNode = psHash_Table->m_psHash_List[uiIndex];
    uMem.psNode->m_uiHash = uiHash;
    uMem.psNode->m_psNext = uMem_Next.psNode;
    if (nullptr != pValue)
    {
        tgMM_Copy( uMem.psNode->m_auiData, psHash_Table->m_nbyNode_Data, pValue, psHash_Table->m_nbyNode_Data );
    };
    psHash_Table->m_psHash_List[uiIndex] = uMem.psNode;
    ++psHash_Table->m_nuiNode_Active;

    return (KTgS_OK);
}


/* ---- tgCM_UT_LF__HT_RW__Remove_Internal --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_UT_LF__HT_RW__Remove_Internal( STg2_UT_LF__HT_RW_PCU psHash_Table, TgUINT_MAX_C uiHash )
{
    STg2_UT_ST__HT_Node_P               psNode;

    TgRSIZE_C       uiIndex = uiHash % psHash_Table->m_nuiTop_Level_Node;

    psNode = psHash_Table->m_psHash_List[uiIndex];

    if (nullptr == psNode)
    {
        return (KTgE_FAIL);
    };

    if (psNode->m_uiHash == uiHash)
    {
        psHash_Table->m_psHash_List[uiIndex] = psNode->m_psNext;
    }
    else
    {
        STg2_UT_ST__HT_Node_P               psPrev_Node;

        for (psPrev_Node = psNode, psNode = psNode->m_psNext; nullptr != psNode; psPrev_Node = psNode, psNode = psNode->m_psNext)
        {
            if (psNode->m_uiHash == uiHash)
            {
                psPrev_Node->m_psNext = psNode->m_psNext;
                break;
            };
        };

        if (nullptr == psNode)
        {
            return (KTgE_FAIL);
        }
    };

    psNode->m_uiHash = KTgEMPTY_HASH;
    psNode->m_psNext = psHash_Table->m_psFree_Node_Head;
    psHash_Table->m_psFree_Node_Head = psNode;
    --psHash_Table->m_nuiNode_Active;

    return (KTgS_OK);
}


