/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Common - Mem MGR.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Platform Functions                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Determine the number of bytes in the default (standard) memory page of the OS memory manager.
    @return Integer holding the number of bytes in the default (standard) memory page of the OS memory manager. */
TgEXTN TgUINT_F32
tgMM_PM_Page_Size( TgVOID );

/** @brief Function wrapper for the operating system virtual memory allocation. 
    @param [in] ARG0 Integer holding the amount of memory to allocate.
    @return Pointer to the block of memory allocated (may not be committed), or NULL otherwise. */
TgEXTN TgVOID_P
tgMM_PM_Virtual_Reserve(
    TgRSIZE_C ARG0 );

/** @brief Function wrapper for the operating system virtual memory commit. 
    @param [in] ARG0 Pointer to the start of the memory to commit.
    @param [in] ARG1 Integer holding the amount of memory to commit.
    @return Pointer to the block of memory committed, or NULL otherwise. */
TgEXTN TgVOID_P
tgMM_PM_Virtual_Commit(
    TgVOID_PC ARG0, TgRSIZE_C ARG1 );

/** @brief Function wrapper for the operating system free. 
    @param [in] ARG0 Pointer to the start of the memory to free. */
TgEXTN TgVOID
tgMM_PM_Virtual_Free(
    TgVOID_PC ARG0 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgMM_PM_Page_Size -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F32 tgMM_PM_Page_Size( TgVOID )
{
    return (tgSI_SYSTEM_Page_Size());
}


/* ---- tgMM_PM_Virtual_Reserve -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_PM_Virtual_Reserve( TgRSIZE_C iSize )
{
#if defined(TgBUILD_UNIVERSAL__UWP)
    return (g_pfnVirtualAllocFromApp( nullptr, iSize, 0x2000, 0x04 ));
#else
    return (g_pfnVirtualAlloc( nullptr, iSize, 0x2000, 0x04 ));
#endif
}


/* ---- tgMM_PM_Virtual_Commit --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_PM_Virtual_Commit( TgVOID_PC pMem, TgRSIZE_C iSize )
{
#if defined(TgBUILD_UNIVERSAL__UWP)
    TgVOID_PC pCheck = g_pfnVirtualAllocFromApp( pMem, iSize, 0x1000u | (nullptr == pMem ? 0x2000u : 0), 0x04u );
#else
    TgVOID_PC pCheck = g_pfnVirtualAlloc( pMem, iSize, 0x1000u | (nullptr == pMem ? 0x2000u : 0), 0x04u );
#endif
    TgCRITICAL( (0 == pMem) || (0 == pCheck) || (pCheck == (TgVOID_P)((TgUINT_PTR)pMem & (~(TgUINT_PTR)(tgMM_Page_Size() - 1)))) );
    return (pCheck);
}


/* ---- tgMM_PM_Virtual_Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_PM_Virtual_Free( TgVOID_PC pMem )
{
    TgVERIFY( 0 != g_pfnVirtualFree( pMem, 0, 0x8000 ) );
}


