/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Resource [Texture] [Load] [TIFF].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

TgDISABLE_ALL_WARNNGS_PUSH
#define NULL nullptr /* Needed for Clang Build. */
#include <tiffio.h>
#include <stdlib.h>
#undef NULL
TgDISABLE_ALL_WARNNGS_POP


/* == Kernel ===================================================================================================================================================================== */
TgCLANG_WARN_DISABLE_PUSH(reserved-identifier)

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(TIFF_MEMORY_FILE,)
{
	TgUINT_E08_CP                               m_pData;
	tmsize_t                                    m_nuiData;
	tmsize_t                                    m_uiLOC;
};

static tmsize_t _tiffReadProc(
    thandle_t fd, void *buf, tmsize_t size );

static tmsize_t
_tiffWriteProc(
    thandle_t fd, void *buf, tmsize_t size );

static uint64_t
_tiffSeekProc(
    thandle_t fd, uint64_t off, int whence );

static int
_tiffCloseProc(
    thandle_t fd );

static uint64_t
_tiffSizeProc(
    thandle_t fd );

static int
_tiffMapProc(
    thandle_t fd, void **pbase, toff_t *psize );

static TgVOID
_tiffUnmapProc(
    thandle_t fd, void *base, toff_t size );

static TgVOID
Win32WarningHandler(
    const char *module, const char *fmt, va_list ap );

static TgVOID
Win32ErrorHandler(
    const char *module, const char *fmt, va_list ap );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  External Functions and Data                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TIFF* 
TIFFOpenInPlace(
    const uint8_t *data, const tmsize_t data_size, const char *mode );

TIFFErrorHandler _TIFFwarningHandler = Win32WarningHandler;
TIFFErrorHandler _TIFFerrorHandler = Win32ErrorHandler;



TgEXTN TgKN_GPU_TX_IMG_INST_ID DoSomething( UTg2_KN_GPU_CMD_C uCMD );

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU_TX_IMG__Load_TIFF_From_OS_File_System --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if !defined(TGS_FINAL)
TgKN_GPU_TX_IMG_INST_ID tgKN_GPU_TX_IMG__Load_TIFF_From_OS_File_System( UTg2_KN_GPU_CMD_C uCMD, TgKN_FS_MOUNT_ID_C tiFS_Mount, TgCHAR_U8_CPC uszPath, TgCHAR_U8_CPC uszFile,
                                                                        ETgKN_GPU_ALLOCATOR_C enAllocator )
{
    STg2_KN_File_Open_Command           sOpen_Cmd;
    TgKN_FILE_ID                        tiFile;
    TgKN_GPU_TX_IMG_INST_ID             sID_Inst_Ret;

    TgERROR_MSG( (nullptr != uszFile) && (uszFile[0] != 0),  u8"tgKN_GPU_RS_File_Load_BIN: Invalid File" );

    /* 1. Open the file for a blocking load.  Non-Blocking loads should not be done through the file execution path */
    if (nullptr == uszFile || TgFAILED(tgUSZ_Hash( &sOpen_Cmd.m_uiFile, uszFile, KTgMAX_RSIZE )))
    {
        TgERROR_SEV_MSG( false, KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, uszFile ? uszFile : u8"" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    if (nullptr == uszPath || TgFAILED(tgUSZ_Hash( &sOpen_Cmd.m_uiPath, uszPath, KTgMAX_RSIZE )))
    {
        sOpen_Cmd.m_uiPath = KTgEMPTY_HASH;
    };

    sOpen_Cmd.m_tiFS_Mount = tiFS_Mount;
    sOpen_Cmd.m_uiMode = ETgFILE_IO_ACCESS__READ | ETgFILE_IO_ACCESS__SHARED;
    sOpen_Cmd.m_iCache = 0;
    sOpen_Cmd.m_pszFile_Name = nullptr;

    tiFile = tgKN_FS_BL_Open( &sOpen_Cmd );

    if (KTgKN_FILE_ID__INVALID.m_uiKI == tiFile.m_uiKI)
    {
        TgERROR_SEV_MSG( false, KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, uszFile ? uszFile : u8"" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    /* 2. Load the contents of the file using the standard loader. */
    sID_Inst_Ret = tgKN_GPU_TX_IMG__Load_TIFF_From_KN_File_System( uCMD, tiFile, 0, enAllocator );

    /* 3. Close the file and return. */
    tgKN_FS_BL_Close( tiFile );
    return (sID_Inst_Ret);
}

/*# !defined(TGS_FINAL) */
#endif


/* ---- tgKN_GPU_TX_IMG__Load_TIFF_From_KN_File_System --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgKN_GPU_TX_IMG_INST_ID tgKN_GPU_TX_IMG__Load_TIFF_From_KN_File_System( UTg2_KN_GPU_CMD_C uCMD, TgKN_FILE_ID_C tiFile, TgRSIZE_C uiFile_Offset, ETgKN_GPU_ALLOCATOR_C enAllocator )
{
    STg2_KN_GPU_TX_IMG_DESC             sTX_IMG_DESC;
    STg2_KN_File_Read_Command           sRead_Command;
    TIFF                                *psTIFF;
    TgRSIZE                             nbyScanline;
    TgRSIZE                             uiRow;
    TgUINT_E32                          uiRow_Per_Strip;
    TgUINT_E16                          uiSamples_Per_Pixel;
    TgUINT_E16                          uiCompression;
    TgUINT_E16                          uiBits_Per_Sample;
    STg2_KN_GPU_TX_Surface              sSF0;
    TgKN_GPU_TX_IMG_INST_ID             sTXI_IMG;

    (void)uiFile_Offset;
    (void)enAllocator;

    tgMM_Set_U08_0x00( &sTX_IMG_DESC, sizeof( sTX_IMG_DESC ) );
    tgMM_Set_U08_0x00( &sRead_Command, sizeof( sRead_Command ) );

    /// Open and read the contents of the file. */

    sRead_Command.m_tiFile = tiFile;

    if (KTgKN_FILE_ID__INVALID.m_uiKI == sRead_Command.m_tiFile.m_uiKI) {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to open the file." );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    }

    sRead_Command.m_pfnAllocator = tgKN_FILE_ALLOCATOR__Default_Malloc_Pool;
    tgKN_FS_BL_Read( &sRead_Command );

    if (nullptr == sRead_Command.m_pBuffer || 0 == sRead_Command.m_nuiResult) {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to read any contents from the file." );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    }

    /// Open the file to be able to retrieve basic data about it.

    psTIFF = TIFFOpenInPlace( (TgUINT_E08_CP)sRead_Command.m_pBuffer, (tmsize_t)sRead_Command.m_nuiResult, "rcm" );
    if (!psTIFF)
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);

    TgVERIFY(0 < TIFFGetField( psTIFF, TIFFTAG_IMAGEWIDTH, &sTX_IMG_DESC.m_uiWidth ));
    TgVERIFY(0 < TIFFGetField( psTIFF, TIFFTAG_IMAGELENGTH, &sTX_IMG_DESC.m_uiHeight ));

    if(!TIFFGetField( psTIFF, TIFFTAG_ROWSPERSTRIP, &uiRow_Per_Strip )) {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"For performance, TIFF must be saved in strip format." );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    }

    if(!TIFFGetField( psTIFF, TIFFTAG_COMPRESSION, &uiCompression ) || (COMPRESSION_NONE != uiCompression)) {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"For simplicity, TIFF must be uncompressed." );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    if(!TIFFGetField( psTIFF, TIFFTAG_BITSPERSAMPLE, &uiBits_Per_Sample ) || (8 != uiBits_Per_Sample && 16 != uiBits_Per_Sample)) { 
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"For performance, TIFF must have 4 samples per pixel (RGBA)." );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    if(!TIFFGetField( psTIFF, TIFFTAG_SAMPLESPERPIXEL, &uiSamples_Per_Pixel ) || (4 != uiSamples_Per_Pixel)) { /* Validate that we have RGBA for the copy. */
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"For performance, TIFF must have 4 samples per pixel (RGBA)." );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    nbyScanline = (TgRSIZE)TIFFScanlineSize( psTIFF );

    /// Create the texture resource instance.

    sTX_IMG_DESC.m_enFormat = ETgKN_GPU_EXT_FORMAT_R16G16B16A16_UNORM;
    sTX_IMG_DESC.m_nuiMIP = 1;
    sTX_IMG_DESC.m_uszName = u8"DeltaE_16bit_G10.tif";

    sTXI_IMG = tgKN_GPU_TX_IMG_Inst__Create( uCMD, ETgKN_GPU_ALLOCATOR__VIDEO_MEMORY_WRITEONLY, &sTX_IMG_DESC );

    if (KTgKN_GPU_TX_IMG_INST_ID__INVALID.m_uiKI == sTXI_IMG.m_uiKI)
    {
        tgCN_PrintF( KTgCN_CHANEL_ERROR | KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create a default colour texture" );
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);
    };

    /// Lock the texture so as to have a valid data pointer - and fill in the assigned colour into it.

    tgMM_Set_U08_0x00( &sSF0, sizeof( sSF0 ) );
    sSF0.m_uiMIP = 0;
    tgKN_GPU_EXT_TX_IMG__Lock( &sSF0, uCMD, sTXI_IMG );
    TgVERIFY(nullptr != sSF0.m_puiData);

    if (0 == sSF0.m_puiData)
        return (KTgKN_GPU_TX_IMG_INST_ID__INVALID);

    for (uiRow = 0; uiRow < sTX_IMG_DESC.m_uiHeight; uiRow += uiRow_Per_Strip)
    {
        TgRSIZE_C                           nuiRows = tgCM_MIN_UMAX( uiRow + uiRow_Per_Strip, sTX_IMG_DESC.m_uiHeight ) - uiRow; // Upper bound is the height of the image.
        TgRSIZE_C                           nbyRowData = tgCM_MIN_UMAX( nuiRows*nbyScanline, sSF0.m_nuiTotal - uiRow * sTX_IMG_DESC.m_uiWidth * 8u );
        tstrip_t                            uiStrip = TIFFComputeStrip( psTIFF, (TgUINT_E32)uiRow, 0 );

        if (TIFFReadEncodedStrip( psTIFF, uiStrip, sSF0.m_puiData + uiRow * sTX_IMG_DESC.m_uiWidth * 8, (tmsize_t)nbyRowData ) < 0)
            break;
    };

    tgKN_GPU_EXT_TX_IMG__Unlock( uCMD, &sSF0, sTXI_IMG );

    /// Free the memory allocated when we read the contents of the file. */

    TIFFClose(psTIFF);
    TgFREE_POOL( sRead_Command.m_pBuffer );
    return (sTXI_IMG);
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  External Functions for LibTIFF to process in place and use internal memory management                                                                                          */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- TIFFOpenInPlace ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TIFF* TIFFOpenInPlace( const uint8_t *data, const tmsize_t data_size, const char *mode )
{
    TIFF *tif;
    TIFF_MEMORY_FILE *fd;

    fd = (TIFF_MEMORY_FILE *)TgMALLOC_POOL( sizeof( TIFF_MEMORY_FILE ) );
    if (!fd)
        return 0;
    _TIFFmemset( fd, 0, sizeof( TIFF_MEMORY_FILE ) );
    fd->m_pData = data;
    fd->m_nuiData = data_size;
    tif = TIFFClientOpen( "NULL", mode,
        (thandle_t)fd,
        _tiffReadProc, _tiffWriteProc,
        _tiffSeekProc, _tiffCloseProc,
        _tiffSizeProc,
        _tiffMapProc, _tiffUnmapProc );
    if (tif)
    {
        TIFFSetFileno( tif, (intptr_t)fd );
        return tif;
    }
    else
    {
        TgFREE_POOL( fd );
        return 0;
    }
}

/* These functions should only be used to allocate the tracking structure and that is it. */
/* ---- _TIFFmalloc -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
void *_TIFFmalloc( tmsize_t s )
{
    if (s == 0)
        return ((void *) nullptr);

    return (TgMALLOC_POOL( (size_t)s ));
}

/* ---- _TIFFcalloc -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
void *_TIFFcalloc( tmsize_t nmemb, tmsize_t siz )
{
    if (nmemb == 0 || siz == 0)
        return ((void *) nullptr);

    tgPM_Break();
    return calloc( (size_t)nmemb, (size_t)siz );
}

/* ---- _TIFFfree ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
void _TIFFfree( void *p )
{
    TgFREE_POOL( p );
}

/* ---- _TIFFrealloc ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
void *_TIFFrealloc( void *p, tmsize_t s )
{
    return (TgREALLOC_POOL( p, (size_t)s ));
}

/* ---- _TIFFmemset -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
void _TIFFmemset( void *p, int v, tmsize_t c )
{
    tgMM_Set_U08( p, (size_t)c, (TgUINT_E08)v );
}

/* ---- _TIFFmemcpy -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
void _TIFFmemcpy( void *d, const void *s, tmsize_t c )
{
    tgMM_Copy( d, (size_t)c, s, (size_t)c );
}

/* ---- _TIFFmemcmp -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
int _TIFFmemcmp( const void *p1, const void *p2, tmsize_t c )
{
    return (tgMM_Compare( p1, (size_t)c, p2, (size_t)c ));
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- _tiffReadProc ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static tmsize_t _tiffReadProc( thandle_t fd, void *buf, tmsize_t size )
{
    TIFF_MEMORY_FILE                    *psFile = (TIFF_MEMORY_FILE *)fd;
    tmsize_t                            toread = size < psFile->m_nuiData - psFile->m_uiLOC ? size : psFile->m_nuiData - psFile->m_uiLOC;

    _TIFFmemcpy( buf, psFile->m_pData + psFile->m_uiLOC, toread );
    psFile->m_uiLOC += toread;
    return toread;
}

/* ---- _tiffWriteProc ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static tmsize_t _tiffWriteProc( thandle_t fd, void *buf, tmsize_t size )
{
    (void)fd;
    (void)buf;
    (void)size;
    return 0;
}

/* ---- _tiffSeekProc ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static uint64_t _tiffSeekProc( thandle_t fd, uint64_t off, int whence )
{
    TIFF_MEMORY_FILE                    *psFile = (TIFF_MEMORY_FILE *)fd;

    switch (whence) {
    case 0:
        psFile->m_uiLOC = (tmsize_t)off;
        break;
    case 1:
        psFile->m_uiLOC += (tmsize_t)off;
        break;
    case 2:
        psFile->m_uiLOC = psFile->m_nuiData - (tmsize_t)off;
        break;
    default:
        psFile->m_uiLOC = (tmsize_t)off;
        break;
    }
    return((uint64_t)psFile->m_uiLOC);
}

/* ---- _tiffCloseProc ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static int _tiffCloseProc( thandle_t fd )
{
    _TIFFfree( fd );
    return (0);
}

/* ---- _tiffSizeProc ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static uint64_t _tiffSizeProc( thandle_t fd )
{
    TIFF_MEMORY_FILE *psFile = (TIFF_MEMORY_FILE *)fd;
    return (uint64_t)psFile->m_nuiData;
}

/* ---- _tiffMapProc ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static int _tiffMapProc( thandle_t fd, void **pbase, toff_t *psize )
{
    (void)fd;
    (void)pbase;
    (void)psize;
    return (0);
}

/* ---- _tiffUnmapProc ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static void _tiffUnmapProc( thandle_t fd, void *base, toff_t size )
{
    (void)fd;
    (void)base;
    (void)size;
}

/* ---- Win32WarningHandler ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static void Win32WarningHandler( const char *module, const char *fmt, va_list ap )
{
    TgCHAR_U8                           uszMSG[256];

    (void)module; // -Wunused-parameter
    tgUSZ_PrintVF( uszMSG, sizeof( uszMSG ), (TgCHAR_U8_CP)fmt, ap );
    TgWARNING_MSG( false, u8"LibTIFF Warning: %s - %s", module, uszMSG );
}

/* ---- Win32ErrorHandler -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static void Win32ErrorHandler( const char *module, const char *fmt, va_list ap )
{
    TgCHAR_U8                           uszMSG[256];

    (void)module; // -Wunused-parameter
    tgUSZ_PrintVF( uszMSG, sizeof( uszMSG ), (TgCHAR_U8_CP)fmt, ap );
    TgERROR_MSG(false, u8"LibTIFF Error: %s - %s", module, uszMSG );
}

TgCLANG_WARN_DISABLE_POP(reserved-identifier)

