/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - System [GPU] [Context] [DEVC].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU__Device__Init --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU__Device__Init( STg2_KN_GPU_Init_Result_PCU psResult, STg2_KN_GPU_Select_CPCU psSelect, TgRSIZE_C uiAdapter_Index )
{
    TgRSIZE                             uiDevice_Index_In_Host_Context;
    TgRSIZE                             uiIndex;
    TgKN_GPU_CXT_DEVC_ID                tiCXT_DEVC;
    union
    {
        STg2_KN_GPU_CXT_DEVC_P              ps;
        STg2_UT_ST__ST_Node_P               pNode;
    }                                   sCXT_DEVC;

    /* Find an empty slot in the host context for the device. */
    for (uiDevice_Index_In_Host_Context = 0; uiDevice_Index_In_Host_Context < KTgKN_GPU_MAX_DEVC_CONTEXT; ++uiDevice_Index_In_Host_Context)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCXT_DEVC[uiDevice_Index_In_Host_Context].m_uiKI == KTgKN_GPU_CXT_DEVC_ID__INVALID.m_uiKI)
        {
            break;
        };
    };

    /* Theoretically impossible, however range checking is still good practice. */
    if (uiDevice_Index_In_Host_Context >= KTgKN_GPU_MAX_DEVC_CONTEXT)
    {
        return (KTgE_FAIL);
    };

    /* Take a context from the free list. */
    sCXT_DEVC.pNode = tgCM_UT_LF__ST__Pop( &g_sKN_GPU_CXT_DEVC_Free_Stack.m_sStack );
    if (nullptr == sCXT_DEVC.pNode)
    {
        return (KTgE_FAIL);
    };

    /* Initialize the context. */
    tgMM_Set_U08_0x00( sCXT_DEVC.pNode, sizeof( STg2_KN_GPU_CXT_DEVC ) );
    tgKN_GPU_CXT_DEVC_ID_Init( &sCXT_DEVC.ps->m_tiCXT_DEVC_S, (TgUINT_E32)(sCXT_DEVC.ps - g_asKN_GPU_CXT_DEVC) );
    tgKN_GPU_CXT_DEVC_ID_Load( &tiCXT_DEVC, &sCXT_DEVC.ps->m_tiCXT_DEVC_S );

    sCXT_DEVC.ps->m_uiAdapter_Index = (TgUINT_E32)psSelect->m_uiEnumeration_Adapter_Index[uiAdapter_Index];

    /* API specific additional work. */
    if (TgFAILED(tgKN_GPU_EXT__Device__Init( tiCXT_DEVC )))
    {
        goto tgKN_GPU__Device__Init_FAIL;
    };

    /* Initialize all of the execution contexts associated with this device. */
    for (uiIndex = 0; uiIndex < psSelect->m_nuiNode; ++uiIndex)
    {
        if (psSelect->m_sNode[uiIndex].m_uiAdapter_Index != uiAdapter_Index)
            continue;
        if ((uiIndex < KTgKN_GPU_MAX_EXEC_CONTEXT) && TgFAILED(tgKN_GPU__Execute__Init( psResult, psSelect, uiIndex, tiCXT_DEVC )))
        {
            goto tgKN_GPU__Device__Init_FAIL_1;
        };
    };

    g_sKN_GPU_CXT_HOST.m_atiCXT_DEVC[uiDevice_Index_In_Host_Context] = tiCXT_DEVC;
    return (KTgS_OK);

tgKN_GPU__Device__Init_FAIL_1:
    tgKN_GPU_EXT__Device__Free( tiCXT_DEVC );
tgKN_GPU__Device__Init_FAIL:
    tgMM_Set_U08_0x00( sCXT_DEVC.pNode, sizeof( STg2_KN_GPU_CXT_DEVC ) );
    tgKN_GPU_CXT_DEVC_ID_Invalidate( &sCXT_DEVC.ps->m_tiCXT_DEVC_S );
    tgCM_UT_LF__ST__Push( &g_sKN_GPU_CXT_DEVC_Free_Stack.m_sStack, sCXT_DEVC.pNode );
    return (KTgE_FAIL);
}


/* ---- tgKN_GPU__Device__Free --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU__Device__Free( TgKN_GPU_CXT_DEVC_ID_C tiCXT_DEVC )
{
    TgRSIZE                             uiIndex;
    union
    {
        STg2_KN_GPU_CXT_DEVC_P              ps;
        STg2_UT_ST__ST_Node_P               pNode;
    }                                   sCXT_DEVC;

    sCXT_DEVC.ps = g_asKN_GPU_CXT_DEVC + tiCXT_DEVC.m_uiI;
    TgERROR(tgKN_GPU_CXT_DEVC_ID_Is_Equal( &sCXT_DEVC.ps->m_tiCXT_DEVC_S, tiCXT_DEVC ));

    tgKN_GPU_EXT__Device__Free( tiCXT_DEVC );

    tgMM_Set_U08_0x00( sCXT_DEVC.pNode, sizeof( STg2_KN_GPU_CXT_DEVC ) );
    tgKN_GPU_CXT_DEVC_ID_Invalidate( &sCXT_DEVC.ps->m_tiCXT_DEVC_S );
    tgCM_UT_LF__ST__Push( &g_sKN_GPU_CXT_DEVC_Free_Stack.m_sStack, sCXT_DEVC.pNode );

    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_DEVC_CONTEXT; ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCXT_DEVC[uiIndex].m_uiKI == tiCXT_DEVC.m_uiKI)
        {
            g_sKN_GPU_CXT_HOST.m_atiCXT_DEVC[uiIndex] = KTgKN_GPU_CXT_DEVC_ID__INVALID;
            break;
        };
    };
    TgERROR(uiIndex < KTgKN_GPU_MAX_DEVC_CONTEXT);
}
