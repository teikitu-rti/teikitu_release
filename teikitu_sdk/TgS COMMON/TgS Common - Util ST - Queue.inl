/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util ST - Queue.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_ST_QUEUE_INL)
#define TGS_COMMON_UTIL_ST_QUEUE_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Spin-Lock Queue ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- tgCM_UT_ST__QU__Init ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__QU__Init( STg2_UT_ST__QU_PC psMP_QU )
{
    psMP_QU->m_sNode.m_pNext_Node = &psMP_QU->m_sNode;
    psMP_QU->m_psTail_Node = &psMP_QU->m_sNode;
    return (KTgS_OK);
}


/* ---- tgCM_UT_ST__QU__Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__QU__Free( TgATTRIBUTE_UNUSED_PARAM_CHECK STg2_UT_ST__QU_PC psMP_QU )
{
    TgPARAM_CHECK(tgCM_UT_ST__QU__Is_Empty( psMP_QU ));
}


/* ---- tgCM_UT_ST__QU__Enqueue -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__QU__Enqueue( STg2_UT_ST__QU_PC psMP_QU, STg2_UT_ST__QU_Node_PC psNode )
{
    STg2_UT_ST__QU_Node_P               psTailNode;

    psTailNode = psNode;
    while (nullptr != psTailNode->m_pNext_Node)
    {
        psTailNode = psTailNode->m_pNext_Node;
    } 

    psMP_QU->m_psTail_Node->m_pNext_Node = psNode;
    psMP_QU->m_psTail_Node = psTailNode;
    psMP_QU->m_psTail_Node->m_pNext_Node = &psMP_QU->m_sNode;
}


/* ---- tgCM_UT_ST__QU__Merge ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__QU__Merge( STg2_UT_ST__QU_PC psMP_QU0, STg2_UT_ST__QU_PC psMP_QU1 )
{
    STg2_UT_ST__QU_Node_P               psTailNode;
    STg2_UT_ST__QU_Node_P               psNode;

    if( tgCM_UT_ST__QU__Is_Empty( psMP_QU1 ))
    {
        return;
    };

    psNode = psMP_QU1->m_sNode.m_pNext_Node;

    psTailNode = psMP_QU1->m_psTail_Node;
    psTailNode->m_pNext_Node = &psMP_QU0->m_sNode;

    psMP_QU0->m_psTail_Node->m_pNext_Node = psNode;
    psMP_QU0->m_psTail_Node = psTailNode;

    psMP_QU1->m_sNode.m_pNext_Node = &psMP_QU1->m_sNode;
    psMP_QU1->m_psTail_Node = &psMP_QU1->m_sNode;
}


/* ---- tgCM_UT_ST__QU__Dequeue -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE STg2_UT_ST__QU_Node_P tgCM_UT_ST__QU__Dequeue( STg2_UT_ST__QU_PC psMP_QU )
{
    STg2_UT_ST__QU_Node_P               psNode;

    psNode = psMP_QU->m_sNode.m_pNext_Node;
    if (&psMP_QU->m_sNode == psNode)
    {
        return (nullptr);
    };

    psMP_QU->m_sNode.m_pNext_Node = psNode->m_pNext_Node;

    if (&psMP_QU->m_sNode == psNode->m_pNext_Node)
    {
        psMP_QU->m_psTail_Node = &psMP_QU->m_sNode;
    };

    psNode->m_pNext_Node = (STg2_UT_ST__QU_Node_P)nullptr;
    return (psNode);
}


/* ---- tgCM_UT_ST__QU__Is_Empty ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCM_UT_ST__QU__Is_Empty( STg2_UT_ST__QU_PC psMP_QU )
{
    return (&psMP_QU->m_sNode == psMP_QU->m_sNode.m_pNext_Node);
}


/* ---- tgCM_UT_ST__QU__Is_Valid ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCM_UT_ST__QU__Is_Valid( STg2_UT_ST__QU_PC psMP_QU )
{
    STg2_UT_ST__QU_Node_P               psNode;

    if ((nullptr == psMP_QU->m_psTail_Node) || (psMP_QU->m_psTail_Node->m_pNext_Node != &psMP_QU->m_sNode))
    {
        return (false);
    };

    psNode = psMP_QU->m_sNode.m_pNext_Node;
    do
    {
        if (psNode == psMP_QU->m_psTail_Node)
        {
            return (true);
        };
        psNode = psNode->m_pNext_Node;
    }
    while (psNode != &psMP_QU->m_sNode);
    return (false);
}


/* ---- tgCM_UT_ST__QU__In_Queue ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCM_UT_ST__QU__In_Queue( STg2_UT_ST__QU_PC psMP_QU, STg2_UT_ST__QU_Node_PC psTest )
{
    STg2_UT_ST__QU_Node_P               psNode;

    psNode = psMP_QU->m_sNode.m_pNext_Node;
    do
    {
        if (psNode == psTest)
        {
            return (true);
        };
        if (psNode == psMP_QU->m_psTail_Node)
        {
            break;
        };
        psNode = psNode->m_pNext_Node;
    }
    while (psNode != &psMP_QU->m_sNode);
    return (false);
}


/* =============================================================================================================================================================================== */
#endif
