/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - System.c
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

/* ---- tgKN_Notify_Start -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_NOTIFY_ID tgKN_Notify_Start( TgKN_FCN_NOTIFY_CALLBACK psFCN, TgUINT_PTR_C uiParam0, TgUINT_F64_C uiMSG )
{
    TgRSIZE                             uiCount;
    TgUINT_MAX                          uiHash;
    TgUINT_E32                          uiFree_Index;

    tgCM_UT_LF__SN__Lock_Spin( &g_sKN_Notfiy_Lock.m_sLock );

    /* Check for a free entry */
    if (KTgMAX_U32 ==  g_uiKN_Notfiy_Free_Index)
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Exceeded number of notification entries." );
        tgCM_UT_LF__SN__Signal( &g_sKN_Notfiy_Lock.m_sLock );
        return (KTgKN_NOTIFY_ID__INVALID);
    };

    /* Check for a possible hash collision */
    uiHash = uiMSG % KTgHASH_MD_SIZE;
    uiCount = 0;
    do
    {
        if (KTgMAX_U32 == g_auiKN_Notify_Index[uiHash] || uiMSG == g_auiKN_Notify_MSG[g_auiKN_Notify_Index[uiHash]])
        {
            break;
        };

        uiHash = (uiHash + 1) % KTgHASH_MD_SIZE;
    }
    while (++uiCount < KTgHASH_MD_SIZE);

    /* Make sure the hash table has not been filled */
    if (KTgHASH_MD_SIZE == uiCount)
    {
        TgCRITICAL_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Exceeded notification hash table." );
        tgCM_UT_LF__SN__Signal( &g_sKN_Notfiy_Lock.m_sLock );
        return (KTgKN_NOTIFY_ID__INVALID);
    };

    /* Take the first free element and forward the global free index */
    uiFree_Index = g_uiKN_Notfiy_Free_Index;
    g_uiKN_Notfiy_Free_Index = g_auiKN_Notify_Next[g_uiKN_Notfiy_Free_Index];

    /* This is the first function to register for this specific message (hash) */
    if (KTgMAX_U32 == g_auiKN_Notify_Index[uiHash])
    {
        g_auiKN_Notify_Index[uiHash] = uiFree_Index;
    }
    /* We have existing functions registered for this message, add this new entry to the linked list */
    else
    {
        TgRSIZE                             uiIndex;

        uiIndex = g_auiKN_Notify_Index[uiHash];
        while (KTgMAX_U32 != g_auiKN_Notify_Next[uiIndex])
        {
            uiIndex = g_auiKN_Notify_Next[uiIndex];
        };

        g_auiKN_Notify_Next[uiIndex] = uiFree_Index;
    };

    /* Fill in the data for the notification */
    g_asKN_Notify_Data[uiFree_Index].m_psFCN = psFCN;
    g_asKN_Notify_Data[uiFree_Index].m_uiParam0 = uiParam0;
    g_auiKN_Notify_MSG[uiFree_Index] = uiMSG;
    g_auiKN_Notify_Next[uiFree_Index] = KTgMAX_U32;
    tgKN_NOTIFY_ID_Init( &g_atiKN_Notify[uiFree_Index], uiFree_Index );

    tgCM_UT_LF__SN__Signal( &g_sKN_Notfiy_Lock.m_sLock );
    return (tgKN_NOTIFY_ID_Query_Unsafe( g_atiKN_Notify + uiFree_Index ));
}


/* ---- tgKN_Notify_End ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_Notify_End( TgKN_NOTIFY_ID_C tiNotify )
{
    TgRSIZE                             uiCount;
    TgUINT_E64                          uiMSG;
    TgUINT_MAX                          uiHash;
    TgUINT_E32_P                        puiIndex;

    tgCM_UT_LF__SN__Lock_Spin( &g_sKN_Notfiy_Lock.m_sLock );

    /* Make sure the entry is still valid */
    if (tiNotify.m_uiI >= KTgKN_MAX_NOTIFY_ENTRIES || !tgKN_NOTIFY_ID_Is_Equal( g_atiKN_Notify + tiNotify.m_uiI, tiNotify ))
    {
        tgCM_UT_LF__SN__Signal( &g_sKN_Notfiy_Lock.m_sLock );
        return (KTgE_FAIL);
    };

    /* Find the hash listing for the message attached to this entry */
    uiHash = g_auiKN_Notify_MSG[tiNotify.m_uiI] % KTgHASH_MD_SIZE;
    uiMSG = g_auiKN_Notify_MSG[tiNotify.m_uiI];
    uiCount = 0;
    do
    {
        if ((KTgMAX_U32 != g_auiKN_Notify_Index[uiHash]) && (uiMSG == g_auiKN_Notify_MSG[g_auiKN_Notify_Index[uiHash]]))
        {
            break;
        };

        uiHash = (uiHash + 1) % KTgHASH_MD_SIZE;
    }
    while (++uiCount < KTgHASH_MD_SIZE);

    /* Make sure the hash table has not been filled */
    if (KTgHASH_MD_SIZE == uiCount)
    {
        tgCM_UT_LF__SN__Signal( &g_sKN_Notfiy_Lock.m_sLock );
        return (KTgE_FAIL);
    };

    /* Remove entry from the link list of handlers for the message */
    puiIndex = g_auiKN_Notify_Index + uiHash;
    while (tiNotify.m_uiI != *puiIndex)
    {
        puiIndex = g_auiKN_Notify_Next + *puiIndex;
    };
    *puiIndex = g_auiKN_Notify_Next[tiNotify.m_uiI];

    /* Add the entry back into the free list */
    g_auiKN_Notify_Next[tiNotify.m_uiI] = g_uiKN_Notfiy_Free_Index;
    g_uiKN_Notfiy_Free_Index = tiNotify.m_uiI;

    tgCM_UT_LF__SN__Signal( &g_sKN_Notfiy_Lock.m_sLock );
    return (KTgS_OK);
}


/* ---- tgKN_Notify_MSG ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_Notify_MSG( TgUINT_F64_C uiMSG, TgUINT_F64_C uiParam1, TgUINT_F64_C uiParam2 )
{
    TgUINT_MAX                          uiHash;
    TgRSIZE                             uiCount;
    TgRSIZE                             uiIndex;

    tgCM_UT_LF__SN__Lock_Spin( &g_sKN_Notfiy_Lock.m_sLock );

    /* Find the hash listing for the message attached to this entry */
    uiHash = uiMSG % KTgHASH_MD_SIZE;
    uiCount = 0;
    do
    {
        if (KTgMAX_U32 != g_auiKN_Notify_Index[uiHash] && (uiMSG == g_auiKN_Notify_MSG[g_auiKN_Notify_Index[uiHash]]))
        {
            break;
        };

        uiHash = (uiHash + 1) % KTgHASH_MD_SIZE;
    }
    while (++uiCount < KTgHASH_MD_SIZE);

    /* Make sure the hash table has not been filled */
    if (KTgHASH_MD_SIZE == uiCount)
    {
        tgCM_UT_LF__SN__Signal( &g_sKN_Notfiy_Lock.m_sLock );
        return (KTgE_FAIL);
    };

    uiIndex = g_auiKN_Notify_Index[uiHash];
    do
    {
        g_asKN_Notify_Data[uiIndex].m_psFCN( g_asKN_Notify_Data[uiIndex].m_uiParam0, uiParam1, uiParam2 );
    }
    while (KTgMAX_U32 != (uiIndex = g_auiKN_Notify_Next[uiIndex]));

    tgCM_UT_LF__SN__Signal( &g_sKN_Notfiy_Lock.m_sLock );
    return (KTgS_OK);
}
