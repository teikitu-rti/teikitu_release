/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - System [GPU] [Context] [Host].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU__Host__Init ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU__Host__Init( TgVOID )
{
    TgKN_GPU_TX_CBE_ID                  sID_TX_CBE;
    TgKN_GPU_TX_IMG_ID                  sID_TX_IMG;
    TgKN_GPU_TX_VOL_ID                  sID_TX_VOL;

    tgMM_Set_U08_0x00( &g_sKN_GPU_CXT_HOST, sizeof( STg2_KN_GPU_CXT_HOST ) );
    tgKN_GPU_CXT_HOST_ID_Init( &g_sKN_GPU_CXT_HOST.m_tiCXT_HOST_S, 0 );

    tgMM_Set_U08_0x00( &g_sKN_GPU_CXT_HOST_EXT, sizeof( STg2_KN_GPU_CXT_HOST_EXTN ) );
    tgKN_GPU_CXT_HOST_EXTN_ID_Init( &g_sKN_GPU_CXT_HOST_EXT.m_tiCXT_HOST_EXT_S, 0 );

    /* Initialize the resource ID. */
    sID_TX_CBE.m_uiIndex = sID_TX_IMG.m_uiIndex = sID_TX_VOL.m_uiIndex = (1 << KTgKN_GPU_RS_BIT__MAX_INDEX) - 1;
    sID_TX_CBE.m_uiK = sID_TX_IMG.m_uiK = sID_TX_VOL.m_uiK = 128 & ((1 << KTgKN_GPU_RS_BIT__SALT) - 1);
    sID_TX_CBE.m_uiLoad = sID_TX_IMG.m_uiLoad = sID_TX_VOL.m_uiLoad = 1;
    sID_TX_CBE.m_uiFree = sID_TX_IMG.m_uiFree = sID_TX_VOL.m_uiFree = 0;
    sID_TX_CBE.m_uiRef = sID_TX_IMG.m_uiRef = sID_TX_VOL.m_uiRef = 1;

    /* Create a set of standard colour textures in the 709 colour space. */
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Black_709 = sID_TX_IMG; --sID_TX_IMG.m_uiIndex; ++sID_TX_IMG.m_uiK;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_White_709 = sID_TX_IMG; --sID_TX_IMG.m_uiIndex; ++sID_TX_IMG.m_uiK;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Red_709 = sID_TX_IMG; --sID_TX_IMG.m_uiIndex; ++sID_TX_IMG.m_uiK;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Green_709 = sID_TX_IMG; --sID_TX_IMG.m_uiIndex; ++sID_TX_IMG.m_uiK;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Blue_709 = sID_TX_IMG; --sID_TX_IMG.m_uiIndex; ++sID_TX_IMG.m_uiK;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Yellow_709 = sID_TX_IMG; --sID_TX_IMG.m_uiIndex; ++sID_TX_IMG.m_uiK;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Magenta_709 = sID_TX_IMG; --sID_TX_IMG.m_uiIndex; ++sID_TX_IMG.m_uiK;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Cyan_709 = sID_TX_IMG; --sID_TX_IMG.m_uiIndex; ++sID_TX_IMG.m_uiK;

    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_VOL_Black_709 = sID_TX_VOL; --sID_TX_VOL.m_uiIndex; ++sID_TX_VOL.m_uiK;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_VOL_White_709 = sID_TX_VOL; --sID_TX_VOL.m_uiIndex; ++sID_TX_VOL.m_uiK;

    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_CBE_Black_709 = sID_TX_CBE; --sID_TX_CBE.m_uiIndex; ++sID_TX_CBE.m_uiK;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_CBE_White_709 = sID_TX_CBE; --sID_TX_CBE.m_uiIndex; ++sID_TX_CBE.m_uiK;

    if (TgFAILED(tgKN_GPU_EXT__Host__Init()))
    {
        tgMM_Set_U08_0x00( &g_sKN_GPU_CXT_HOST, sizeof( STg2_KN_GPU_CXT_HOST ) );
        tgMM_Set_U08_0x00( &g_sKN_GPU_CXT_HOST_EXT, sizeof( STg2_KN_GPU_CXT_HOST_EXTN ) );
        tgKN_GPU_CXT_HOST_ID_Invalidate( &g_sKN_GPU_CXT_HOST.m_tiCXT_HOST_S );
        tgKN_GPU_CXT_HOST_EXTN_ID_Invalidate( &g_sKN_GPU_CXT_HOST_EXT.m_tiCXT_HOST_EXT_S );
        return (KTgE_FAIL);
    };

    return (KTgS_OK);
}


/* ---- tgKN_GPU__Host__Free ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__Host__Free( TgVOID )
{
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_DEVC_CONTEXT; ++uiIndex)
    {
        TgERROR(g_sKN_GPU_CXT_HOST.m_atiCXT_DEVC[uiIndex].m_uiKI == KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI);
    };

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_EXEC_CONTEXT; ++uiIndex)
    {
        TgERROR(g_sKN_GPU_CXT_HOST.m_atiCXT_EXEC[uiIndex].m_uiKI == KTgKN_GPU_CXT_EXEC_ID__INVALID.m_uiKI);
    };

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_SWAP_CONTEXT; ++uiIndex)
    {
        TgERROR(g_sKN_GPU_CXT_HOST.m_atiCXT_SWAP[uiIndex].m_uiKI == KTgKN_GPU_CXT_SWAP_ID__INVALID.m_uiKI);
    };

    tgKN_GPU_EXT__Host__Free();

    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_CBE_White_709 = KTgKN_GPU_TX_CBE_ID__INVALID;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_CBE_Black_709 = KTgKN_GPU_TX_CBE_ID__INVALID;

    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_VOL_White_709 = KTgKN_GPU_TX_VOL_ID__INVALID;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_VOL_Black_709 = KTgKN_GPU_TX_VOL_ID__INVALID;

    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Cyan_709 = KTgKN_GPU_TX_IMG_ID__INVALID;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Magenta_709 = KTgKN_GPU_TX_IMG_ID__INVALID;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Yellow_709 = KTgKN_GPU_TX_IMG_ID__INVALID;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Blue_709 = KTgKN_GPU_TX_IMG_ID__INVALID;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Green_709 = KTgKN_GPU_TX_IMG_ID__INVALID;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Red_709 = KTgKN_GPU_TX_IMG_ID__INVALID;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_White_709 = KTgKN_GPU_TX_IMG_ID__INVALID;
    g_sKN_GPU_CXT_HOST_EXT.m_sID_TX_IMG_Black_709 = KTgKN_GPU_TX_IMG_ID__INVALID;

    tgMM_Set_U08_0x00( &g_sKN_GPU_CXT_HOST_EXT, sizeof( STg2_KN_GPU_CXT_HOST_EXTN ) );
    tgKN_GPU_CXT_HOST_EXTN_ID_Invalidate( &g_sKN_GPU_CXT_HOST_EXT.m_tiCXT_HOST_EXT_S );

    tgMM_Set_U08_0x00( &g_sKN_GPU_CXT_HOST, sizeof( STg2_KN_GPU_CXT_HOST ) );
    tgKN_GPU_CXT_HOST_ID_Invalidate( &g_sKN_GPU_CXT_HOST.m_tiCXT_HOST_S );
}


