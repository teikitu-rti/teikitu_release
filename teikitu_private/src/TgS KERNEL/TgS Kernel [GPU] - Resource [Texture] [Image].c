/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Resource [Texture] [Image].c
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

/* ---- tgKN_GPU_TX_IMG_Inst__Init_Colour ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_GPU_TX_IMG_INST_ID tgKN_GPU_TX_IMG_Inst__Init_Colour( UTg2_KN_GPU_CMD_C uCMD, TgCOLOUR32_C sCL0, TgCHAR_U8_CPCU uszName )
{
    STg2_KN_GPU_TX_IMG_DESC             sTX_IMG_DESC;
    TgKN_GPU_TX_IMG_INST_ID             sTXI_IMG;
    STg2_KN_GPU_TX_Surface              sSF0;

    /* Create the texture as a 4x4.  Smaller textures do not work on the PS3 due to alignment restrictions. */

    tgMM_Set_U08_0x00( &sTX_IMG_DESC, sizeof( sTX_IMG_DESC ) );
    sTX_IMG_DESC.m_enFormat = ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM;
    sTX_IMG_DESC.m_nuiMIP = 1;
    sTX_IMG_DESC.m_uiHeight = 4;
    sTX_IMG_DESC.m_uiWidth = 4;
    sTX_IMG_DESC.m_uszName = uszName;
    sTXI_IMG = tgKN_GPU_TX_IMG_Inst__Create( uCMD, ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_WRITEONLY, &sTX_IMG_DESC );

    if (KTgKN_GPU_TX_IMG_INST_ID__INVALID.m_uiKI == sTXI_IMG.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create a default colour texture" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

#if TgS_DEBUG__KERNEL
    tgCN_PrintF( KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_7, STD_MSG_PREFIX u8"[Init] %-57.57s | id(% 4d) | % -9d BY\n", STD_MSG_POST, uszName ? uszName : u8"", sTXI_IMG.m_uiIndex,
                 g_uiKN_Size_GPU_TX_IMG[sTXI_IMG.m_uiIndex] );
#endif

    /* Lock the texture so as to have a valid data pointer - and fill in the assigned colour into it. */

    tgMM_Set_U08_0x00( &sSF0, sizeof( sSF0 ) );
    sSF0.m_uiMIP = 0;
    tgKN_GPU_EXT_TX_IMG__Lock( &sSF0, uCMD, sTXI_IMG );
    TgVERIFY(nullptr != sSF0.m_puiData);

    {
        TgUINT_E32                          uiY, uiX;
        union
        {
            TgUINT_E08_P                        pui08;
            TgUINT_E32_P                        pui32;
        }                                   sMem;

        for (uiY = 0; uiY < sSF0.m_nuiRow; ++uiY)
        {
            sMem.pui08 = sSF0.m_puiData + sSF0.m_uiMemPitch*uiY;
            for (uiX = 0; uiX < sSF0.m_uiRowPitch; uiX += 4)
            {
                *sMem.pui32 = sCL0.m_ui32;
                sMem.pui08 += 4;
            };
        };
    };

    tgKN_GPU_EXT_TX_IMG__Unlock( uCMD, &sSF0, sTXI_IMG );

    return (sTXI_IMG);
}


/* ---- tgKN_GPU_TX_IMG_Inst__Create --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_GPU_TX_IMG_INST_ID tgKN_GPU_TX_IMG_Inst__Create( UTg2_KN_GPU_CMD_C uCMD, ETgKN_GPU_ALLOCATOR_C enAllocator, STg2_KN_GPU_TX_IMG_DESC_CPCU psTX_IMG_DESC )
{
    TgKN_GPU_TX_IMG_ID                  sTX_IMG;
    TgKN_GPU_TX_IMG_INST_ID             sTXI_IMG;

    sTX_IMG = tgKN_GPU_TX_IMG__Load_From_Memory( psTX_IMG_DESC, enAllocator );

    if (KTgKN_GPU_TX_IMG_ID__INVALID.m_uiKI == sTX_IMG.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create texture" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    sTXI_IMG = tgKN_GPU_TX_IMG_Inst__Init( uCMD, sTX_IMG, psTX_IMG_DESC->m_uszName );

    if (KTgKN_GPU_TX_IMG_INST_ID__INVALID.m_uiKI == sTXI_IMG.m_uiKI)
    {
        tgKN_GPU_TX_IMG__Release( sTX_IMG );
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create texture instance" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    return (sTXI_IMG);
}


/* ---- tgKN_GPU_RT_IMG__Create -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_GPU_TX_IMG_INST_ID tgKN_GPU_RT_IMG__Create( UTg2_KN_GPU_CMD_C uCMD, ETgKN_GPU_ALLOCATOR_C enAllocator, STg2_KN_GPU_TX_IMG_DESC_CPCU psTX_IMG_DESC )
{
    TgKN_GPU_TX_IMG_ID                  sTX_IMG;
    TgKN_GPU_TX_IMG_INST_ID             sTXI_IMG;

    TgCOMPILER_ASSERT( sizeof( TgRSIZE ) == sizeof( STg2_KN_GPU_TX_IMG_DESC_P ), 0 );

    sTX_IMG = tgKN_GPU_TX_IMG__Load_From_Memory( psTX_IMG_DESC, enAllocator );

    if (KTgKN_GPU_TX_IMG_ID__INVALID.m_uiKI == sTX_IMG.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_5, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to render target texture" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    sTXI_IMG = tgKN_GPU_TX_IMG_Inst__Init( uCMD, sTX_IMG, psTX_IMG_DESC->m_uszName );

    if (KTgKN_GPU_TX_IMG_INST_ID__INVALID.m_uiKI == sTXI_IMG.m_uiKI)
    {
        tgKN_GPU_TX_IMG__Release( sTX_IMG );
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_5, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to instance render target" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    return (sTXI_IMG);
}


/* ---- tgKN_GPU_TX_IMG_Inst__Font_ROM ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
TgKN_GPU_TX_IMG_INST_ID tgKN_GPU_TX_IMG_Inst__Font_ROM( UTg2_KN_GPU_CMD_C uCMD, STg2_KN_GPU_FONT_PC psFont_ROM )
{
    TgRSIZE_C                           uiDest_Glyph_X = psFont_ROM->m_uiFntX + 1;
    TgRSIZE_C                           uiDest_Glyph_Y = psFont_ROM->m_uiFntY + 1;
    TgRSIZE_C                           uiSrc_Glyph_X = psFont_ROM->m_uiFntX;
    TgRSIZE_C                           uiSrc_Glyph_Y = psFont_ROM->m_uiFntY;

    STg2_KN_GPU_TX_IMG_DESC             sTX_IMG_DESC;
    TgKN_GPU_TX_IMG_INST_ID             sTXI_IMG;
    STg2_KN_GPU_TX_Surface              sSF0;

    tgMM_Set_U08_0x00( &sTX_IMG_DESC, sizeof( sTX_IMG_DESC ) );
    sTX_IMG_DESC.m_enFormat = ETgKN_GPU_EXT_FORMAT_A8_UNORM;
    sTX_IMG_DESC.m_nuiMIP = 1;
    sTX_IMG_DESC.m_uszName = psFont_ROM->m_uszName;

    sTX_IMG_DESC.m_uiWidth = 32;
    while(1)
    {
        if ((sTX_IMG_DESC.m_uiWidth / uiDest_Glyph_X) * (sTX_IMG_DESC.m_uiWidth / uiDest_Glyph_Y) >= psFont_ROM->m_nuiGlyph)
            break;
        sTX_IMG_DESC.m_uiWidth *= 2;
    };
    sTX_IMG_DESC.m_uiHeight = sTX_IMG_DESC.m_uiWidth;
    sTXI_IMG = tgKN_GPU_TX_IMG_Inst__Create( uCMD, ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_WRITEONLY, &sTX_IMG_DESC );

    if (KTgKN_GPU_TX_IMG_INST_ID__INVALID.m_uiKI == sTXI_IMG.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create a default colour texture" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

#if TgS_DEBUG__KERNEL
    tgCN_PrintF( KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_7, STD_MSG_PREFIX u8"[Init] %-57.57s | id(% 4d) | % -9d BY\n", STD_MSG_POST,
                 psFont_ROM->m_uszName ? psFont_ROM->m_uszName : u8"", sTXI_IMG.m_uiIndex, g_uiKN_Size_GPU_TX_IMG[sTXI_IMG.m_uiIndex] );
#endif

    /* Lock the texture so as to have a valid data pointer. */

    tgMM_Set_U08_0x00( &sSF0, sizeof( sSF0 ) );
    sSF0.m_uiMIP = 0;
    tgKN_GPU_EXT_TX_IMG__Lock( &sSF0, uCMD, sTXI_IMG );
    TgVERIFY(nullptr != sSF0.m_puiData);

    if (0 != sSF0.m_puiData)
    {
        TgRSIZE                          iGlpyh, iY, iX, iGlyphMax, uiDestIndex, uiSrcIndex;

        TgPARAM_CHECK( uiSrc_Glyph_X <= uiDest_Glyph_X );
        TgPARAM_CHECK( uiSrc_Glyph_Y <= uiDest_Glyph_Y );

        // Lock the texture so as to have a valid data pointer.

        tgMM_Set_U08_0x00( sSF0.m_puiData, sSF0.m_nuiTotal );

        /* First row of the texture*/
        iGlyphMax = psFont_ROM->m_uiBufX * 8 / psFont_ROM->m_uiFntX / psFont_ROM->m_uiFntY;
        for (iGlpyh = 0; iGlpyh < iGlyphMax; ++iGlpyh)
        {
            uiDestIndex = (iGlpyh % (sSF0.m_uiRowPitch / uiDest_Glyph_X))*uiDest_Glyph_X
                        + (iGlpyh / (sSF0.m_uiRowPitch / uiDest_Glyph_X))*(sSF0.m_uiMemPitch * uiDest_Glyph_Y);

            uiSrcIndex = iGlpyh * psFont_ROM->m_uiFntX * psFont_ROM->m_uiFntY / 8;

            for (iY = 0; iY < uiSrc_Glyph_Y; ++iY)
            {
                for (iX = 0; iX < uiSrc_Glyph_X; ++iX)
                {
                    (sSF0.m_puiData + uiDestIndex + iY*sSF0.m_uiMemPitch)[iX] = (psFont_ROM->m_puiData[uiSrcIndex + (iY*uiSrc_Glyph_X + iX)/8] & (1 << (7 - iX % 8))) ? 0xFFu : 0x00u;
                };
                for (; iX < uiDest_Glyph_X; ++iX)
                {
                    (sSF0.m_puiData + uiDestIndex + iY*sSF0.m_uiMemPitch)[iX] = 0x00u;
                };
            };

            for (; iY < uiDest_Glyph_Y; ++iY)
            {
                for (iX = 0; iX < uiDest_Glyph_X; ++iX)
                {
                    (sSF0.m_puiData + uiDestIndex + iY*sSF0.m_uiMemPitch)[iX] = 0x00u;
                };
            };
        };
    };

    tgKN_GPU_EXT_TX_IMG__Unlock( uCMD, &sSF0, sTXI_IMG );

    psFont_ROM->m_uiTX_X = (TgUINT_E32)sTX_IMG_DESC.m_uiWidth;
    psFont_ROM->m_uiTX_Y = (TgUINT_E32)sTX_IMG_DESC.m_uiHeight;
    psFont_ROM->m_uiTX_Cell_X = (TgUINT_E32)uiDest_Glyph_X;
    psFont_ROM->m_uiTX_Cell_Y = (TgUINT_E32)uiDest_Glyph_Y;

    return (sTXI_IMG);
}
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif


/* ---- tgKN_GPU_TX_IMG_Inst__Init_MIP ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
TgKN_GPU_TX_IMG_INST_ID tgKN_GPU_TX_IMG_Inst__Init_MIP( UTg2_KN_GPU_CMD_C uCMD, TgUINT_E32 uiW, TgUINT_E32 uiH, TgCHAR_U8_CPCU uszName )
{
    STg2_KN_GPU_TX_IMG_DESC             sTX_IMG_DESC;
    TgKN_GPU_TX_IMG_INST_ID             sTXI_IMG;
    STg2_KN_GPU_TX_Surface              sSF0;
    TgSINT_E08                          niMIP, iMIP;
    TgUINT_E32                          uiMin;

    uiW = tgCM_PRV_PW2_U32( uiW );
    uiH = tgCM_PRV_PW2_U32( uiH );
    uiMin = tgCM_MIN_U32( uiW, uiH );
    niMIP = tgPM_BSR_U32( uiMin );

    if (0 >= uiW || 0 >= uiH)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create a default MIP texture" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    /* Create the texture. */

    tgMM_Set_U08_0x00( &sTX_IMG_DESC, sizeof( sTX_IMG_DESC ) );
    sTX_IMG_DESC.m_enFormat = ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM;
    sTX_IMG_DESC.m_nuiMIP = (TgUINT_E32)niMIP;
    sTX_IMG_DESC.m_uiHeight = uiH;
    sTX_IMG_DESC.m_uiWidth = uiW;
    sTX_IMG_DESC.m_uszName = uszName;
    sTXI_IMG = tgKN_GPU_TX_IMG_Inst__Create( uCMD, ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_WRITEONLY, &sTX_IMG_DESC );

    if (KTgKN_GPU_TX_IMG_INST_ID__INVALID.m_uiKI == sTXI_IMG.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create a default colour texture" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

#if TgS_DEBUG__KERNEL
    tgCN_PrintF( KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_7, STD_MSG_PREFIX u8"[Init] %-57.57s | id(% 4d) | % -9d BY\n", STD_MSG_POST, uszName ? uszName : u8"", sTXI_IMG.m_uiIndex,
                 g_uiKN_Size_GPU_TX_IMG[sTXI_IMG.m_uiIndex] );
#endif

    /* Lock the texture so as to have a valid data pointer. */

    for (iMIP = 0; iMIP < niMIP; ++iMIP)
    {
        TgFLOAT32_C                         fHue = tgPM_FMOD_F32( ((TgFLOAT32)iMIP) * 0.3F, 1.0F );
        TgFLOAT32_C                         fSat = 1.0F;
        TgFLOAT32_C                         fLight = 1.0F;
        TgVEC_F32_04_1                      vK = tgMH_Init_ELEM_F32_04_1( 1.0F, 2.0F / 3.0F, 1.0F / 3.0F, 3.0F );
        TgVEC_F32_04_1                      vC0 = tgMH_ADD_F32_04_1( tgMH_SET1_F32_04_1( fHue ), vK );
        TgVEC_F32_04_1                      vC1 = tgMH_SUB_F32_04_1( vC0, tgMH_FLR_F32_04_1( vC0 ) );
        TgVEC_F32_04_1                      vC2 = tgMH_MUL_F32_04_1( vC1, tgMH_SET1_F32_04_1( 6.0F ) );
        TgVEC_F32_04_1                      vC3 = tgMH_SUB_F32_04_1( vC2, tgMH_SPW_F32_04_1( vK ) );
        TgVEC_F32_04_1                      vP = tgMH_ABS_F32_04_1( vC3 );
        TgVEC_F32_04_1                      vC4 = tgMH_SUB_F32_04_1( vP, tgMH_SPX_F32_04_1( vK ) );
        TgVEC_F32_04_1                      vC5 = tgMH_CLP_F32_04_1( vC4, tgMH_SET1_F32_04_1( 0.0F ), tgMH_SET1_F32_04_1( 1.0F ) );
        TgVEC_F32_04_1                      vC6 = tgMH_LRP_F32_04_1( tgMH_SPX_F32_04_1( vK ), vC5, tgMH_SET1_F32_04_1( fSat ) );
        TgVEC_F32_04_1                      vC7 = tgMH_MUL_F32_04_1( tgMH_SET1_F32_04_1( fLight ), vC6 );
        TgCOLOUR32                          sCL = tgCM_CL_U32_Init_F32( vC7 );

        tgMM_Set_U08_0x00( &sSF0, sizeof( sSF0 ) );
        sSF0.m_uiMIP = (TgUINT_E32)niMIP - (TgUINT_E32)iMIP - 1u;
        tgKN_GPU_EXT_TX_IMG__Lock( &sSF0, uCMD, sTXI_IMG );
        TgVERIFY(nullptr != sSF0.m_puiData);

        sCL.m_uiAlpha = 0xFF;

        {
            TgUINT_E32                          uiY, uiX;
            union
            {
                TgUINT_E08_P                        pui08;
                TgUINT_E32_P                        pui32;
            }                                   sMem;

            for (uiY = 0; uiY < sSF0.m_nuiRow; ++uiY)
            {
                sMem.pui08 = sSF0.m_puiData + sSF0.m_uiMemPitch*uiY;
                for (uiX = 0; uiX < sSF0.m_uiRowPitch; uiX += 4)
                {
                    *sMem.pui32 = sCL.m_ui32;
                    sMem.pui08 += 4;
                };
            };
        };

        tgKN_GPU_EXT_TX_IMG__Unlock( uCMD, &sSF0, sTXI_IMG );
    };

    return (sTXI_IMG);
}
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif


/* ---- tgKN_GPU_TX_IMG_Inst__Init_Gamma_Test ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
TgKN_GPU_TX_IMG_INST_ID tgKN_GPU_TX_IMG_Inst__Init_Gamma_Test( UTg2_KN_GPU_CMD_C uCMD, TgUINT_E32 uiW, TgUINT_E32 uiH, TgCHAR_U8_CPCU uszName )
{
    STg2_KN_GPU_TX_IMG_DESC             sTX_IMG_DESC;
    TgKN_GPU_TX_IMG_INST_ID             sTXI_IMG;
    STg2_KN_GPU_TX_Surface              sSF0;

    uiW = tgCM_PRV_PW2_U32( uiW );
    uiH = tgCM_PRV_PW2_U32( uiH );

    if (0 >= uiW || 0 >= uiH)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create a default MIP texture" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    /* Create the texture. */

    tgMM_Set_U08_0x00( &sTX_IMG_DESC, sizeof( sTX_IMG_DESC ) );
    sTX_IMG_DESC.m_enFormat = ETgKN_GPU_EXT_FORMAT_R8_UNORM;
    sTX_IMG_DESC.m_nuiMIP = 1;
    sTX_IMG_DESC.m_uiHeight = uiH;
    sTX_IMG_DESC.m_uiWidth = uiW;
    sTX_IMG_DESC.m_uszName = uszName;
    sTXI_IMG = tgKN_GPU_TX_IMG_Inst__Create( uCMD, ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_WRITEONLY, &sTX_IMG_DESC );

    if (KTgKN_GPU_TX_IMG_INST_ID__INVALID.m_uiKI == sTXI_IMG.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create a default colour texture" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

#if TgS_DEBUG__KERNEL
    tgCN_PrintF( KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_7, STD_MSG_PREFIX u8"[Init] %-57.57s | id(% 4d) | % -9d BY\n", STD_MSG_POST, uszName ? uszName : u8"", sTXI_IMG.m_uiIndex,
                 g_uiKN_Size_GPU_TX_IMG[sTXI_IMG.m_uiIndex] );
#endif

    /* Lock the texture so as to have a valid data pointer. */

    tgMM_Set_U08_0x00( &sSF0, sizeof( sSF0 ) );
    sSF0.m_uiMIP = 0;
    tgKN_GPU_EXT_TX_IMG__Lock( &sSF0, uCMD, sTXI_IMG );
    TgVERIFY(nullptr != sSF0.m_puiData);

    if (nullptr != sSF0.m_puiData)
    {
        TgUINT_E32                          uiY, uiX;
        TgUINT_E08_P                        pui08;

        /* Create a gradient over top an interleaved pattern of white and black lines. */
        for (uiY = 0; uiY < sSF0.m_nuiRow >> 1; ++uiY)
        {
            pui08 = sSF0.m_puiData + sSF0.m_uiMemPitch*uiY;
            for (uiX = 0; uiX < sSF0.m_uiRowPitch; ++uiX, ++pui08)
            {
                *pui08 = (TgUINT_E08)(uiX & 0xFF);
            };
        };

        for (; uiY < sSF0.m_nuiRow; ++uiY)
        {
            pui08 = sSF0.m_puiData + sSF0.m_uiMemPitch*uiY;
            for (uiX = 0; uiX < sSF0.m_uiRowPitch; ++uiX, ++pui08)
            {
                *pui08 = (TgUINT_E08)((uiX % 2) * 0xFF);
            };
        };
    };

    tgKN_GPU_EXT_TX_IMG__Unlock( uCMD, &sSF0, sTXI_IMG );

    return (sTXI_IMG);
}
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif


/* ---- tgKN_GPU_TX_IMG_Inst__Init_Checker_Pattern ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
TgKN_GPU_TX_IMG_INST_ID tgKN_GPU_TX_IMG_Inst__Init_Checker_Pattern( UTg2_KN_GPU_CMD_C uCMD, TgUINT_E32 uiW, TgUINT_E32 uiH, TgCOLOUR32_C sCL0,  TgCOLOUR32_C sCL1,
                                                                    TgCHAR_U8_CPCU uszName )
{
    STg2_KN_GPU_TX_IMG_DESC             sTX_IMG_DESC;
    TgKN_GPU_TX_IMG_INST_ID             sTXI_IMG;
    STg2_KN_GPU_TX_Surface              sSF0;

    uiW = tgCM_MAX_U32( 64, tgCM_PRV_PW2_U32( uiW ) );
    uiH = tgCM_MAX_U32( 64, tgCM_PRV_PW2_U32( uiH ) );

    if (0 >= uiW || 0 >= uiH)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create a default MIP texture" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    /* Create the texture. */

    tgMM_Set_U08_0x00( &sTX_IMG_DESC, sizeof( sTX_IMG_DESC ) );
    sTX_IMG_DESC.m_enFormat = ETgKN_GPU_EXT_FORMAT_R8G8B8A8_UNORM;
    sTX_IMG_DESC.m_nuiMIP = 1;
    sTX_IMG_DESC.m_uiHeight = uiH;
    sTX_IMG_DESC.m_uiWidth = uiW;
    sTX_IMG_DESC.m_uszName = uszName;
    sTXI_IMG = tgKN_GPU_TX_IMG_Inst__Create( uCMD, ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_WRITEONLY, &sTX_IMG_DESC );

    if (KTgKN_GPU_TX_IMG_INST_ID__INVALID.m_uiKI == sTXI_IMG.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create a default colour texture" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

#if TgS_DEBUG__KERNEL
    tgCN_PrintF( KTgCN_CHANEL_INITIALIZE | KTgCN_SEVERITY_7, STD_MSG_PREFIX u8"[Init] %-57.57s | id(% 4d) | % -9d BY\n", STD_MSG_POST, uszName ? uszName : u8"", sTXI_IMG.m_uiIndex,
                 g_uiKN_Size_GPU_TX_IMG[sTXI_IMG.m_uiIndex] );
#endif

    /* Lock the texture so as to have a valid data pointer. */

    tgMM_Set_U08_0x00( &sSF0, sizeof( sSF0 ) );
    sSF0.m_uiMIP = 0;
    tgKN_GPU_EXT_TX_IMG__Lock( &sSF0, uCMD, sTXI_IMG );
    TgVERIFY(nullptr != sSF0.m_puiData);

    if (nullptr != sSF0.m_puiData)
    {
        TgUINT_E32                          uiY, uiX;
        union
        {
            TgUINT_E08_P                        pui08;
            TgUINT_E32_P                        pui32;
        }                                   sMem;

        /* Create a gradient over top an interleaved pattern of white and black lines. */
        for (uiY = 0; uiY < sSF0.m_nuiRow; ++uiY)
        {
            sMem.pui08 = sSF0.m_puiData + sSF0.m_uiMemPitch*uiY;
            for (uiX = 0; uiX < sSF0.m_uiRowPitch; uiX += 4, sMem.pui08 += 4)
            {
                
                if (0 == ((((uiX >> 2) >> 5) % 2) +  ((uiY >> 5) % 2)) % 2)
                {
                    *sMem.pui32 = sCL0.m_ui32;
                }
                else
                {
                    *sMem.pui32 = sCL1.m_ui32;
                }
            };
        };
    };

    tgKN_GPU_EXT_TX_IMG__Unlock( uCMD, &sSF0, sTXI_IMG );

    return (sTXI_IMG);
}
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU_TX_IMG__Execute_Load -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_TX_IMG__Execute_Load( TgKN_FILE_ID_C tiFile, TgRSIZE_C uiFile_Offset, STg2_KN_GPU_TX_IMG_DESC_CPC psDESC, ETgKN_GPU_ALLOCATOR_C enAllocator,
                                        TgKN_GPU_TX_IMG_ID_C sID  )
{
    g_asKN_Lib_TX_IMG_Data[sID.m_uiIndex].m_sTX.m_nuiMIP = psDESC ? psDESC->m_nuiMIP : KTgMAX_U32;
    g_asKN_Lib_TX_IMG_Data[sID.m_uiIndex].m_sTX.m_enFormat = psDESC ? psDESC->m_enFormat : ETgKN_GPU_EXT_FORMAT_UNKNOWN;
    g_asKN_Lib_TX_IMG_Data[sID.m_uiIndex].m_sTX.m_enAllocator = enAllocator;
    g_asKN_Lib_TX_IMG_Data[sID.m_uiIndex].m_sTX.m_uiFlags = psDESC ? psDESC->m_uiFlags : 0;
    g_asKN_Lib_TX_IMG_Data[sID.m_uiIndex].m_sTX.m_uiLastTouch = 0;
    g_asKN_Lib_TX_IMG_Data[sID.m_uiIndex].m_sTX.m_uiPriority = 0;
    g_asKN_Lib_TX_IMG_Data[sID.m_uiIndex].m_uiWidth = psDESC ? psDESC->m_uiWidth : KTgMAX_U32;
    g_asKN_Lib_TX_IMG_Data[sID.m_uiIndex].m_uiHeight = psDESC ? psDESC->m_uiHeight : KTgMAX_U32;

    return (tgKN_GPU_EXT_TX_IMG__Execute_Load( tiFile, uiFile_Offset, psDESC, enAllocator, sID ));
}


/* ---- tgKN_GPU_TX_IMG__Execute_Free -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_TX_IMG__Execute_Free( TgKN_GPU_TX_IMG_ID_C sID  )
{
    tgKN_GPU_EXT_TX_IMG__Execute_Free( sID );
    tgMM_Set_U08_0x00( g_asKN_Lib_TX_IMG_Data + sID.m_uiIndex, sizeof( g_asKN_Lib_TX_IMG_Data[0] ) );
}
