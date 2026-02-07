/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - System [Context] [DEVC].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7, Claude 4.0
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__Device__Init ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Device__Init( TgKN_GPU_CXT_DEVC_ID_C tiCXT_DEVC )
{
    STg2_KN_GPU_VLKN_CXT_DEVC_PC        psEXT_CXT_DEVC = g_asKN_GPU_EXT_CXT_DEVC + tiCXT_DEVC.m_uiI;
    STg2_KN_GPU_CXT_DEVC_PC             psCXT_DEVC = g_asKN_GPU_CXT_DEVC + tiCXT_DEVC.m_uiI;

    TgPARAM_CHECK_INDEX(tiCXT_DEVC.m_uiI, g_asKN_GPU_EXT_CXT_DEVC);
    TgPARAM_CHECK( tgKN_GPU_CXT_DEVC_ID_Is_Equal( &(g_asKN_GPU_CXT_DEVC[tiCXT_DEVC.m_uiI].m_tiCXT_DEVC_S), tiCXT_DEVC ) );

    tgMM_Set_U08_0x00( psEXT_CXT_DEVC, sizeof( STg2_KN_GPU_CXT_DEVC ) );
    psEXT_CXT_DEVC->m_tiID = tiCXT_DEVC;
    psEXT_CXT_DEVC->m_idxCXT_HOST_Physical_Device = psCXT_DEVC->m_idxCXT_HOST_Physical_Device;

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Device__Free ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Device__Free( TgKN_GPU_CXT_DEVC_ID_C tiCXT_DEVC )
{
    STg2_KN_GPU_VLKN_CXT_DEVC_PC        psEXT_CXT_DEVC = g_asKN_GPU_EXT_CXT_DEVC + tiCXT_DEVC.m_uiI;
    STg2_KN_GPU_CXT_DEVC_PC             psCXT_DEVC = g_asKN_GPU_CXT_DEVC + tiCXT_DEVC.m_uiI;

    TgPARAM_CHECK_INDEX(tiCXT_DEVC.m_uiI, g_asKN_GPU_EXT_CXT_DEVC);

    //TgVERIFY(g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device[psCXT_DEVC->m_idxCXT_HOST_Physical_Device].m_tiID_DEVC.m_uiKI != KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI);
    //TgVERIFY(g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device[psCXT_DEVC->m_idxCXT_HOST_Physical_Device].m_tiID_DEVC.m_uiKI == tiCXT_DEVC.m_uiKI);

    g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Physical_Device[psCXT_DEVC->m_idxCXT_HOST_Physical_Device].m_tiID_DEVC.m_uiKI = KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI;

    tgMM_Set_U08_0x00( psEXT_CXT_DEVC, sizeof( STg2_KN_GPU_VLKN_CXT_DEVC ) );
    psEXT_CXT_DEVC->m_tiID = KTgKN_GPU_CXT_DEVC_ID__INVALID;
}
