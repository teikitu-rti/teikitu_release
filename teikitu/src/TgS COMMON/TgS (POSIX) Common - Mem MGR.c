/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (POSIX) Common - Mem MGR.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include <unistd.h>
#include <stdlib.h>
#include <mach/mach_init.h>
#include <mach/vm_map.h>

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Platform Functions                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

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
    @param [in] ARG0 Integer holding the amount of memory to commit.
    @return Pointer to the block of memory committed, or NULL otherwise. */
TgEXTN TgVOID_P
tgMM_PM_Virtual_Commit( 
    TgVOID_PC ARG0, TgRSIZE_C ARG1 );

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
TgUINT_F32 tgMM_PM_Page_Size( TgVOID )
{
    return ((TgUINT_F32)getpagesize());
}


/* ---- tgMM_PM_Virtual_Reserve -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID_P tgMM_PM_Virtual_Reserve( TgRSIZE_C iSize )
{
    TgVOID_P                            pMem;

    posix_memalign( &pMem, tgMM_PM_Page_Size(), iSize );
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
TgVOID_P tgMM_PM_Virtual_Commit( TgVOID_PC pMem, TgRSIZE_C iSize )
{
    return (nullptr == pMem ? tgMM_PM_Virtual_Reserve( iSize ) : pMem);
}


/* ---- tgMM_PM_Virtual_Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgMM_PM_Virtual_Free( TgVOID_PC pMem )
{
    free( pMem );
}
