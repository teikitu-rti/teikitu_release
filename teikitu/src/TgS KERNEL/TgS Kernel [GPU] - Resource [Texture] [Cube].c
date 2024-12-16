/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Resource [Texture] [Cube].c
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

/* ---- tgKN_GPU_TX_CBE_Inst__Init_Colour ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_GPU_TX_CBE_INST_ID tgKN_GPU_TX_CBE_Inst__Init_Colour( UTg2_KN_GPU_CMD_C uCMD, TgCOLOUR32_C sCL0, TgCHAR_U8_CPCU uszName )
{
    STg2_KN_GPU_TX_CBE_DESC             sTX_CBE_DESC;
    TgKN_GPU_TX_CBE_INST_ID             sTXI_CBE;
    STg2_KN_GPU_TX_Surface              sSF0;

    /* Create the texture as a 4x4x4 */

    tgMM_Set_U08_0x00( &sTX_CBE_DESC, sizeof( sTX_CBE_DESC ) );
    sTX_CBE_DESC.m_enFormat = ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM;
    sTX_CBE_DESC.m_nuiMIP = 1;
    sTX_CBE_DESC.m_uiEdge = 4;
    sTX_CBE_DESC.m_uszName = uszName;
    sTXI_CBE = tgKN_GPU_TX_CBE_Inst__Create( uCMD, ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_WRITEONLY, &sTX_CBE_DESC );

    if (KTgKN_GPU_TX_CBE_INST_ID__INVALID.m_uiKI == sTXI_CBE.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_PREFIX u8"%-64.64s |\n", STD_MSG_POST, u8"Failed to create a default colour texture" );
        return (KTgKN_GPU_TX_CBE_INST_ID__INVALID);
    };

#if TgS_DEBUG__KERNEL
    tgCN_PrintF( KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_7, STD_MSG_PREFIX u8"[Init] %-57.57s | id(% 4d) | % -9d BY\n", STD_MSG_POST,
                 uszName ? uszName : u8"", sTXI_CBE.m_uiIndex, g_uiKN_Size_GPU_TX_CBE[sTXI_CBE.m_uiIndex] );
#endif

    /* Lock the texture so as to have a valid data pointer - and fill in the assigned colour into it */

    {
        TgUINT_F32                          uiY, uiX, uiD;
        union
        {
            TgUINT_F08_P                        pui08;
            TgUINT_F32_P                        pui32;
        }                                   sMem;

        for (uiD = 0; uiD < 4; ++uiD)
        {
            tgMM_Set_U08_0x00( &sSF0, sizeof( sSF0 ) );
            sSF0.m_uiMIP = 0;
            tgKN_GPU_EXT_TX_CBE__Lock( &sSF0, uCMD, sTXI_CBE );
            TgVERIFY(nullptr != sSF0.m_puiData);

            for (uiY = 0; uiY < sSF0.m_nuiRow; ++uiY)
            {
                for (uiX = 0; uiX < sSF0.m_uiRowPitch; ++uiX)
                {
                    sMem.pui08 = sSF0.m_puiData + sSF0.m_uiRowPitch*uiY;
                    sMem.pui32[uiX] = sCL0.m_ui32;
                };
            };

            tgKN_GPU_EXT_TX_CBE__Unlock( uCMD, &sSF0, sTXI_CBE );
        };
    };

    return (sTXI_CBE);
}


/* ---- tgKN_GPU_TX_CBE_Inst__Create --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_GPU_TX_CBE_INST_ID tgKN_GPU_TX_CBE_Inst__Create( UTg2_KN_GPU_CMD_C uCMD, ETgKN_GPU_ALLOCATOR_C enAllocator, STg2_KN_GPU_TX_CBE_DESC_CPCU psTX_CBE_DESC )
{
    TgKN_GPU_TX_CBE_ID                  sTX_CBE;
    TgKN_GPU_TX_CBE_INST_ID             sTXI_CBE;

    sTX_CBE = tgKN_GPU_TX_CBE__Load_From_Memory( psTX_CBE_DESC, enAllocator );

    if (KTgKN_GPU_TX_CBE_ID__INVALID.m_uiKI == sTX_CBE.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create texture" );
        return (KTgKN_GPU_TX_CBE_INST_ID__INVALID);
    };

    sTXI_CBE = tgKN_GPU_TX_CBE_Inst__Init( uCMD, sTX_CBE, psTX_CBE_DESC->m_uszName );

    if (KTgKN_GPU_TX_CBE_INST_ID__INVALID.m_uiKI == sTXI_CBE.m_uiKI)
    {
        tgKN_GPU_TX_CBE__Release( sTX_CBE );
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create texture instance" );
        return (KTgKN_GPU_TX_CBE_INST_ID__INVALID);
    };

    return (sTXI_CBE);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU_TX_CBE__Execute_Load -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_TX_CBE__Execute_Load( TgKN_FILE_ID_C tiFile, TgRSIZE_C uiFile_Offset, STg2_KN_GPU_TX_CBE_DESC_CPC psDESC, ETgKN_GPU_ALLOCATOR_C enAllocator,
                                        TgKN_GPU_TX_CBE_ID_C sID  )
{
    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_sTX.m_nuiMIP = psDESC ? psDESC->m_nuiMIP : KTgMAX_U32;
    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_sTX.m_enFormat = psDESC ? psDESC->m_enFormat : ETgKN_GPU_EXT_FORMAT_UNKNOWN;
    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_sTX.m_enAllocator = enAllocator;
    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_sTX.m_uiFlags = psDESC ? psDESC->m_uiFlags : 0;
    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_sTX.m_uiLastTouch = 0;
    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_sTX.m_uiPriority = 0;

    g_asKN_Lib_TX_CBE_Data[sID.m_uiIndex].m_uiEdge = psDESC ? psDESC->m_uiEdge : KTgMAX_U32;

    return (tgKN_GPU_EXT_TX_CBE__Execute_Load( tiFile, uiFile_Offset, psDESC, enAllocator, sID ));
}


/* ---- tgKN_GPU_TX_CBE__Execute_Free -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_TX_CBE__Execute_Free( TgKN_GPU_TX_CBE_ID_C sID  )
{
    tgKN_GPU_EXT_TX_CBE__Execute_Free( sID );
    tgMM_Set_U08_0x00( g_asKN_Lib_TX_CBE_Data + sID.m_uiIndex, sizeof( g_asKN_Lib_TX_CBE_Data[0] ) );
}
