/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Event MGR.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_EVENT_MGR_INL)
#define TGS_COMMON_EVENT_MGR_INL
#pragma once


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Inline Functions */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgEM_TB_Set_Paused ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgEM_TB_Set_Paused( STg2_EM_TB_PCU psTB, TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &psTB->m_bfFlags, 0, bFlag );
}


/* ---- tgEM_TB_Set_Active ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgEM_TB_Set_Active( STg2_EM_TB_PCU psTB, TgBOOL_C bFlag )
{
    tgBF_Set_Flag_U32( &psTB->m_bfFlags, 1, bFlag );
}


/* ---- tgEM_TB_Is_Paused -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgEM_TB_Is_Paused( STg2_EM_TB_CPCU psTB )
{
    return (tgBF_Test_Flag_U32( &psTB->m_bfFlags, 0 ) );
}


/* ---- tgEM_TB_Is_Paused -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgEM_TB_Is_Active( STg2_EM_TB_CPCU psTB )
{
    return (tgBF_Test_Flag_U32( &psTB->m_bfFlags, 1 ) );
}


/* ---- tgEM_TE_FRM_Lock --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgEM_TE_FRM_Lock( TgEM_TE_FRM_ID tiTE, TgUINT_E32_C uiPool, TgUINT_E32_C uiIndex )
{
    TgPARAM_CHECK(uiIndex < KTgEM_NUM_TE_IN_POOL);
    TgPARAM_CHECK(uiPool < KTgEM_MAX_TE_FRM_POOL);

    tgCM_UT_LF__SN__Lock_Spin( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );

    /* Time lines are only valid for the period for which they have a valid id */

    if ((nullptr == g_apsEM_TE_FRM[uiPool]) || (tiTE.m_uiKI !=  g_apsEM_TE_FRM[uiPool]->m_atiEM_TE_FRM_NoSingleton[uiIndex].m_uiKI ))
    {
        tgCM_UT_LF__SN__Signal( &g_asEM_TE_FRM_Data_Lock[uiPool].m_sLock );
        return (KTgE_FAIL);
    };

    return (KTgS_OK);
}


/* ---- tgEM_TE_SEC_Lock --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgEM_TE_SEC_Lock( TgEM_TE_SEC_ID tiTE, TgUINT_E32_C uiPool, TgUINT_E32_C uiIndex )
{
    TgPARAM_CHECK(uiIndex < KTgEM_NUM_TE_IN_POOL);
    TgPARAM_CHECK(uiPool < KTgEM_MAX_TE_SEC_POOL);

    tgCM_UT_LF__SN__Lock_Spin( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );

    /* Time lines are only valid for the period for which they have a valid id */
    if ((nullptr == g_apsEM_TE_SEC[uiPool]) || (tiTE.m_uiKI !=  g_apsEM_TE_SEC[uiPool]->m_atiEM_TE_SEC_NoSingleton[uiIndex].m_uiKI ))
    {
        tgCM_UT_LF__SN__Signal( &g_asEM_TE_SEC_Data_Lock[uiPool].m_sLock );
        return (KTgE_FAIL);
    };

    return (KTgS_OK);
}


/* =============================================================================================================================================================================== */
#endif
