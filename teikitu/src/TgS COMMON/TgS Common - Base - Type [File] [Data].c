/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Type [File] [Data].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_File_Output_Header -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_File_Output_Header( STg2_Output_P psOUT, STg2_File_Block_CPC psFileBlock )
{
    TgRSIZE                             uiIndex;
    union
    {
        TgUINT_E08_CP                       pui;
        STg2_File_Section_CP                ps;
    }                                   psSection;

    TgPARAM_CHECK(psOUT && psFileBlock);

    tgIO_PrintF( psOUT, u8"File Header\n" );
    tgIO_PrintF( psOUT, u8" - FourCC Tool: %lld\n", psFileBlock->m_uiFourCC_Tool );
    tgIO_PrintF( psOUT, u8" - FourCC Data: %lld\n", psFileBlock->m_uiFourCC_Data );
    tgIO_PrintF( psOUT, u8" - Version: %d\n", psFileBlock ->m_uiVersion );
    tgIO_PrintF( psOUT, u8" - Machine: %d\n", psFileBlock ->m_uiMachine );
    tgIO_PrintF( psOUT, u8" - Flags: %d\n", psFileBlock ->m_uiFlags );
    tgIO_PrintF( psOUT, u8" - Tools Version: %d\n", psFileBlock ->m_uiTool_Version );
    tgIO_PrintF( psOUT, u8" - Tool Id: %d\n", psFileBlock ->m_uiTool_ID );
    tgIO_PrintF( psOUT, u8" - Section Version: %d\n", psFileBlock ->m_uiSection_Version );
    tgIO_PrintF( psOUT, u8" - Section Count: %d\n", psFileBlock ->m_uiSection_Count );
    tgIO_PrintF( psOUT, u8" - Section Size: %d\n", psFileBlock ->m_uiSection_Size );

    psSection.pui = (TgUINT_F08_CP)psFileBlock->m_asSection;
    for (uiIndex = 0; uiIndex < psFileBlock->m_uiSection_Count; ++uiIndex)
    {
        tgIO_PrintF( psOUT, u8" - Section (% 4d) FourCC Tool: %lld\n", uiIndex, psSection.ps->m_uiFourCC_Tool );
        tgIO_PrintF( psOUT, u8" - Section (% 4d) FourCC Data: %lld\n", uiIndex, psSection.ps->m_uiFourCC_Data );
        tgIO_PrintF( psOUT, u8" - Section (% 4d) Offset: %d\n", uiIndex, psSection.ps->m_uiOffset );
        psSection.pui += psFileBlock->m_uiSection_Size;
    };
}


/* ---- tgCM_File_Output_Data_Headers -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_File_Output_Data_Headers( STg2_Output_P psOUT, STg2_File_Block_CPC psFileBlock )
{
    TgRSIZE                             uiIndex;
    union
    {
        TgUINT_E08_CP                       pui;
        STg2_File_Section_CP                ps;
    }                                   psSection;
    union
    {
        TgUINT_E08_CP                       pui;
        STg2_File_Data_CP                   ps;
    }                                   psData;

    TgPARAM_CHECK(psOUT && psFileBlock);

    psSection.pui = (TgUINT_F08_CP)psFileBlock->m_asSection;
    for (uiIndex = 0; uiIndex < psFileBlock->m_uiSection_Count; ++uiIndex)
    {
        psData.pui = (TgUINT_F08_CP)psFileBlock + psSection.ps->m_uiOffset;
        tgIO_PrintF( psOUT, u8" - Section Data (% 4d) FourCC Data: %d\n", uiIndex, psData.ps->m_uiFourCC_Data );
        tgIO_PrintF( psOUT, u8" - Section Data (% 4d) Offset: %d\n", uiIndex, psData.ps->m_iOffset );
        tgIO_PrintF( psOUT, u8" - Section Data (% 4d) Size: %d\n", uiIndex, psData.ps->m_uiSize );
        tgIO_PrintF( psOUT, u8" - Section Data (% 4d) Version: %d\n", uiIndex, psData.ps->m_uiVersion );
        psSection.pui += psFileBlock->m_uiSection_Size;
    };
}


/* ---- tgCM_File_Query_Data ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCM_File_Query_Data( TgVOID const **ppRet, STg2_File_Block_CPC psFileBlock, TgUINT_F32_C uiBlockIndex )
{
    union
    {
        TgUINT_E08_CP                       pui;
        STg2_File_Section_CP                ps;
    }                                   psSection;
    union
    {
        TgUINT_E08_CP                       pui;
        STg2_File_Data_CP                   ps;
    }                                   psData;

    TgPARAM_CHECK(ppRet && psFileBlock);

    if (uiBlockIndex >= psFileBlock->m_uiSection_Count)
        return (false);

    psSection.pui = (TgUINT_F08_CP)psFileBlock->m_asSection + uiBlockIndex * psFileBlock->m_uiSection_Size;
    psData.pui = (TgUINT_F08_CP)psFileBlock + psSection.ps->m_uiOffset;

    *ppRet = (TgVOID_CP)(psData.pui + psData.ps->m_iOffset);
    return (true);
}


/* ---- tgCM_File_Query_Data_Size ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCM_File_Query_Data_Size( TgRSIZE_P puiSize, STg2_File_Block_CPC psFileBlock, TgUINT_F32_C uiBlockIndex )
{
    union
    {
        TgUINT_E08_CP                       pui;
        STg2_File_Section_CP                ps;
    }                                   psSection;
    union
    {
        TgUINT_E08_CP                       pui;
        STg2_File_Data_CP                   ps;
    }                                   psData;

    TgPARAM_CHECK(puiSize && psFileBlock);

    if (uiBlockIndex >= psFileBlock->m_uiSection_Count)
        return (false);

    psSection.pui = (TgUINT_F08_CP)psFileBlock->m_asSection + uiBlockIndex * psFileBlock->m_uiSection_Size;
    psData.pui = (TgUINT_F08_CP)psFileBlock + psSection.ps->m_uiOffset;

    *puiSize = psData.ps->m_uiSize;
    return (true);
}


/* ---- tgCM_File_Query_Data_Count ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgCM_File_Query_Data_Count( STg2_File_Block_CPC psFileBlock )
{
    TgPARAM_CHECK(psFileBlock);
    return (psFileBlock->m_uiSection_Count);
}


/* ---- tgCM_File_Check_Block ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_File_Check_Block( STg2_File_Block_CPCU psFileBlock )
{
    TgRSIZE                             uiIndex;
    union
    {
        TgUINT_E08_CP                       pui;
        STg2_File_Section_CP                ps;
    }                                   psSection;
    union
    {
        TgUINT_E08_CP                       pui;
        STg2_File_Data_CP                   ps;
    }                                   psData;

    TgPARAM_CHECK(psFileBlock);

    if (!(psFileBlock->m_uiSize == sizeof( STg2_File_Block ))) return (KTgE_FAIL);
    if (!((psFileBlock->m_uiVersion > 0))) return (KTgE_FAIL);
    if (!((psFileBlock->m_uiTool_Version > 0))) return (KTgE_FAIL);
    if (!((psFileBlock->m_uiSection_Version > 0))) return (KTgE_FAIL);
    if (!((psFileBlock->m_uiSection_Count > 0))) return (KTgE_FAIL);
    if (!((psFileBlock->m_uiSection_Size == sizeof( STg2_File_Section )))) return (KTgE_FAIL);

    psSection.pui = (TgUINT_F08_CP)psFileBlock->m_asSection;
    for (uiIndex = 0; uiIndex < psFileBlock->m_uiSection_Count; ++uiIndex)
    {
        psData.pui = (TgUINT_F08_CP)psFileBlock + psSection.ps->m_uiOffset;
        if (!((psSection.ps->m_uiFourCC_Data == psData.ps->m_uiFourCC_Data))) return (KTgE_FAIL);
        if (!((psData.ps->m_iOffset > 0))) return (KTgE_FAIL);
        if (!((psData.ps->m_uiSize > 0))) return (KTgE_FAIL);
        if (!((psData.ps->m_uiVersion > 0))) return (KTgE_FAIL);
        psSection.pui += psFileBlock->m_uiSection_Size;
    };

    return (KTgS_OK);
}

