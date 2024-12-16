/*
 * Copyright (c) 1988-1997 Sam Leffler
 * Copyright (c) 1991-1997 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and 
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
 * 
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 */

/*
 * TIFF Library Win32-specific Routines.  Adapted from tif_unix.c 4/5/95 by
 * Scott Wagner (wagner@itek.com), Itek Graphix, Rochester, NY USA
 */

#include "tiffiop.h"

//typedef struct
//{
//	const uint8_t *m_pData;
//	size_t m_nuiData;
//	rsize_t m_uiLOC;
//} TIFF_MEMORY_FILE;
//
//static tmsize_t
//_tiffReadProc(thandle_t fd, void* buf, tmsize_t size)
//{
//	TIFF_MEMORY_FILE *psFile = (TIFF_MEMORY_FILE*)fd;
//	size_t toread = size < psFile->m_nuiData - psFile->m_uiLOC ? size : psFile->m_nuiData - psFile->m_uiLOC;
//	_TIFFmemcpy( buf, psFile->m_pData + psFile->m_uiLOC, toread );
//	return toread;
//}
//
//static tmsize_t
//_tiffWriteProc(thandle_t fd, void* buf, tmsize_t size)
//{
//	return 0;
//}
//
//static uint64_t
//_tiffSeekProc(thandle_t fd, uint64_t off, int whence)
//{
//	TIFF_MEMORY_FILE *psFile = (TIFF_MEMORY_FILE*)fd;
//	switch(whence)
//	{
//		case SEEK_SET:
//			psFile->m_uiLOC = off;
//			break;
//		case SEEK_CUR:
//			psFile->m_uiLOC += off;
//			break;
//		case SEEK_END:
//			psFile->m_uiLOC = psFile->m_nuiData - off;
//			break;
//		default:
//			psFile->m_uiLOC = off;
//			break;
//	}
//	return(psFile->m_uiLOC);
//}
//
//static int
//_tiffCloseProc(thandle_t fd)
//{
//	_TIFFfree(fd);
//	return (0);
//}
//
//static uint64_t
//_tiffSizeProc(thandle_t fd)
//{
//	TIFF_MEMORY_FILE *psFile = (TIFF_MEMORY_FILE*)fd;
//	return psFile->m_nuiData;
//}
//
//static int
//_tiffMapProc(thandle_t fd, void** pbase, toff_t* psize)
//{
//	(void) fd;
//	(void) pbase;
//	(void) psize;
//	return (0);
//}
//
//static void
//_tiffUnmapProc(thandle_t fd, void* base, toff_t size)
//{
//	(void) fd;
//	(void) base;
//	(void) size;
//}
//
///*
// * Open a TIFF file for read/writing.
// */
//TIFF*
//TIFFOpenInPlace(const uint8_t* data, const size_t data_size, const char* mode)
//{
//	static const char module[] = "TIFFOpen";
//	TIFF* tif;
//	TIFF_MEMORY_FILE *fd;
//
//	fd = (TIFF_MEMORY_FILE*)_TIFFmalloc(sizeof(TIFF_MEMORY_FILE));
//	if (!fd)
//		return 0;
//	_TIFFmemset( fd, 0, sizeof(TIFF_MEMORY_FILE));
//	fd->m_pData = data;
//	fd->m_nuiData = data_size;
//	tif = TIFFClientOpen( NULL, mode, 
//			(thandle_t)fd,
//			_tiffReadProc, _tiffWriteProc,
//			_tiffSeekProc, _tiffCloseProc,
//			_tiffSizeProc,
//			_tiffMapProc, _tiffUnmapProc );
//	if (tif) {
//		tif->tif_fd = (intptr_t)fd;
//		return tif;
//	} else {
//		_TIFFfree(fd);
//		return 0;
//	}
//}

//void*
//_TIFFmalloc(tmsize_t s)
//{
//	if (s == 0)
//		return ((void *) NULL);
//
//	return (malloc((size_t) s));
//}
//
//void* _TIFFcalloc(tmsize_t nmemb, tmsize_t siz)
//{
//	if( nmemb == 0 || siz == 0 )
//		return ((void *) NULL);
//
//	return calloc((size_t) nmemb, (size_t)siz);
//}
//
//void
//_TIFFfree(void* p)
//{
//	free(p);
//}
//
//void*
//_TIFFrealloc(void* p, tmsize_t s)
//{
//	return (realloc(p, (size_t) s));
//}
//
//void
//_TIFFmemset(void* p, int v, tmsize_t c)
//{
//	memset(p, v, (size_t) c);
//}
//
//void
//_TIFFmemcpy(void* d, const void* s, tmsize_t c)
//{
//	memcpy(d, s, (size_t) c);
//}
//
//int
//_TIFFmemcmp(const void* p1, const void* p2, tmsize_t c)
//{
//	return (memcmp(p1, p2, (size_t) c));
//}
//
//static void
//Win32WarningHandler(const char* module, const char* fmt, va_list ap)
//{
//	if (module != NULL)
//		fprintf(stderr, "%s: ", module);
//	fprintf(stderr, "Warning, ");
//	vfprintf(stderr, fmt, ap);
//	fprintf(stderr, ".\n");
//}
//TIFFErrorHandler _TIFFwarningHandler = Win32WarningHandler;
//
//static void
//Win32ErrorHandler(const char* module, const char* fmt, va_list ap)
//{
//	if (module != NULL)
//		fprintf(stderr, "%s: ", module);
//	vfprintf(stderr, fmt, ap);
//	fprintf(stderr, ".\n");
//}
//TIFFErrorHandler _TIFFerrorHandler = Win32ErrorHandler;

/* vim: set ts=8 sts=8 sw=8 noet: */
/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 8
 * fill-column: 78
 * End:
 */
