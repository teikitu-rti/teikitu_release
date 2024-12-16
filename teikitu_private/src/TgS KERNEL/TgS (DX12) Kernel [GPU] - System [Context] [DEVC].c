/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - System [GPU] [Context] [DEVC].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__Device__Init ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Device__Init( TgKN_GPU_CXT_DEVC_ID_C tiCXT_DEVC )
{
    STg2_KN_GPU_EXT_CXT_DEVC_PC         psEXT_CXT_DEVC = g_asKN_GPU_EXT_CXT_DEVC + tiCXT_DEVC.m_uiI;
    STg2_KN_GPU_CXT_DEVC_PC             psCXT_DEVC = g_asKN_GPU_CXT_DEVC + tiCXT_DEVC.m_uiI;

    TgPARAM_CHECK_INDEX(tiCXT_DEVC.m_uiI, g_asKN_GPU_EXT_CXT_DEVC);
    TgVERIFY(g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_DEVC->m_uiAdapter_Index].m_tiID_DEVC.m_uiKI == KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI);

    tgMM_Set_U08_0x00( psEXT_CXT_DEVC, sizeof( STg2_KN_GPU_CXT_DEVC ) );
    psEXT_CXT_DEVC->m_tiID = tiCXT_DEVC;
    psEXT_CXT_DEVC->m_uiAdapter_Index = psCXT_DEVC->m_uiAdapter_Index;

    g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_DEVC->m_uiAdapter_Index].m_tiID_DEVC.m_uiKI = tiCXT_DEVC.m_uiKI;

#if !defined(TGS_FINAL)
    {
        ID3D12Device10_PC                   psDX12_Device = g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_DEVC->m_uiAdapter_Index].m_psDX12_Device;

        ID3D12InfoQueue1_P                  psDX12_Info_Queue_1;
        D3D12_INFO_QUEUE_FILTER             sDX12_Info_Queue_Filter;

        tgMM_Set_U08_0x00( &sDX12_Info_Queue_Filter, sizeof( D3D12_INFO_QUEUE_FILTER ) );

        if (SUCCEEDED( ID3D12Device10_QueryInterface( psDX12_Device, MS_REF IID_ID3D12InfoQueue1, (TgVOID_PP)&psDX12_Info_Queue_1 ) ))
        {
            /* Suppress whole categories of messages.
            D3D12_MESSAGE_CATEGORY aCategories[]
            {
            };
            NewFilter.DenyList.NumCategories = TgARRAY_COUNT(aCategories);
            NewFilter.DenyList.pCategoryList = aCategories;
            */

            /* Suppress messages based on their severity level. */
            D3D12_MESSAGE_SEVERITY aSeverities[] =
            {
                D3D12_MESSAGE_SEVERITY_INFO
            };
            sDX12_Info_Queue_Filter.DenyList.NumSeverities = TgARRAY_COUNT(aSeverities);
            sDX12_Info_Queue_Filter.DenyList.pSeverityList = aSeverities;

            /* Suppress individual messages by their ID.
            D3D12_MESSAGE_ID aDenyIds[] =
            {
            };
            sDX12_Info_Queue_Filter.DenyList.NumIDs = TgARRAY_COUNT(aDenyIds);
            sDX12_Info_Queue_Filter.DenyList.pIDList = aDenyIds;
            */

            ID3D12InfoQueue1_PushStorageFilter( psDX12_Info_Queue_1, &sDX12_Info_Queue_Filter );
            ID3D12InfoQueue1_SetBreakOnSeverity( psDX12_Info_Queue_1, D3D12_MESSAGE_SEVERITY_WARNING, TRUE );
            ID3D12InfoQueue1_Release( psDX12_Info_Queue_1 );
        }
    }
/*# !defined(TGS_FINAL)*/
#endif

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Device__Free ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Device__Free( TgKN_GPU_CXT_DEVC_ID_C tiCXT_DEVC )
{
    STg2_KN_GPU_EXT_CXT_DEVC_PC         psEXT_CXT_DEVC = g_asKN_GPU_EXT_CXT_DEVC + tiCXT_DEVC.m_uiI;
    STg2_KN_GPU_CXT_DEVC_PC             psCXT_DEVC = g_asKN_GPU_CXT_DEVC + tiCXT_DEVC.m_uiI;

    TgPARAM_CHECK_INDEX(tiCXT_DEVC.m_uiI, g_asKN_GPU_EXT_CXT_DEVC);

    TgVERIFY(g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_DEVC->m_uiAdapter_Index].m_tiID_DEVC.m_uiKI != KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI);
    TgVERIFY(g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_DEVC->m_uiAdapter_Index].m_tiID_DEVC.m_uiKI == tiCXT_DEVC.m_uiKI);
    g_sKN_GPU_EXT_CXT_HOST.m_asEXT_Adapter[psCXT_DEVC->m_uiAdapter_Index].m_tiID_DEVC.m_uiKI = KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI;

    tgMM_Set_U08_0x00( psEXT_CXT_DEVC, sizeof( STg2_KN_GPU_EXT_CXT_DEVC ) );
    psEXT_CXT_DEVC->m_tiID = KTgKN_GPU_CXT_DEVC_ID__INVALID;
}
