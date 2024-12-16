/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util ST - List.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_ST_LIST_INL)
#define TGS_COMMON_UTIL_ST_LIST_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Spin-Lock Queue ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- tgCM_UT_ST__LT__Init ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__LT__Init( STg2_UT_ST__LT_PCU psMP_LT )
{
    TgPARAM_CHECK(psMP_LT);
    psMP_LT->m_sNode.m_pPrev_Node = &psMP_LT->m_sNode;
    psMP_LT->m_sNode.m_pNext_Node = &psMP_LT->m_sNode;
    return (KTgS_OK);
}


/* ---- tgCM_UT_ST__LT__Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__LT__Free( TgATTRIBUTE_UNUSED_PARAM_CHECK STg2_UT_ST__LT_PCU psMP_LT )
{
    TgPARAM_CHECK(psMP_LT && psMP_LT->m_sNode.m_pPrev_Node && psMP_LT->m_sNode.m_pNext_Node);
    TgERROR(tgCM_UT_ST__LT__Is_Empty( psMP_LT ));
}


/* ---- tgCM_UT_ST__LT__Push_Front ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__LT__Push_Front( STg2_UT_ST__LT_PCU psMP_LT, STg2_UT_ST__LT_Node_PC psNode )
{
    TgPARAM_CHECK(psMP_LT->m_sNode.m_pPrev_Node && psMP_LT->m_sNode.m_pNext_Node && psNode);
    psNode->m_pPrev_Node = &psMP_LT->m_sNode;
    psNode->m_pNext_Node = psMP_LT->m_sNode.m_pNext_Node;
    TgERROR(nullptr != psNode->m_pNext_Node);
    psMP_LT->m_sNode.m_pNext_Node->m_pPrev_Node = psNode;
    psMP_LT->m_sNode.m_pNext_Node = psNode;
    TgERROR(nullptr != psNode);
}


/* ---- tgCM_UT_ST__LT__Push_Back ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__LT__Push_Back( STg2_UT_ST__LT_PCU psMP_LT, STg2_UT_ST__LT_Node_PC psNode )
{
    TgPARAM_CHECK(psMP_LT && psMP_LT->m_sNode.m_pPrev_Node && psMP_LT->m_sNode.m_pNext_Node && psNode);
    psNode->m_pPrev_Node = psMP_LT->m_sNode.m_pPrev_Node;
    psNode->m_pNext_Node = &psMP_LT->m_sNode;
    TgERROR(nullptr != psNode->m_pNext_Node);
    psMP_LT->m_sNode.m_pPrev_Node->m_pNext_Node = psNode;
    TgERROR(nullptr != psNode);
    psMP_LT->m_sNode.m_pPrev_Node = psNode;
}


/* ---- tgCM_UT_ST__LT__Pop_Front ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__LT_Node_P tgCM_UT_ST__LT__Pop_Front( STg2_UT_ST__LT_PCU psMP_LT )
{
    STg2_UT_ST__LT_Node_P                  psNode;

    TgPARAM_CHECK(psMP_LT && psMP_LT->m_sNode.m_pPrev_Node && psMP_LT->m_sNode.m_pNext_Node);
    psNode = psMP_LT->m_sNode.m_pNext_Node;
    if (&psMP_LT->m_sNode == psNode)
    {
        return (nullptr);
    };

    psNode->m_pNext_Node->m_pPrev_Node = psNode->m_pPrev_Node;
    psMP_LT->m_sNode.m_pNext_Node = psNode->m_pNext_Node;

    return (psNode);
}


/* ---- tgCM_UT_ST__LT__Pop_Back ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__LT_Node_P tgCM_UT_ST__LT__Pop_Back( STg2_UT_ST__LT_PCU psMP_LT )
{
    STg2_UT_ST__LT_Node_P                  psNode;

    TgPARAM_CHECK(psMP_LT && psMP_LT->m_sNode.m_pPrev_Node && psMP_LT->m_sNode.m_pNext_Node);
    psNode = psMP_LT->m_sNode.m_pPrev_Node;
    if (&psMP_LT->m_sNode == psNode)
    {
        return (nullptr);
    };

    psNode->m_pPrev_Node->m_pNext_Node = psNode->m_pNext_Node;
    psMP_LT->m_sNode.m_pPrev_Node = psNode->m_pPrev_Node;

    return (psNode);
}


/* ---- tgCM_UT_ST__LT__Insert --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__LT__Insert( STg2_UT_ST__LT_Node_PC psNodeAt, STg2_UT_ST__LT_Node_PC psNewNode )
{
    TgPARAM_CHECK(psNodeAt && psNewNode);
    psNewNode->m_pPrev_Node = psNodeAt->m_pPrev_Node;
    psNewNode->m_pNext_Node = psNodeAt;
    psNodeAt->m_pPrev_Node->m_pNext_Node = psNewNode;
    psNodeAt->m_pPrev_Node = psNewNode;
}


/* ---- tgCM_UT_ST__LT__Remove --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__LT__Remove( STg2_UT_ST__LT_Node_PC psNode )
{
    TgPARAM_CHECK(psNode && psNode->m_pPrev_Node && psNode->m_pNext_Node);
    psNode->m_pPrev_Node->m_pNext_Node = psNode->m_pNext_Node;
    psNode->m_pNext_Node->m_pPrev_Node = psNode->m_pPrev_Node;
    TgPARAM_CHECK(psNode->m_pPrev_Node && psNode->m_pPrev_Node->m_pPrev_Node && psNode->m_pPrev_Node->m_pNext_Node);
    TgPARAM_CHECK(psNode->m_pNext_Node && psNode->m_pNext_Node->m_pPrev_Node && psNode->m_pNext_Node->m_pNext_Node);
    psNode->m_pNext_Node = (STg2_UT_ST__LT_Node_P)nullptr;
    psNode->m_pPrev_Node = (STg2_UT_ST__LT_Node_P)nullptr;
}


/* ---- tgCM_UT_ST__LT__Is_Empty ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCM_UT_ST__LT__Is_Empty( STg2_UT_ST__LT_PCU psMP_LT )
{
    TgPARAM_CHECK(psMP_LT && psMP_LT->m_sNode.m_pPrev_Node && psMP_LT->m_sNode.m_pNext_Node);
    return (psMP_LT->m_sNode.m_pPrev_Node == &psMP_LT->m_sNode);
}


/* =============================================================================================================================================================================== */
#endif
