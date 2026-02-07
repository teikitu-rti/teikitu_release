/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (POSIX) Common - Mem MGR.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include <sys/param.h>
#include <sys/mman.h>
#if defined(TgBUILD_HOST_SYSTEM__HMAC)
#include <stdlib.h>
#else
#include <malloc.h>
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Platform Functions                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Determine the number of bytes in the default (standard) memory page of the OS memory manager.
    @return Integer holding the number of bytes in the default (standard) memory page of the OS memory manager. */
TgEXTN TgRSIZE
tgMM_PM_Page_Size( TgVOID );

/** @brief Function wrapper for the operating system virtual memory allocation. 
    @param [in] ARG0 Integer holding the amount of memory to allocate.
    @return Pointer to the block of memory allocated (may not be committed), or NULL otherwise. */
TgEXTN TgVOID_P
tgMM_PM_Virtual_Reserve( 
    TgRSIZE_C ARG0 );

/** @brief Function wrapper for the operating system virtual memory commit. 
    @param [in] ARG0 Pointer to the start of a reserved region, or null for a new allocation.
    @param [in] ARG1 Offset from the pointer base to the start of the region to commit.
    @param [in] ARG2 Size of the region to commit.
    @return Pointer to the block of memory committed, or NULL otherwise. */
TgEXTN TgVOID_P
tgMM_PM_Virtual_Commit(
    TgVOID_PC ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2 );

/** @brief Function wrapper for the operating system free. 
    @param [in] ARG0 Pointer to the start of the memory to free. */
TgEXTN TgVOID
tgMM_PM_Virtual_Free(
    TgVOID_PC ARG0 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgMM_PM_Page_Size -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgMM_PM_Page_Size( TgVOID )
{
    return (0);
    //return ((TgUINT_E32)getpagesize());
}


/* ---- tgMM_PM_Virtual_Reserve -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_PM_Virtual_Reserve( TgRSIZE_C iSize )
{
    TgVOID_P                            pMem;

    pMem = malloc( iSize );
    return (pMem);

//    TgSIZE_ALL                          uiPageSize, uiSize_To_Allocate;
//    TgVOID_P                            pMem;
//    kern_return_t                       err;
//
//    uiPageSize = tgMM_PM_Page_Size();
//    uiSize_To_Allocate = uiPageSize * ((uiSize + uiPageSize - 1) / uiPageSize);
//    err = vm_allocate(  (vm_map_t) mach_task_self(),
//                        (vm_address_t*) &pMem,
//                        uiSize_To_Allocate,
//                        VM_FLAGS_ANYWHERE);
//
//    TgERROR(err == KERN_SUCCESS);
//    if(err != KERN_SUCCESS)
//    {
//       pMem = nullptr;
//    }
//
//    return pMem;
}


/* ---- tgMM_PM_Virtual_Commit --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_PM_Virtual_Commit( TgVOID_PC pMem, TgRSIZE_C uiOffset, TgRSIZE_C uiSize )
{
    (void)uiOffset;
    return (nullptr == pMem ? tgMM_PM_Virtual_Reserve( uiSize ) : pMem);
}


/* ---- tgMM_PM_Virtual_Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_PM_Virtual_Free( TgVOID_PC pMem )
{
    free( pMem );
}
