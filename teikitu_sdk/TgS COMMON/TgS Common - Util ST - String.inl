/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util ST - String.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_SP_STRING_INL)
#define TGS_COMMON_UTIL_SP_STRING_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgRESULT
tgCM_UT_ST__ST__Change_Cast_Internal(
    STg2_UT_ST__ST_PC NONULL, TgBOOL_C  );

TgEXTN TgRESULT
tgCM_UT_ST__ST__SO_SF_Find_String_Internal(
    STg1_Text_Length_PC NONULL, STg2_UT_ST__ST_CPC NONULL, TgRSIZE_C, STg2_UT_ST__ST_CPC NONULL, TgRSIZE_C, TgRSIZE_C, TgBOOL );

TgEXTN TgRESULT
tgCM_UT_ST__ST__SO_SN_Find_Set_Internal(
    STg1_Text_Length_PC NONULL, STg2_UT_ST__ST_CPC NONULL, TgRSIZE_C, TgCHAR_U8_CPC NONULL, TgRSIZE_C, TgBOOL_C, TgBOOL_C );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_UT_LF__ST__Init ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__Init( STg2_UT_ST__ST_PC psDest )
{
    psDest->m_nbyReserve = KTgSTRING_STATIC_BUFFER_SIZE;
    psDest->m_nbyBuffer = 0;
    psDest->m_ambBuffer[0] = '\0';
}


/* ---- tgCM_UT_ST__ST__Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__Free( STg2_UT_ST__ST_PC psDest )
{
    tgCM_UT_ST__ST__Clear( psDest );
}


/* ---- tgCM_UT_ST__ST__SZ_Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SZ_Init( STg2_UT_ST__ST_PC psDest, TgCHAR_U8_CPC mbzARG )
{
    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzARG));
    tgCM_UT_ST__ST__Init( psDest );
    tgCM_UT_ST__ST__SZ_Assign( psDest, mbzARG );
}


/* ---- tgCM_UT_ST__ST__SN_Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SN_Init( STg2_UT_ST__ST_PC psDest, TgCHAR_U8_CPC mbzARG, TgRSIZE_C nbyMaxARG )
{
    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzARG));
    tgCM_UT_ST__ST__Init( psDest );
    tgCM_UT_ST__ST__SN_Assign( psDest, mbzARG, nbyMaxARG );
}


/* ---- tgCM_UT_ST__ST__PT_Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__PT_Init( STg2_UT_ST__ST_PC psDest, TgCHAR_U8_CPC mbzStart, TgCHAR_U8_CPC mbzEnd )
{
    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzStart) && (nullptr != mbzEnd));
    tgCM_UT_ST__ST__Init( psDest );
    tgCM_UT_ST__ST__PT_Assign( psDest, mbzStart, mbzEnd );
}


/* ---- tgCM_UT_ST__ST__ST_Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__ST_Init( STg2_UT_ST__ST_PC psDest, STg2_UT_ST__ST_CPC psARG )
{
    TgPARAM_CHECK((nullptr != psDest) && (nullptr != psARG));
    tgCM_UT_ST__ST__Init( psDest );
    tgCM_UT_ST__ST__ST_Assign( psDest, psARG );
}


/* ---- tgCM_UT_ST__ST__SO_Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SO_Init( STg2_UT_ST__ST_PC psDest, STg2_UT_ST__ST_CPC psARG, TgRSIZE_C uiARG_Offset )
{
    TgPARAM_CHECK((nullptr != psDest) && (nullptr != psARG));
    tgCM_UT_ST__ST__Init( psDest );
    tgCM_UT_ST__ST__SO_Assign( psDest, psARG, uiARG_Offset );
}


/* ---- tgCM_UT_ST__ST__SF_Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SF_Init( STg2_UT_ST__ST_PC psDest, STg2_UT_ST__ST_CPC psARG, TgRSIZE_C uiARG_Offset, TgRSIZE_C uiMaxRead )
{
    TgPARAM_CHECK((nullptr != psDest) && (nullptr != psARG));
    tgCM_UT_ST__ST__Init( psDest );
    tgCM_UT_ST__ST__SF_Assign( psDest, psARG, uiARG_Offset, uiMaxRead );
}


/* ---- tgCM_UT_ST__ST__SZ_Assign ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SZ_Assign( STg2_UT_ST__ST_PC psDest, TgCHAR_U8_CPC mbzARG )
{
    STg2_UT_ST__ST                    sSrc;

    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzARG));
    sSrc.m_uszSrc = mbzARG;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG, KTgMAX_RSIZE );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    tgCM_UT_ST__ST__SF_Assign( psDest, &sSrc, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__SN_Assign ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SN_Assign( STg2_UT_ST__ST_PC psDest, TgCHAR_U8_CPC mbzARG, TgRSIZE_C nbyMaxARG )
{
    STg2_UT_ST__ST                    sSrc;

    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzARG));
    sSrc.m_uszSrc = mbzARG;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG, nbyMaxARG );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    tgCM_UT_ST__ST__SF_Assign( psDest, &sSrc, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__PT_Assign ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__PT_Assign( STg2_UT_ST__ST_PC psDest, TgCHAR_U8_CPC mbzStart, TgCHAR_U8_CPC mbzEnd )
{
    STg2_UT_ST__ST                    sSrc;

    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzStart) && (nullptr != mbzEnd));

    if (!(mbzStart <= mbzEnd))
    {
        return;
    };

    TgPARAM_CHECK((TgRSIZE)(mbzEnd - mbzStart) < KTgMAX_RSIZE);
    sSrc.m_uszSrc = mbzStart;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzStart, (TgRSIZE)(mbzEnd - mbzStart) );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    tgCM_UT_ST__ST__SF_Assign( psDest, &sSrc, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__ST_Assign ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__ST_Assign( STg2_UT_ST__ST_PC psDest, STg2_UT_ST__ST_CPC psARG )
{
    tgCM_UT_ST__ST__SF_Assign( psDest, psARG, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__SO_Assign ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SO_Assign( STg2_UT_ST__ST_PC psDest, STg2_UT_ST__ST_CPC psARG, TgRSIZE_C uiARG_Offset )
{
    tgCM_UT_ST__ST__SF_Assign( psDest, psARG, uiARG_Offset, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__SZ_Append ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SZ_Append( STg2_UT_ST__ST_PC psDest, TgCHAR_U8_CPC mbzARG )
{
    STg2_UT_ST__ST                    sSrc;

    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzARG));
    sSrc.m_uszSrc = mbzARG;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG, KTgMAX_RSIZE );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    tgCM_UT_ST__ST__SF_Append( psDest, &sSrc, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__SN_Append ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SN_Append( STg2_UT_ST__ST_PC psDest, TgCHAR_U8_CPC mbzARG, TgRSIZE_C nbyMaxARG )
{
    STg2_UT_ST__ST                    sSrc;

    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzARG));
    sSrc.m_uszSrc = mbzARG;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG, nbyMaxARG );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    tgCM_UT_ST__ST__SF_Append( psDest, &sSrc, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__PT_Append ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__PT_Append( STg2_UT_ST__ST_PC psDest, TgCHAR_U8_CPC mbzStart, TgCHAR_U8_CPC mbzEnd )
{
    STg2_UT_ST__ST                    sSrc;

    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzStart) && (nullptr != mbzEnd));

    if (!(mbzStart <= mbzEnd))
    {
        return;
    };

    TgPARAM_CHECK((TgRSIZE)(mbzEnd - mbzStart) < KTgMAX_RSIZE);
    sSrc.m_uszSrc = mbzStart;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzStart, (TgRSIZE)(mbzEnd - mbzStart) );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    tgCM_UT_ST__ST__SF_Append( psDest, &sSrc, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__ST_Append ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__ST_Append( STg2_UT_ST__ST_PC psDest, STg2_UT_ST__ST_CPC psARG )
{
    tgCM_UT_ST__ST__SF_Append( psDest, psARG, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__SO_Append ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SO_Append( STg2_UT_ST__ST_PC psDest, STg2_UT_ST__ST_CPC psARG, TgRSIZE_C uiARG_Offset )
{
    tgCM_UT_ST__ST__SF_Append( psDest, psARG, uiARG_Offset, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__SZ_Insert ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SZ_Insert( STg2_UT_ST__ST_PC psDest, TgRSIZE_C uiIndex, TgCHAR_U8_CPC mbzARG )
{
    STg2_UT_ST__ST                    sSrc;

    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzARG));
    sSrc.m_uszSrc = mbzARG;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG, KTgMAX_RSIZE );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    tgCM_UT_ST__ST__SF_Insert( psDest, uiIndex, &sSrc, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__SN_Insert ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SN_Insert( STg2_UT_ST__ST_PC psDest, TgRSIZE_C uiIndex, TgCHAR_U8_CPC mbzARG, TgRSIZE_C nbyMaxARG )
{
    STg2_UT_ST__ST                    sSrc;

    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzARG));
    sSrc.m_uszSrc = mbzARG;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG, nbyMaxARG );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    tgCM_UT_ST__ST__SF_Insert( psDest, uiIndex, &sSrc, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__PT_Insert ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__PT_Insert( STg2_UT_ST__ST_PC psDest, TgRSIZE_C uiIndex, TgCHAR_U8_CPC mbzStart, TgCHAR_U8_CPC mbzEnd )
{
    STg2_UT_ST__ST                    sSrc;

    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzStart) && (nullptr != mbzEnd));

    if (!(mbzStart <= mbzEnd))
    {
        return;
    };

    TgPARAM_CHECK((TgRSIZE)(mbzEnd - mbzStart) < KTgMAX_RSIZE);
    sSrc.m_uszSrc = mbzStart;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzStart, (TgRSIZE)(mbzEnd - mbzStart) );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    tgCM_UT_ST__ST__SF_Insert( psDest, uiIndex, &sSrc, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__ST_Insert ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__ST_Insert( STg2_UT_ST__ST_PC psDest, TgRSIZE_C uiIndex, STg2_UT_ST__ST_CPC psARG )
{
    tgCM_UT_ST__ST__SF_Insert( psDest, uiIndex, psARG, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__SO_Insert ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SO_Insert( STg2_UT_ST__ST_PC psDest, TgRSIZE_C uiIndex, STg2_UT_ST__ST_CPC psARG, TgRSIZE_C uiARG_Offset )
{
    tgCM_UT_ST__ST__SF_Insert( psDest, uiIndex, psARG, uiARG_Offset, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__SF_Insert ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SF_Insert( STg2_UT_ST__ST_PC psDest, TgRSIZE_C uiIndex, STg2_UT_ST__ST_CPC psARG, TgRSIZE_C uiARG_Offset, TgRSIZE_C uiMaxRead )
{
    tgCM_UT_ST__ST__SF_Replace( psDest, uiIndex, uiIndex, psARG, uiARG_Offset, uiMaxRead );
}


/* ---- tgCM_UT_ST__ST__SZ_Replace ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SZ_Replace( STg2_UT_ST__ST_PC psDest, TgRSIZE_C uiStart, TgRSIZE_C uiEnd, TgCHAR_U8_CPC mbzARG )
{
    STg2_UT_ST__ST                    sSrc;

    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzARG));

    if (!(uiStart <= uiEnd))
    {
        return;
    };

    sSrc.m_uszSrc = mbzARG;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG, KTgMAX_RSIZE );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    tgCM_UT_ST__ST__SF_Replace( psDest, uiStart, uiEnd, &sSrc, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__SN_Replace ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SN_Replace( STg2_UT_ST__ST_PC psDest, TgRSIZE_C uiStart, TgRSIZE_C uiEnd, TgCHAR_U8_CPC mbzARG, TgRSIZE_C nbyMaxARG )
{
    STg2_UT_ST__ST                    sSrc;

    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzARG));

    if (!(uiStart <= uiEnd))
    {
        return;
    };

    sSrc.m_uszSrc = mbzARG;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG, nbyMaxARG );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    tgCM_UT_ST__ST__SF_Replace( psDest, uiStart, uiEnd, &sSrc, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__PT_Replace ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__PT_Replace( STg2_UT_ST__ST_PC psDest, TgRSIZE_C uiStart, TgRSIZE_C uiEnd, TgCHAR_U8_CPC mbzStart, TgCHAR_U8_CPC mbzEnd )
{
    STg2_UT_ST__ST                    sSrc;

    TgPARAM_CHECK((nullptr != psDest) && (nullptr != mbzStart) && (nullptr != mbzEnd));

    if (!(mbzStart <= mbzEnd))
    {
        return;
    };

    TgPARAM_CHECK((TgRSIZE)(mbzEnd - mbzStart) < KTgMAX_RSIZE);
    sSrc.m_uszSrc = mbzStart;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzStart, (TgRSIZE)(mbzEnd - mbzStart) );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    tgCM_UT_ST__ST__SF_Replace( psDest, uiStart, uiEnd, &sSrc, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__ST_Replace ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__ST_Replace( STg2_UT_ST__ST_PC psDest, TgRSIZE_C uiStart, TgRSIZE_C uiEnd, STg2_UT_ST__ST_CPC psARG )
{
    tgCM_UT_ST__ST__SF_Replace( psDest, uiStart, uiEnd, psARG, 0, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__SO_Replace ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__SO_Replace( STg2_UT_ST__ST_PC psDest, TgRSIZE_C uiStart, TgRSIZE_C uiEnd, STg2_UT_ST__ST_CPC psARG, TgRSIZE_C uiARG_Offset )
{
    tgCM_UT_ST__ST__SF_Replace( psDest, uiStart, uiEnd, psARG, uiARG_Offset, KTgMAX_RSIZE );
}


/* ---- tgCM_UT_ST__ST__Clear ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__Clear( STg2_UT_ST__ST_PC psDest )
{
    if (psDest->m_nbyReserve > KTgSTRING_STATIC_BUFFER_SIZE)
    {
        TgFREE_POOL( psDest->m_uszDest );
        psDest->m_nbyReserve = KTgSTRING_STATIC_BUFFER_SIZE;
    };

    psDest->m_nbyBuffer = 0;
    psDest->m_ambBuffer[0] = '\0';
}


/* ---- tgCM_UT_ST__ST__To_Upper ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__To_Upper( STg2_UT_ST__ST_PC psDest )
{
    return (tgCM_UT_ST__ST__Change_Cast_Internal(psDest, true));
}


/* ---- tgCM_UT_ST__ST__To_Lower ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__To_Lower( STg2_UT_ST__ST_PC psDest )
{
    return (tgCM_UT_ST__ST__Change_Cast_Internal(psDest, false));
}


/* ---- tgCM_UT_ST__ST__Query_String --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgCHAR_U8_CP tgCM_UT_ST__ST__Query_String( STg2_UT_ST__ST_CPC psDest )
{
    return (nullptr == psDest ? nullptr : KTgSTRING_STATIC_BUFFER_SIZE < psDest->m_nbyReserve ? psDest->m_uszDest : psDest->m_ambBuffer);
}


/* ---- tgCM_UT_ST__ST__Is_Empty ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCM_UT_ST__ST__Is_Empty( STg2_UT_ST__ST_CPC psDest )
{
    return (0 == psDest->m_nbyBuffer);
}


/* ---- tgCM_UT_ST__ST__Capacity ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgCM_UT_ST__ST__Capacity( STg2_UT_ST__ST_CPC psDest )
{
    return (psDest->m_nbyReserve - 1);
}


/* ---- tgCM_UT_ST__ST__Max_Size ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgCM_UT_ST__ST__Max_Size( TgATTRIBUTE_UNUSED STg2_UT_ST__ST_CPC psDest )
{
    return (KTgMAX_U32 - 1);
}


/* ---- tgCM_UT_ST__ST__Length_U08 ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgCM_UT_ST__ST__Length_U08( STg2_UT_ST__ST_CPC psDest )
{
    return (psDest->m_nbyBuffer);
}


/* ---- tgCM_UT_ST__ST__Length_Count --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__Length_Count( TgRSIZE_P puiLength_Count, STg2_UT_ST__ST_CPC psDest )
{
    return (tgUSZ_Length_Count(puiLength_Count, tgCM_UT_ST__ST__Query_String( psDest ), psDest->m_nbyReserve));
}


/* ---- tgCM_UT_ST__ST__Reserve -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__Reserve( STg2_UT_ST__ST_PC psDest, TgRSIZE_C nbyNew_Size )
{
    if (TgEXPECT_TRUE( nbyNew_Size + 1 > psDest->m_nbyReserve ))
    {
        tgCM_UT_ST__ST__Resize_NCS( psDest, nbyNew_Size, '\0' );
    };
}


/* ---- tgCM_UT_ST__ST__Swap ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__Swap( STg2_UT_ST__ST_PC psARG0, STg2_UT_ST__ST_PC psARG1 )
{
    STg2_UT_ST__ST                      tgTmp;

    tgMM_Copy( &tgTmp, sizeof( STg2_UT_ST__ST ), psARG0, sizeof( STg2_UT_ST__ST ) );
    tgMM_Copy( psARG0, sizeof( STg2_UT_ST__ST ), psARG1, sizeof( STg2_UT_ST__ST ) );
    tgMM_Copy( psARG1, sizeof( STg2_UT_ST__ST ), &tgTmp, sizeof( STg2_UT_ST__ST ) );
}

/* ---- tgCM_UT_ST__ST__Is_Inside ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCM_UT_ST__ST__Is_Inside( STg2_UT_ST__ST_CPC psDest, TgCHAR_U8_CPC mbzARG1 )
{
    return (tgCM_UT_ST__ST__Query_String( psDest ) <= mbzARG1 && mbzARG1 <= tgCM_UT_ST__ST__Query_String( psDest ) + psDest->m_nbyBuffer);
}


/* ---- tgCM_UT_ST__ST__ST_SZ_Compare -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__ST_SZ_Compare( TgSINT_E08_P piCMP, STg2_UT_ST__ST_CPC psARG0, TgCHAR_U8_CPC mbzARG1 )
{
    STg2_UT_ST__ST                    sSrc;

    sSrc.m_uszSrc = mbzARG1;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG1, KTgMAX_RSIZE );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    return (tgCM_UT_ST__ST__SF_SF_Compare( piCMP, psARG0, 0, KTgMAX_RSIZE, &sSrc, 0 ));
}


/* ---- tgCM_UT_ST__ST__ST_SN_Compare -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__ST_SN_Compare( TgSINT_E08_P piCMP, STg2_UT_ST__ST_CPC psARG0, TgCHAR_U8_CPC mbzARG1, TgRSIZE_C nbyARG1 )
{
    STg2_UT_ST__ST                    sSrc;

    sSrc.m_uszSrc = mbzARG1;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG1, nbyARG1 );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    return (tgCM_UT_ST__ST__SF_SF_Compare( piCMP, psARG0, 0, KTgMAX_RSIZE, &sSrc, 0 ));
}


/* ---- tgCM_UT_ST__ST__ST_ST_Compare -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__ST_ST_Compare( TgSINT_E08_P piCMP, STg2_UT_ST__ST_CPC psARG0, STg2_UT_ST__ST_CPC psARG1 )
{
    return (tgCM_UT_ST__ST__SF_SF_Compare( piCMP, psARG0, 0, KTgMAX_RSIZE, psARG1, 0 ));
}


/* ---- tgCM_UT_ST__ST__ST_SF_Compare -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__ST_SF_Compare(
    TgSINT_E08_P piCMP, STg2_UT_ST__ST_CPC psARG0, STg2_UT_ST__ST_CPC psARG1, TgRSIZE_C uiOffset_ARG1, TgRSIZE_C uiMaxRead )
{
    return (tgCM_UT_ST__ST__SF_SF_Compare( piCMP, psARG0, 0, uiMaxRead, psARG1, uiOffset_ARG1 ));
}


/* ---- tgCM_UT_ST__ST__SF_SZ_Compare -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SF_SZ_Compare( TgSINT_E08_P piCMP, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgRSIZE_C uiMaxRead, TgCHAR_U8_CPC mbzARG1 )
{
    STg2_UT_ST__ST                    sSrc;

    sSrc.m_uszSrc = mbzARG1;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG1, KTgMAX_RSIZE );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    return (tgCM_UT_ST__ST__SF_SF_Compare( piCMP, psARG0, uiOffset_ARG0, uiMaxRead, &sSrc, 0 ));
}


/* ---- tgCM_UT_ST__ST__SF_SN_Compare -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SF_SN_Compare(
    TgSINT_E08_P piCMP, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgRSIZE_C uiMaxRead, TgCHAR_U8_CPC mbzARG1, TgRSIZE_C nbyARG )
{
    STg2_UT_ST__ST                    sSrc;

    sSrc.m_uszSrc = mbzARG1;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG1, nbyARG );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    return (tgCM_UT_ST__ST__SF_SF_Compare( piCMP, psARG0, uiOffset_ARG0, uiMaxRead, &sSrc, 0 ));
}


/* ---- tgCM_UT_ST__ST__SF_ST_Compare -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SF_ST_Compare(
    TgSINT_E08_P piCMP, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgRSIZE_C uiMaxRead, STg2_UT_ST__ST_CPC psARG1 )
{
    return (tgCM_UT_ST__ST__SF_SF_Compare( piCMP, psARG0, uiOffset_ARG0, uiMaxRead, psARG1, 0 ));
}


/* ---- tgCM_UT_ST__ST__SF_SF_Compare -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SF_SF_Compare(
    TgSINT_E08_P piCMP, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgRSIZE_C uiMaxRead, STg2_UT_ST__ST_CPC psARG1, TgRSIZE_C uiOffset_ARG1 )
{
    TgCHAR_U8_CP                        mbzARG0, mbzARG1;

    mbzARG0 = tgCM_UT_ST__ST__Query_String( psARG0 );
    mbzARG1 = tgCM_UT_ST__ST__Query_String( psARG1 );

    return (tgUSZ_CompareN( piCMP, mbzARG0, psARG0->m_nbyBuffer, uiOffset_ARG0, mbzARG1, psARG1->m_nbyBuffer, uiOffset_ARG1, uiMaxRead ));
}


/* ---- tgCM_UT_ST__ST__SO_SZ_Find_String ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SZ_Find_String(
    STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgCHAR_U8_CPC mbzARG1 )
{
    STg2_UT_ST__ST                    sSrc;

    sSrc.m_uszSrc = mbzARG1;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG1, KTgMAX_RSIZE );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    return (tgCM_UT_ST__ST__SO_SF_Find_String( psOffset, psARG0, uiOffset_ARG0, &sSrc, 0, KTgMAX_RSIZE ));
}


/* ---- tgCM_UT_ST__ST__SO_SN_Find_String ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SN_Find_String(
    STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgCHAR_U8_CPC mbzARG1, TgRSIZE_C nbyARG )
{
    STg2_UT_ST__ST                    sSrc;

    sSrc.m_uszSrc = mbzARG1;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG1, nbyARG );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    return (tgCM_UT_ST__ST__SO_SF_Find_String( psOffset, psARG0, uiOffset_ARG0, &sSrc, 0, KTgMAX_RSIZE ));
}


/* ---- tgCM_UT_ST__ST__SO_ST_Find_String ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_ST_Find_String( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, STg2_UT_ST__ST_CPC psARG1 )
{
    return (tgCM_UT_ST__ST__SO_SF_Find_String( psOffset, psARG0, uiOffset_ARG0, psARG1, 0, KTgMAX_RSIZE ));
}


/* ---- tgCM_UT_ST__ST__SO_SF_Find_String ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SF_Find_String(
    STg1_Text_Length_PC OUT0, STg2_UT_ST__ST_CPC psARG_0, TgRSIZE_C uiARG_0_Offset, STg2_UT_ST__ST_CPC psARG_1, TgRSIZE_C uiARG_1_Offset, TgRSIZE_C uiMaxRead )
{
    return (tgCM_UT_ST__ST__SO_SF_Find_String_Internal( OUT0, psARG_0, uiARG_0_Offset, psARG_1, uiARG_1_Offset, uiMaxRead, false ));
}


/* ---- tgCM_UT_ST__ST__SO_SZ_Find_Set ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SZ_Find_Set( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgCHAR_U8_CPC mbzARG1 )
{
    return (tgCM_UT_ST__ST__SO_SN_Find_Set( psOffset, psARG0, uiOffset_ARG0, mbzARG1, KTgMAX_RSIZE ));
}


/* ---- tgCM_UT_ST__ST__SO_SN_Find_Set ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SN_Find_Set( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG_0, TgRSIZE_C uiARG_0_Offset, TgCHAR_U8_CPC mbzARG_1, TgRSIZE_C nbyARG_1 )
{
    return (tgCM_UT_ST__ST__SO_SN_Find_Set_Internal( psOffset, psARG_0, uiARG_0_Offset, mbzARG_1, nbyARG_1, true, false ));
}


/* ---- tgCM_UT_ST__ST__SO_ST_Find_Set ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_ST_Find_Set( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, STg2_UT_ST__ST_CPC psARG1 )
{
    return (tgCM_UT_ST__ST__SO_SN_Find_Set( psOffset, psARG0, uiOffset_ARG0, tgCM_UT_ST__ST__Query_String( psARG1 ), psARG1->m_nbyBuffer ));
}


/* ---- tgCM_UT_ST__ST__SO_SZ_Find_Not_Set --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SZ_Find_Not_Set( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgCHAR_U8_CPC mbzARG1 )
{
    return (tgCM_UT_ST__ST__SO_SN_Find_Not_Set( psOffset, psARG0, uiOffset_ARG0, mbzARG1, KTgMAX_RSIZE ));
}


/* ---- tgCM_UT_ST__ST__SO_SN_Find_Not_Set --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SN_Find_Not_Set( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG_0, TgRSIZE_C uiARG_0_Offset, TgCHAR_U8_CPC mbzARG_1, TgRSIZE_C nbyARG_1)
{
    return (tgCM_UT_ST__ST__SO_SN_Find_Set_Internal( psOffset, psARG_0, uiARG_0_Offset, mbzARG_1, nbyARG_1, false, false ));
}


/* ---- tgCM_UT_ST__ST__SO_ST_Find_Not_Set --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_ST_Find_Not_Set( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, STg2_UT_ST__ST_CPC psARG1 )
{
    return (tgCM_UT_ST__ST__SO_SN_Find_Not_Set( psOffset, psARG0, uiOffset_ARG0, tgCM_UT_ST__ST__Query_String( psARG1 ), psARG1->m_nbyBuffer ));
}


/* ---- tgCM_UT_ST__ST__SO_ST_RFind_String --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_ST_RFind_String( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, STg2_UT_ST__ST_CPC psARG1 )
{
    return (tgCM_UT_ST__ST__SO_SF_RFind_String( psOffset, psARG0, uiOffset_ARG0, psARG1, 0, KTgMAX_RSIZE ));
}


/* ---- tgCM_UTS_SO_SF_RFind_String ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SF_RFind_String(
    STg1_Text_Length_PC OUT0, STg2_UT_ST__ST_CPC psARG_0, TgRSIZE_C uiARG_0_Offset, STg2_UT_ST__ST_CPC psARG_1, TgRSIZE_C uiARG_1_Offset, TgRSIZE_C uiMaxRead )
{
    return (tgCM_UT_ST__ST__SO_SF_Find_String_Internal( OUT0, psARG_0, uiARG_0_Offset, psARG_1, uiARG_1_Offset, uiMaxRead, true ));
}


/* ---- tgCM_UT_ST__ST__SO_SZ_RFind_String --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SZ_RFind_String( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgCHAR_U8_CPC mbzARG1 )
{
    STg2_UT_ST__ST                    sSrc;

    sSrc.m_uszSrc = mbzARG1;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG1, KTgMAX_RSIZE );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    return (tgCM_UT_ST__ST__SO_SF_RFind_String( psOffset, psARG0, uiOffset_ARG0, &sSrc, 0, KTgMAX_RSIZE ));
}


/* ---- tgCM_UT_ST__ST__SO_SN_RFind_String --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SN_RFind_String(
    STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgCHAR_U8_CPC mbzARG1, TgRSIZE_C nbyARG1 )
{
    STg2_UT_ST__ST                    sSrc;

    sSrc.m_uszSrc = mbzARG1;
    sSrc.m_nbyBuffer = tgUSZ_Length_U08( mbzARG1, nbyARG1 );
    sSrc.m_nbyReserve = KTgMAX_RSIZE;

    return (tgCM_UT_ST__ST__SO_SF_RFind_String( psOffset, psARG0, uiOffset_ARG0, &sSrc, 0, KTgMAX_RSIZE ));
}


/* ---- tgCM_UT_ST__ST__SO_SZ_RFind_Set ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SZ_RFind_Set( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgCHAR_U8_CPC mbzARG1 )
{
    return (tgCM_UT_ST__ST__SO_SN_RFind_Set( psOffset, psARG0, uiOffset_ARG0, mbzARG1, KTgMAX_RSIZE ));
}


/* ---- tgCM_UT_ST__ST__SO_SN_RFind_Set ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SN_RFind_Set( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG_0, TgRSIZE_C uiARG_0_Offset, TgCHAR_U8_CPC mbzARG_1, TgRSIZE_C nbyARG_1 )
{
    return (tgCM_UT_ST__ST__SO_SN_Find_Set_Internal( psOffset, psARG_0, uiARG_0_Offset, mbzARG_1, nbyARG_1, true, true ));

}

/* ---- tgCM_UT_ST__ST__SO_ST_RFind_Set ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_ST_RFind_Set( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, STg2_UT_ST__ST_CPC psARG1 )
{
    return (tgCM_UT_ST__ST__SO_SN_RFind_Set( psOffset, psARG0, uiOffset_ARG0, tgCM_UT_ST__ST__Query_String( psARG1 ), psARG1->m_nbyBuffer ));
}


/* ---- tgCM_UT_ST__ST__SO_SZ_RFind_Not_Set -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SZ_RFind_Not_Set( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgCHAR_U8_CPC mbzARG1 )
{
    return (tgCM_UT_ST__ST__SO_SN_RFind_Not_Set( psOffset, psARG0, uiOffset_ARG0, mbzARG1, KTgMAX_RSIZE ));
}


/* ---- tgCM_UT_ST__ST__SO_SN_RFind_Not_Set -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_SN_RFind_Not_Set( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, TgCHAR_U8_CPC mbzARG1, TgRSIZE_C nbyARG1 )
{
    return (tgCM_UT_ST__ST__SO_SN_Find_Set_Internal( psOffset, psARG0, uiOffset_ARG0, mbzARG1, nbyARG1, false, true ));
}


/* ---- tgCM_UT_ST__ST__SO_ST_RFind_Not_Set -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__ST__SO_ST_RFind_Not_Set( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG0, TgRSIZE_C uiOffset_ARG0, STg2_UT_ST__ST_CPC psARG1 )
{
    return (tgCM_UT_ST__ST__SO_SN_RFind_Not_Set( psOffset, psARG0, uiOffset_ARG0, tgCM_UT_ST__ST__Query_String( psARG1 ), psARG1->m_nbyBuffer ));
}


/* ---- tgCM_UT_ST__ST__Trim_Start_Set ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__Trim_Start_Set( STg2_UT_ST__ST_PC psDest, TgCHAR_U8_CPC mbzARG1, TgRSIZE_C nbyARG1 )
{
    STg1_Text_Length                    sOffset;

    if (TgFAILED(tgCM_UT_ST__ST__SO_SN_Find_Not_Set( &sOffset, psDest, 0, mbzARG1, nbyARG1 )))
    {
        tgCM_UT_ST__ST__Clear( psDest );
    }
    else
    {
        tgCM_UT_ST__ST__Erase( psDest, 0, sOffset.m_nuiCharacters );
    };
}


/* ---- tgCM_UT_ST__ST__Trim_End_Set --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__ST__Trim_End_Set( STg2_UT_ST__ST_PC psDest, TgCHAR_U8_CPC mbzARG1, TgRSIZE_C nbyARG1 )
{
    STg1_Text_Length                    sOffset;

    if (TgFAILED(tgCM_UT_ST__ST__SO_SN_RFind_Not_Set( &sOffset, psDest, 0, mbzARG1, nbyARG1 )))
    {
        tgCM_UT_ST__ST__Clear( psDest );
    }
    else
    {
        tgCM_UT_ST__ST__Erase( psDest, sOffset.m_nuiCharacters + 1, psDest->m_nbyBuffer - sOffset.m_nbyCharacters );
    };
}


/* =============================================================================================================================================================================== */
#endif
