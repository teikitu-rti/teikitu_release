/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Resource [Texture] [Cube].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU__CMD__TX_CBE_Inst__Init_Colour ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_GPU_TX_CBE_INST_ID tgKN_GPU__CMD__TX_CBE_Inst__Init_Colour( STg2_KN_GPU_CMD_PC psCMD, TgCOLOUR32_C sCL0, TgCHAR_U8_CPCU uszName )
{
    TgUINT_E64_C                        uiResource_Descriptor = ETgKN_GPU_RESOURCE_DESCRIPTOR__TEXTURE_CUBE | ETgKN_GPU_RESOURCE_DESCRIPTOR__MEMORY_LOCAL;
    STg2_KN_GPU_TX_CBE_DESC             sTX_CBE_DESC;
    TgKN_GPU_TX_CBE_INST_ID             sTXI_CBE;
    STg2_KN_GPU_TX_LOCK                 sSF0;
    TgRSIZE                             uiY, uiX, uiD;
    union
    {
        TgUINT_E08_P                        pui08;
        TgUINT_E32_P                        pui32;
    }                                   uMem;

    /* Create the texture as a 4x4x4 */

    tgMM_Set_U08_0x00( &sTX_CBE_DESC, sizeof( sTX_CBE_DESC ) );
    sTX_CBE_DESC.m_enFormat = ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM;
    sTX_CBE_DESC.m_nuiMIP = 1;
    sTX_CBE_DESC.m_uiEdge = 4;
    sTX_CBE_DESC.m_uszName = uszName;
    sTXI_CBE = tgKN_GPU__CMD__TX_CBE_Inst__Create( psCMD, (ETgKN_GPU_RESOURCE_DESCRIPTOR)uiResource_Descriptor, &sTX_CBE_DESC );

    if (KTgKN_GPU_TX_CBE_INST_ID__INVALID.m_uiKI == sTXI_CBE.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_PREFIX u8"%-64.64s |\n", STD_MSG_POST, u8"Failed to create a default colour texture" );
        return (sTXI_CBE);
    };

#if TgS_DEBUG__KERNEL
    tgCN_PrintF( KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_7, STD_MSG_PREFIX u8"[Init] %-57.57s | id(% 4d) | % -9d BY\n", STD_MSG_POST,
                 uszName ? uszName : u8"", sTXI_CBE.m_uiIndex, g_uiKN_Size_GPU_TX_CBE[sTXI_CBE.m_uiIndex] );
#endif

    /* Lock the texture so as to have a valid data pointer - and fill in the assigned colour into it */
    tgKN_GPU_EXT__CMD__TX_CBE__Lock( &sSF0, psCMD, sTXI_CBE );
    TgVERIFY(nullptr != sSF0.m_puiData);

    uMem.pui08 = sSF0.m_puiData;

    for (uiD = 0; uiD < 6; ++uiD)
    {
        for (uiY = 0; uiY < sTX_CBE_DESC.m_uiEdge; ++uiY)
        {
            for (uiX = 0; uiX < sTX_CBE_DESC.m_uiEdge; ++uiX, ++uMem.pui32)
            {
                *uMem.pui32 = sCL0.m_ui32;
            };
        };
    };

    tgKN_GPU_EXT__CMD__TX_CBE__Unlock( psCMD, &sSF0, sTXI_CBE );
    return (sTXI_CBE);
}


/* ---- tgKN_GPU__CMD__TX_CBE_Inst__Create --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_GPU_TX_CBE_INST_ID tgKN_GPU__CMD__TX_CBE_Inst__Create( STg2_KN_GPU_CMD_PC psCMD, TgUINT_E64_C uiResource_Descriptor, STg2_KN_GPU_TX_CBE_DESC_CPCU psTX_CBE_DESC )
{
    TgKN_GPU_TX_CBE_ID                  sTX_CBE;
    TgKN_GPU_TX_CBE_INST_ID             sTXI_CBE;

    sTX_CBE = tgKN_GPU_TX_CBE__Load_From_Memory( psTX_CBE_DESC, uiResource_Descriptor );

    if (KTgKN_GPU_TX_CBE_ID__INVALID.m_uiKI == sTX_CBE.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create texture" );
        sTXI_CBE = KTgKN_GPU_TX_CBE_INST_ID__INVALID;
        return (sTXI_CBE);
    };

    sTXI_CBE = tgKN_GPU__CMD__TX_CBE_Inst__Init( psCMD, sTX_CBE, psTX_CBE_DESC->m_uszName );

    if (KTgKN_GPU_TX_CBE_INST_ID__INVALID.m_uiKI == sTXI_CBE.m_uiKI)
    {
        tgKN_GPU_TX_CBE__Release( sTX_CBE );
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create texture instance" );
        return (sTXI_CBE);
    };

    return (sTXI_CBE);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU_TX_CBE__Execute_Load -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_TX_CBE__Execute_Load( TgKN_FILE_ID_C tiFile, TgRSIZE_C uiFile_Offset, STg2_KN_GPU_TX_CBE_DESC_CPC psDESC, TgUINT_E64_C uiResource_Descriptor,
                                        TgKN_GPU_TX_CBE_ID_C sID  )
{
    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_sTX.m_nuiMIP = psDESC ? psDESC->m_nuiMIP : KTgMAX_U32;
    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_sTX.m_enFormat = psDESC ? psDESC->m_enFormat : ETgKN_GPU_EXT_FORMAT_UNDEFINED;
    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_sTX.m_uiResource_Descriptor = uiResource_Descriptor;
    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_sTX.m_uiFlags = psDESC ? psDESC->m_uiFlags : 0;
    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_sTX.m_uiLast_Touch = 0;
    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_sTX.m_uiPriority = 0;

    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_uiEdge = psDESC ? psDESC->m_uiEdge : KTgMAX_U32;

    return (tgKN_GPU_EXT_TX_CBE__Execute_Load( tiFile, uiFile_Offset, psDESC, uiResource_Descriptor, sID ));
}


/* ---- tgKN_GPU_TX_CBE__Execute_Free -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_TX_CBE__Execute_Free( TgKN_GPU_TX_CBE_ID_C sID  )
{
    tgKN_GPU_EXT_TX_CBE__Execute_Free( sID );
    tgMM_Set_U08_0x00( g_asKN_Lib_TX_CBE_Data + sID.m_uiIndex, sizeof( g_asKN_Lib_TX_CBE_Data[0] ) );
}
