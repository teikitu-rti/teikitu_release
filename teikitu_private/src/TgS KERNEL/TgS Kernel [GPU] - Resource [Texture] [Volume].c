/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Resource [Texture] [Volume].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_TX_VOL_Inst__Init_Colour ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_GPU_TX_VOL_INST_ID tgKN_GPU_TX_VOL_Inst__Init_Colour( UTg2_KN_GPU_CMD_C uCMD, TgCOLOUR32_C sCL0, TgCHAR_U8_CPCU puszName )
{
    STg2_KN_GPU_TX_VOL_DESC             sTX_VOL_DESC;
    TgKN_GPU_TX_VOL_INST_ID             sTXI_VOL;
    STg2_KN_GPU_TX_Surface              sSF0;

    /* Create the texture as a 4x4x4 */

    tgMM_Set_U08_0x00( &sTX_VOL_DESC, sizeof( sTX_VOL_DESC ) );
    sTX_VOL_DESC.m_enFormat = ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM;
    sTX_VOL_DESC.m_nuiMIP = 1;
    sTX_VOL_DESC.m_uiDepth = 4;
    sTX_VOL_DESC.m_uiHeight = 4;
    sTX_VOL_DESC.m_uiWidth = 4;
    sTX_VOL_DESC.m_uszName = puszName;
    sTXI_VOL = tgKN_GPU_TX_VOL_Inst__Create( uCMD, ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_WRITEONLY, &sTX_VOL_DESC );

    if (KTgKN_GPU_TX_VOL_INST_ID__INVALID.m_uiKI == sTXI_VOL.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create a default colour texture" );
        return (KTgKN_GPU_TX_VOL_INST_ID__INVALID);
    };

#if TgS_DEBUG__KERNEL
    tgCN_PrintF( KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_7, STD_MSG_PREFIX u8"[Init] %-57.57s | id(% 4d) | % -9d BY\n", STD_MSG_POST,
                 puszName ? puszName : u8"", sTXI_VOL.m_uiIndex, g_uiKN_Size_GPU_TX_VOL[sTXI_VOL.m_uiIndex] );
#endif

    /* Lock the texture so as to have a valid data pointer - and fill in the assigned colour into it */

    {
        TgUINT_E32                          uiY, uiX, uiD;
        union
        {
            TgUINT_E08_P                        pui08;
            TgUINT_E32_P                        pui32;
        }                                   sMem;

        for (uiD = 0; uiD < 4; ++uiD)
        {
            tgMM_Set_U08_0x00( &sSF0, sizeof( sSF0 ) );
            sSF0.m_uiMIP = 0;
            tgKN_GPU_EXT_TX_VOL__Lock( &sSF0, uCMD, sTXI_VOL );
            TgVERIFY(nullptr != sSF0.m_puiData);

            for (uiY = 0; uiY < sSF0.m_nuiRow; ++uiY)
            {
                for (uiX = 0; uiX < sSF0.m_uiRowPitch; ++uiX)
                {
                    sMem.pui08 = sSF0.m_puiData + sSF0.m_uiRowPitch*uiY;
                    sMem.pui32[uiX] = sCL0.m_ui32;
                };
            };

            tgKN_GPU_EXT_TX_VOL__Unlock( uCMD, &sSF0, sTXI_VOL );
        };
    };

    return (sTXI_VOL);
}


/* ---- tgKN_GPU_TX_VOL_Inst__Create --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_GPU_TX_VOL_INST_ID tgKN_GPU_TX_VOL_Inst__Create( UTg2_KN_GPU_CMD_C uCMD, ETgKN_GPU_ALLOCATOR_C enAllocator, STg2_KN_GPU_TX_VOL_DESC_CPCU psTX_VOL_DESC )
{
    TgKN_GPU_TX_VOL_ID                  sTX_VOL;
    TgKN_GPU_TX_VOL_INST_ID             sTXI_VOL;

    TgCOMPILER_ASSERT( sizeof( TgRSIZE ) == sizeof( STg2_KN_GPU_TX_IMG_DESC_P ), 0 );

    sTX_VOL = tgKN_GPU_TX_VOL__Load_From_Memory( psTX_VOL_DESC, enAllocator );

    if (KTgKN_GPU_TX_VOL_ID__INVALID.m_uiKI == sTX_VOL.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_PREFIX u8"%-64.64s\n", STD_MSG_POST, u8"Failed to create texture" );
        return (KTgKN_GPU_TX_VOL_INST_ID__INVALID);
    };

    sTXI_VOL = tgKN_GPU_TX_VOL_Inst__Init( uCMD, sTX_VOL, psTX_VOL_DESC->m_uszName );

    if (KTgKN_GPU_TX_VOL_INST_ID__INVALID.m_uiKI == sTXI_VOL.m_uiKI)
    {
        tgKN_GPU_TX_VOL__Release( sTX_VOL );
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_PREFIX u8"%-64.64s\n", STD_MSG_POST, u8"Failed to create texture instance" );
        return (KTgKN_GPU_TX_VOL_INST_ID__INVALID);
    };

    return (sTXI_VOL);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU_TX_VOL__Execute_Load -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_TX_VOL__Execute_Load( TgKN_FILE_ID_C tiFile, TgRSIZE_C uiFile_Offset, STg2_KN_GPU_TX_VOL_DESC_CPC psDESC, ETgKN_GPU_ALLOCATOR_C enAllocator,
                                        TgKN_GPU_TX_VOL_ID_C sID  )
{
    g_asKN_Lib_TX_VOL_Data[sID.m_uiIndex].m_sTX.m_nuiMIP = psDESC ? psDESC->m_nuiMIP : KTgMAX_U32;
    g_asKN_Lib_TX_VOL_Data[sID.m_uiIndex].m_sTX.m_enFormat = psDESC ? psDESC->m_enFormat : ETgKN_GPU_EXT_FORMAT_UNKNOWN;
    g_asKN_Lib_TX_VOL_Data[sID.m_uiIndex].m_sTX.m_enAllocator = enAllocator;
    g_asKN_Lib_TX_VOL_Data[sID.m_uiIndex].m_sTX.m_uiFlags = psDESC ? psDESC->m_uiFlags : 0;
    g_asKN_Lib_TX_VOL_Data[sID.m_uiIndex].m_sTX.m_uiLastTouch = 0;
    g_asKN_Lib_TX_VOL_Data[sID.m_uiIndex].m_sTX.m_uiPriority = 0;

    g_asKN_Lib_TX_VOL_Data[sID.m_uiIndex].m_uiWidth = psDESC ? psDESC->m_uiWidth : KTgMAX_U32;
    g_asKN_Lib_TX_VOL_Data[sID.m_uiIndex].m_uiHeight = psDESC ? psDESC->m_uiHeight : KTgMAX_U32;
    g_asKN_Lib_TX_VOL_Data[sID.m_uiIndex].m_uiDepth = psDESC ? psDESC->m_uiDepth : KTgMAX_U32;

    return (tgKN_GPU_EXT_TX_VOL__Execute_Load( tiFile, uiFile_Offset, psDESC, enAllocator, sID ));
}


/* ---- tgKN_GPU_TX_VOL__Execute_Free -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_TX_VOL__Execute_Free( TgKN_GPU_TX_VOL_ID_C sID  )
{
    tgKN_GPU_EXT_TX_VOL__Execute_Free( sID );
    tgMM_Set_U08_0x00( g_asKN_Lib_TX_VOL_Data + sID.m_uiIndex, sizeof( g_asKN_Lib_TX_VOL_Data[0] ) );
}
