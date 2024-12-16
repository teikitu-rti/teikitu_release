/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Mem MGR - Override.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

#if defined(TgBUILD_FEATURE__MALLOC_OVERRIDE) && defined (MK_BUILD__SHARED_LIBRARY)

TgEXTN TgATTRIBUTE_NO_DISCARD TgATTRIBUTE_RESTRICT TgDLL_EXPORT void* 
mi_malloc(size_t size) TgATTRIBUTE_NO_EXCEPT TgATTRIBUTE_MALLOC TgATTRIBUTE_ALLOC_SIZE1(1);

TgATTRIBUTE_RESTRICT void* mi_malloc(size_t size) TgATTRIBUTE_NO_EXCEPT
{
    TgVOID_P pMem;
    if (!tgMM_OS__Preload_Process_Init_Complete())
    {
        tgMM_OS__Preload_Process_Init();
    };
    pMem = tgMM_Malloc( ETgMM_ALLOCATOR_MIMALLOC, size, 0 );
    return pMem;
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgATTRIBUTE_RESTRICT TgDLL_EXPORT void* 
mi_calloc(size_t count, size_t size)  TgATTRIBUTE_NO_EXCEPT TgATTRIBUTE_MALLOC TgATTRIBUTE_ALLOC_SIZE2(1,2);

TgATTRIBUTE_RESTRICT void* mi_calloc(size_t count, size_t size) TgATTRIBUTE_NO_EXCEPT
{
    TgVOID_P pMem;
    if (!tgMM_OS__Preload_Process_Init_Complete())
    {
        tgMM_OS__Preload_Process_Init();
    };
    pMem = tgMM_Malloc( ETgMM_ALLOCATOR_MIMALLOC, count*size, 0 );
    tgMM_Set_U08_0x00( pMem, count*size );
    return pMem;
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgDLL_EXPORT void* 
mi_realloc(void* p, size_t newsize) TgATTRIBUTE_NO_EXCEPT TgATTRIBUTE_ALLOC_SIZE1(2);

void* mi_realloc(void* p, size_t newsize) TgATTRIBUTE_NO_EXCEPT
{
    TgVOID_P pMem;
    if (!tgMM_OS__Preload_Process_Init_Complete())
    {
        tgMM_OS__Preload_Process_Init();
    };
    pMem = tgMM_Realloc( ETgMM_ALLOCATOR_MIMALLOC, p, newsize, 0 );
    return pMem;
}

TgEXTN TgDLL_EXPORT void* 
mi_expand(void* p, size_t newsize) TgATTRIBUTE_NO_EXCEPT TgATTRIBUTE_ALLOC_SIZE1(2);

void* mi_expand(void* p, size_t newsize) TgATTRIBUTE_NO_EXCEPT
{
    tgPM_Abort();
    (void)p;
    (void)newsize;
    return nullptr;
}

TgEXTN TgDLL_EXPORT void 
mi_free(void* pMem) TgATTRIBUTE_NO_EXCEPT;

void mi_free(void* pMem) TgATTRIBUTE_NO_EXCEPT
{
    tgMM_Free( ETgMM_ALLOCATOR_MIMALLOC, pMem );
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgDLL_EXPORT size_t 
mi_usable_size(const void* p) TgATTRIBUTE_NO_EXCEPT;

size_t mi_usable_size(const void* p) TgATTRIBUTE_NO_EXCEPT
{
    tgPM_Abort();
    (void)p;
    return 0;
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgATTRIBUTE_RESTRICT TgDLL_EXPORT void* 
mi_new_nothrow(size_t size) TgATTRIBUTE_NO_EXCEPT TgATTRIBUTE_MALLOC TgATTRIBUTE_ALLOC_SIZE1(1);

TgATTRIBUTE_RESTRICT void* mi_new_nothrow(size_t size) TgATTRIBUTE_NO_EXCEPT
{
    tgPM_Abort();
    (void)size;
    return nullptr;
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgDLL_EXPORT bool 
mi_is_in_heap_region(const void* p) TgATTRIBUTE_NO_EXCEPT;

bool mi_is_in_heap_region(const void* p) TgATTRIBUTE_NO_EXCEPT
{
    tgPM_Abort();
    (void)p;
    return false;
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgATTRIBUTE_RESTRICT TgDLL_EXPORT void* 
mi_malloc_aligned( size_t size, size_t alignment) TgATTRIBUTE_NO_EXCEPT TgATTRIBUTE_MALLOC TgATTRIBUTE_ALLOC_SIZE1(1) TgATTRIBUTE_ALLOC_ALIGN(2);

TgATTRIBUTE_RESTRICT void* mi_malloc_aligned( size_t size, size_t alignment) TgATTRIBUTE_NO_EXCEPT
{
    tgPM_Abort();
    (void)size;
    (void)alignment;
    return nullptr;
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgDLL_EXPORT void* 
mi_realloc_aligned(void* p, size_t newsize, size_t alignment) TgATTRIBUTE_NO_EXCEPT TgATTRIBUTE_ALLOC_SIZE1(2) TgATTRIBUTE_ALLOC_ALIGN(3);

void* mi_realloc_aligned(void* p, size_t newsize, size_t alignment) TgATTRIBUTE_NO_EXCEPT
{
    tgPM_Abort();
    (void)p;
    (void)newsize;
    (void)alignment;
    return nullptr;
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgDLL_EXPORT void* 
mi_aligned_recalloc( void* p, size_t newcount, size_t size, size_t alignment) TgATTRIBUTE_NO_EXCEPT;

TgATTRIBUTE_NO_DISCARD void* mi_aligned_recalloc( void* p, size_t newcount, size_t size, size_t alignment) TgATTRIBUTE_NO_EXCEPT
{
    tgPM_Abort();
    (void)p;
    (void)newcount;
    (void)size;
    (void)alignment;
    return nullptr;
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgATTRIBUTE_RESTRICT TgDLL_EXPORT void* 
mi_malloc_aligned_at(size_t size, size_t alignment, size_t offset) TgATTRIBUTE_NO_EXCEPT TgATTRIBUTE_MALLOC TgATTRIBUTE_ALLOC_SIZE1(1);

/* Used in Release Build - For Windows specific allocation functions we will go directly to Mimalloc */
TgATTRIBUTE_RESTRICT void* mi_malloc_aligned_at( size_t size, size_t alignment, size_t offset) TgATTRIBUTE_NO_EXCEPT
{
    TgVOID_P pMem;
    if (!tgMM_OS__Preload_Process_Init_Complete())
    {
        tgMM_OS__Preload_Process_Init();
    };
    (void)tgMM_MI__Malloc_Aligned_At( &pMem, size, alignment, offset );
    return pMem;
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgDLL_EXPORT void* 
mi_realloc_aligned_at(void* p, size_t newsize, size_t alignment, size_t offset) TgATTRIBUTE_NO_EXCEPT TgATTRIBUTE_ALLOC_SIZE1(2);

void* mi_realloc_aligned_at(void* p, size_t newsize, size_t alignment, size_t offset) TgATTRIBUTE_NO_EXCEPT
{
    tgPM_Abort();
    (void)p;
    (void)newsize;
    (void)alignment;
    (void)offset;
    return nullptr;
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgDLL_EXPORT void* 
mi_aligned_offset_recalloc(void* p, size_t newcount, size_t size, size_t alignment, size_t offset) TgATTRIBUTE_NO_EXCEPT;

void* mi_aligned_offset_recalloc(void* p, size_t newcount, size_t size, size_t alignment, size_t offset) TgATTRIBUTE_NO_EXCEPT
{
    tgPM_Abort();
    (void)p;
    (void)newcount;
    (void)size;
    (void)alignment;
    (void)offset;
    return nullptr;
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgATTRIBUTE_RESTRICT TgDLL_EXPORT void* 
mi_aligned_alloc(size_t alignment, size_t size) TgATTRIBUTE_NO_EXCEPT TgATTRIBUTE_MALLOC TgATTRIBUTE_ALLOC_SIZE1(2) TgATTRIBUTE_ALLOC_ALIGN(1);

TgATTRIBUTE_RESTRICT void* mi_aligned_alloc( size_t alignment, size_t size) TgATTRIBUTE_NO_EXCEPT
{
    tgPM_Abort();
    (void)alignment;
    (void)size;
    return nullptr;
}

TgEXTN TgATTRIBUTE_NO_DISCARD TgDLL_EXPORT void*
mi_recalloc(void* pMem, size_t newcount, size_t size) TgATTRIBUTE_NO_EXCEPT TgATTRIBUTE_ALLOC_SIZE2(2,3);

void* mi_recalloc(void* pMem, size_t newcount, size_t size) TgATTRIBUTE_NO_EXCEPT
{
    size_t oldsize = tgMM_Size(ETgMM_ALLOCATOR_MIMALLOC, pMem);
    if (oldsize >= newcount*size)
    {
        return pMem;
    }
    pMem = tgMM_Realloc( ETgMM_ALLOCATOR_MIMALLOC, pMem, newcount*size, 0 );
    tgMM_Set_U08_0x00( (TgUINT_E08_P)pMem+oldsize, newcount*size - oldsize);
    return pMem;
}

#endif
