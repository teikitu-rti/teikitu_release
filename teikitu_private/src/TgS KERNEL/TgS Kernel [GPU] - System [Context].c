/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - System [Context].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgBOOL
tgKN_GPU__Host__Is_Valid_For_Contexts_Init( TgVOID );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_Select_Context__Init_From_Config -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Select_Context__Init_From_Config( TgATTRIBUTE_UNUSED STg2_KN_GPU_Select_PCU psSelect )
{
    /* #IMPLEMENT */
    return (KTgS_OK);
}


/* ---- tgKN_GPU_Select_Context__Init_From_Enumeration --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Select_Context__Init_From_Enumeration( TgATTRIBUTE_UNUSED STg2_KN_GPU_Select_PCU psSelect )
{
    /* #IMPLEMENT */
    return (KTgS_OK);
}


/* ---- tgKN_GPU_Select_Context__Validate ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Select_Context__Validate( STg2_KN_GPU_Select_CPCU psSelect )
{
    TgRSIZE                             uiIndex;

    tgCM_UT_LF__RW__Enter_Read_Spin_Block( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
    for (uiIndex = 0; uiIndex < psSelect->m_nuiPhysical_Device; ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device <= psSelect->m_uiEnumeration_Physical_Device_Index[uiIndex])
        {
            tgCM_UT_LF__RW__Exit_Read( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
            return (KTgE_FAIL);
        };
    }

    //if (psSelect->m_uiOutput_Index >= g_sKN_GPU_CXT_HOST.m_asKN_GPU_Physical_Device[psSelect->m_idxCXT_HOST_Physical_Device].m_nuiOutput)
    //{
    //    return (KTgE_FAIL);
    //};

    tgCM_UT_LF__RW__Exit_Read( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_Contexts__Init -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Contexts__Init( STg2_KN_GPU_Init_Result_PCU psResult, STg2_KN_GPU_Select_CPCU psSelect )
{
    TgRSIZE                             uiIndex;

    /* Validate the selection parameter and the host system. */

    if (!tgKN_GPU_Select_Context__Validate( psSelect ))
    {
        return (KTgE_FAIL);
    };

    tgCM_UT_LF__RW__Enter_Write_Spin_Block(&g_sKN_GPU_CXT_HOST.m_sLock.m_sLock);

    if (!tgKN_GPU__Host__Is_Valid_For_Contexts_Init())
    {
        tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
        return (KTgE_FAIL);
    };

    /* Check to make sure that there are no existing contexts that have been initialized (i.e. unpaired calls to init). */

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_DEVC_CONTEXT; ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCXT_DEVC[uiIndex].m_uiKI != KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI)
        {
            tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
            return (KTgE_FAIL);
        };
    };

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_EXEC_CONTEXT; ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCXT_EXEC[uiIndex].m_uiKI != KTgKN_GPU_CXT_EXEC_ID__INVALID.m_uiKI)
        {
            tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
            return (KTgE_FAIL);
        };
    };

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiIndex].m_uiKI != KTgKN_GPU_CXT_SWAP_ID__INVALID.m_uiKI)
        {
            tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
            return (KTgE_FAIL);
        };
    };

    /* Create the contexts */

    for (uiIndex = 0; uiIndex < psSelect->m_nuiPhysical_Device; ++uiIndex)
    {
        if (TgFAILED(tgKN_GPU__Device__Init( psResult, psSelect, uiIndex )))
        {
            tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
            tgKN_GPU_Contexts__Free();
            return (KTgE_FAIL);
        };
    };

    tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
    return (KTgS_OK);
}


/* ---- tgKN_GPU_Contexts__Free -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_Contexts__Free( TgVOID )
{
    TgRSIZE                             uiIndex;

    /* Delete the contexts */

    tgCM_UT_LF__RW__Enter_Write_Spin_Block( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiIndex].m_uiKI != KTgKN_GPU_CXT_SWAP_ID__INVALID.m_uiKI)
        {
            tgKN_GPU__SwapChain__Free( g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiIndex] );
        };
    };

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_EXEC_CONTEXT; ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCXT_EXEC[uiIndex].m_uiKI != KTgKN_GPU_CXT_EXEC_ID__INVALID.m_uiKI)
        {
            tgKN_GPU__Execute__Free( g_sKN_GPU_CXT_HOST.m_atiCXT_EXEC[uiIndex] );
        };
    };

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_DEVC_CONTEXT; ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCXT_DEVC[uiIndex].m_uiKI != KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI)
        {
            tgKN_GPU__Device__Free( g_sKN_GPU_CXT_HOST.m_atiCXT_DEVC[uiIndex] );
        };
    };

    tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU__Host__Is_Valid_For_Contexts_Init ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL tgKN_GPU__Host__Is_Valid_For_Contexts_Init( TgVOID )
{
    if (!tgKN_GPU_CXT_HOST_ID_Fetch_And_Is_Valid( nullptr, &g_sKN_GPU_CXT_HOST.m_tiCXT_HOST_S ))
    {
        return (false);
    };

    if (!tgKN_GPU_CXT_HOST_EXTN_ID_Fetch_And_Is_Valid( nullptr, &g_sKN_GPU_CXT_HOST_EXTN.m_tiCXT_HOST_EXT_S ))
    {
        return (false);
    };

    if (g_sKN_GPU_CXT_HOST.m_atiCXT_DEVC[0].m_uiKI != KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI)
    {
        return (false);
    };

    if (g_sKN_GPU_CXT_HOST.m_atiCXT_EXEC[0].m_uiKI != KTgKN_GPU_CXT_EXEC_ID__INVALID.m_uiKI)
    {
        return (false);
    };

    if (g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[0].m_uiKI != KTgKN_GPU_CXT_SWAP_ID__INVALID.m_uiKI)
    {
        return (false);
    };

    return (true);
}
