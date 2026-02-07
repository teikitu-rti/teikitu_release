/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Mimalloc.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR)

/* Using mimalloc and the mimalloc redirector for our own purposes takes a few steps. Unfortunately, the redirector is only released in binary format and so there is no way to 
   create our own without reverse-engineering and hoping that all the needed function offsets were found. Instead, we take the existing mimalloc redirector, and hex-edit the
   binary to include the name of our own dll. You can use a tool similar to mimalloc minject as well. Once the redirector has been modified to load your own memory manager DLL,
   rename the redirector DLL to one of your choice. Use dumpbin to list all exports and then import that with lib to create a new matching library. It will then be necssary
   to implement some number of the mimalloc functions (TgS Common - Mem MGR - Override.c) that the redirector imports. Define these in such a way that they map to your own 
   memory maanger. The next step, assuming you want to use mimalloc yourself, is to wrap a static library compilation of mimalloc into a DLL. You will have to make a few
   changes as you want to maintain the DLL execution flow even when compiling as a static library. Wire up your handling of the redirector to include mimalloc as well. The DLL
   wrapping is necessary to avoid duplicate symbols (and also why mimalloc has to be compiled as a static library to avoid the function exports). */

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
#if defined(TgBUILD_MIMALLOC__HAS_CONSOLE)
TgVOID                                      (*g_pfnCN_PrintF)( TgUINT_E32_C, TgCHAR_U8_CP TgANALYSIS_NO_NULL, ... ) = nullptr;
#endif



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgS_STAT__COMMON
static TgVOID CDECL
tgMM_MI_Output(
    const char *msg, void * arg );
/*# TgS_STAT__COMMON */
#endif



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgMM_MI__Init_MGR -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_MI__Init_MGR( TgVOID )
{
    return (KTgS_OK);
}


/* ---- tgMM_MI__Free_MGR -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_MI__Free_MGR( TgVOID )
{
    return (KTgS_OK);
}


/* ---- tgMM_MI__Stats ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgVOID tgMM_MI__Stats( TgRSIZE (pfnIO_PrintF)( STg2_Output_PC ARG0, TgCHAR_U8_CPC ARG1, ... ), STg2_Output_PC psOUT )
{
    TgPARAM_CHECK( nullptr!= pfnIO_PrintF );
    TgPARAM_CHECK( nullptr!= psOUT );

    pfnIO_PrintF( psOUT, u8"\n");
    pfnIO_PrintF( psOUT, u8"*******************************************************************************************************************************\n");
    pfnIO_PrintF( psOUT, u8"                                                        MIMALLOC STATS                                                         \n");
    pfnIO_PrintF( psOUT, u8"*******************************************************************************************************************************\n");
    pfnIO_PrintF( psOUT, u8"\n");
    mi_stats_print_out( tgMM_MI_Output, (TgVOID_P) psOUT );
    pfnIO_PrintF( psOUT, u8"\n");
    pfnIO_PrintF( psOUT, u8"\n");
}
/*# TgS_STAT__COMMON */
#endif


/* ---- tgMM_MI__Size ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_MI__Size( TgUINT_E32_P pnbyReserve, TgUINT_E32_P pnbyAllocated, TgVOID_CPC pMem )
{
    TgRSIZE_C                           nbySize = mi_malloc_size( pMem );

    TgPARAM_CHECK( nullptr != pnbyReserve );
    TgPARAM_CHECK( nullptr != pnbyAllocated );
    TgPARAM_CHECK( nullptr != pMem );
    TgCRITICAL( nbySize <= KTgMAX_U32 );

    *pnbyReserve = (TgUINT_E32)nbySize;
    *pnbyAllocated = (TgUINT_E32)nbySize;
    return (KTgS_OK);
}


/* ---- tgMM_MI__Malloc ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_MI__Malloc( TgMEM_INFO_HEADER_P psInfo, TgVOID_PP ppReturn, TgRSIZE_C uiSize, TgRSIZE_C uiAlignment )
{
    TgRSIZE                             nbySize;

    TgPARAM_CHECK( nullptr != psInfo );
    TgPARAM_CHECK( nullptr != ppReturn );

    *ppReturn = mi_malloc_aligned( uiSize, uiAlignment < 8 ? 8 : uiAlignment );
    nbySize = mi_malloc_size( *ppReturn );
    TgCRITICAL( nbySize <= KTgMAX_U32 );

    psInfo->m_uiSize = (TgUINT_E32)nbySize;
    psInfo->m_uiFlags = 0;
    psInfo->m_enAllocator = ETgMM_ALLOCATOR_MIMALLOC;
    return (*ppReturn != nullptr ? KTgS_OK : KTgE_FAIL);
}


/* ---- tgMM_MI__Free ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_MI__Free( TgMEM_INFO_HEADER_P psInfo, TgVOID_PC pMem )
{
    TgRSIZE_C                           nbySize = mi_malloc_size( pMem );

    TgPARAM_CHECK( nullptr != psInfo );
    TgPARAM_CHECK( nullptr != pMem );
    TgCRITICAL( nbySize <= KTgMAX_U32 );

    psInfo->m_uiSize = (TgUINT_E32)nbySize;
    psInfo->m_uiFlags = 0;
    psInfo->m_enAllocator = ETgMM_ALLOCATOR_MIMALLOC;
    mi_free( pMem );
    return (KTgS_OK);
}


/* ---- tgMM_MI__Realloc --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_MI__Realloc( TgMEM_INFO_HEADER_P psNew_Info, TgVOID_PP ppNew, TgMEM_INFO_HEADER_P psOld_Info, TgVOID_PC pOld, TgRSIZE_C uiNewSize, TgRSIZE_C uiNewAlignment )
{
    TgRSIZE                             nbySize;

    TgPARAM_CHECK( nullptr != psNew_Info );
    TgPARAM_CHECK( nullptr != ppNew );
    TgPARAM_CHECK( nullptr != psOld_Info );
    TgPARAM_CHECK( nullptr != pOld );

    nbySize = mi_malloc_size( pOld );
    psOld_Info->m_uiSize = (TgUINT_E32)nbySize;
    psOld_Info->m_uiFlags = 0;
    psOld_Info->m_enAllocator = ETgMM_ALLOCATOR_MIMALLOC;

    *ppNew = mi_realloc_aligned( pOld, uiNewSize, uiNewAlignment < 8 ? 8 : uiNewAlignment );

    nbySize = mi_malloc_size( *ppNew );
    psNew_Info->m_uiSize = (TgUINT_E32)nbySize;
    psNew_Info->m_uiFlags = 0;
    psNew_Info->m_enAllocator = ETgMM_ALLOCATOR_MIMALLOC;

    return (*ppNew != nullptr ? KTgS_OK : KTgE_FAIL);
}


/* ---- tgMM_MI__Internal__Process_Load ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_MI__Internal__Process_Load( TgVOID )
{
    mi_process_load();
    mi_register_output( nullptr, nullptr );
}


/* ---- tgMM_MI__Internal__Process_Init ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_MI__Internal__Process_Init( TgVOID )
{
    mi_process_init();
}


/* ---- tgMM_MI__Internal__Thread_Done ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_MI__Internal__Thread_Done( TgVOID ) TgATTRIBUTE_NO_EXCEPT
{
    mi_thread_done();
}


/* ---- tgMM_MI__Internal__Process_Done ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID CDECL tgMM_MI__Internal__Process_Done( TgVOID )
{
    mi_process_done();
}


/* ---- tgMM_MI_Set_CN_PrintF ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_MI_Set_CN_PrintF( TgATTRIBUTE_UNUSED TgVOID (*pfnCN_PrintF)( TgUINT_E32_C, TgCHAR_U8_CP TgANALYSIS_NO_NULL, ... ) )
{
#if defined(TgBUILD_PRELOAD__HAS_CONSOLE)
    g_pfnCN_PrintF = pfnCN_PrintF;
#endif
}


/* ---- tgMM_MI__Malloc_Aligned_At ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgMM_MI__Malloc_Aligned_At( TgVOID_PP ppReturn, TgRSIZE_C uiSize, TgRSIZE_C uiAlignment, TgRSIZE_C uiOffset )
{
    TgPARAM_CHECK( nullptr != ppReturn );

    *ppReturn = mi_malloc_aligned_at( uiSize, uiAlignment, uiOffset );
    return (*ppReturn != nullptr ? KTgS_OK : KTgE_FAIL);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgS_STAT__COMMON
static TgVOID CDECL tgMM_MI_Output( const char *msg, TgVOID_P pOut )
{
    union
    {
        TgVOID_P                            pv;
        STg2_Output_P                       ps;
    }                                   uOUT;

    if (nullptr == pOut || nullptr == msg)
    {
        return;
    };

    uOUT.pv = pOut;
    (void)(*uOUT.ps->m_pfnWrite)(uOUT.ps, KTgMAX_RSIZE, (TgUINT_E08_CP)msg, KTgMAX_RSIZE);
}
/*# TgS_STAT__COMMON */
#endif

/* =============================================================================================================================================================================== */
/* defined(TgBUILD_FEATURE__MIMALLOC_ALLOCATOR) */
#endif
