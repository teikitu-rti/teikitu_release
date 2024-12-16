/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Partition - Module.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Object ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static ETgMODULE_STATE                      s_enPartition_State = ETgMODULE_STATE__FREED;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPA_Module_Init --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Module_Init( TgVOID )
{
    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__FREED == s_enPartition_State );
    s_enPartition_State = ETgMODULE_STATE__INITIALIZING;

    g_aapsPA_Graph = nullptr;
    g_niPA_Graph = 0;
    g_iPA_Graph_End = 0;
    tgPM_MT_MX_Init( &g_sModule_Lock, TgOS_TEXT("Partition Module MX") );

    s_enPartition_State = ETgMODULE_STATE__INITIALIZED;
    return (KTgS_OK);
}


/* ---- tgPA_Module_Boot --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Module_Boot( TgVOID )
{
    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__INITIALIZED == s_enPartition_State );
    s_enPartition_State = ETgMODULE_STATE__BOOTING;

    LOG_STD_MSG_USZ_FMTU64( KTgCN_CHANEL_INITIALIZE_MEMORY, u8"Static Memory Size", tgPA_Query_Fixed_Memory() )

    s_enPartition_State = ETgMODULE_STATE__BOOTED;
    return (KTgS_OK);
}


/* ---- tgPA_Module_Stop --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPA_Module_Stop( TgVOID )
{
    if ((ETgMODULE_STATE__FREED == s_enPartition_State) || (ETgMODULE_STATE__INITIALIZED == s_enPartition_State))
    {
        return;
    };

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__BOOTED == s_enPartition_State );
    s_enPartition_State = ETgMODULE_STATE__STOPPING;

    s_enPartition_State = ETgMODULE_STATE__STOPPED;
}


/* ---- tgPA_Module_Free --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPA_Module_Free( TgVOID )
{
    TgSINT_E32                          iIndex;

    if (ETgMODULE_STATE__FREED == s_enPartition_State)
    {
        return;
    };

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__STOPPED == s_enPartition_State || ETgMODULE_STATE__INITIALIZED == s_enPartition_State );
    s_enPartition_State = ETgMODULE_STATE__FREEING;

    for (iIndex = 0; iIndex < g_iPA_Graph_End; ++iIndex)
    {
        STg2_PA_Graph_PC                    psPA_Graph = g_aapsPA_Graph[iIndex];

        if (nullptr == psPA_Graph)
            continue;

        TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
        switch (psPA_Graph->m_enPA_Graph) {
        case ETgPA_GRAPH_TYPE__PRUNE_SWEEP:
            tgPA_Graph_PNS_Free( tgPARTITION_GRAPH_ID_Query_Unsafe( &psPA_Graph->m_tiGraph_Singleton ) );
            break;
        default: break;
        }
        TgWARN_DISABLE_POP()

        g_aapsPA_Graph[iIndex] = nullptr;
    };

    if (nullptr != g_aapsPA_Graph)
    {
        TgFREE_POOL(g_aapsPA_Graph);
    };
    tgPM_MT_MX_Free( &g_sModule_Lock );

    s_enPartition_State = ETgMODULE_STATE__FREED;
}


/* ---- tgPA_Module_Update ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Module_Update( TgATTRIBUTE_UNUSED TgFLOAT32_C fDT )
{
    return (KTgS_OK);
}


/* ---- tgPA_Load_Config --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPA_Load_Config( TgVOID )
{

}


/* ---- tgPA_Save_Config --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPA_Save_Config( TgVOID )
{

}


/* ---- tgPA_Query_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgPA_Query_Init( TgVOID )
{
    return (ETgMODULE_STATE__INITIALIZED <= s_enPartition_State && s_enPartition_State <= ETgMODULE_STATE__STOPPED);
}


/* ---- tgPA_Query_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgPA_Query_Boot( TgVOID )
{
    return (ETgMODULE_STATE__BOOTED == s_enPartition_State);
}
