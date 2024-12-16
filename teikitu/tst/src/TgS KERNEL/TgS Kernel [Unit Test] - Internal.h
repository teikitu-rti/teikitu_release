/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [Unit Test] - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_KERNEL_UNIT_TEST_INTERNAL_H)
#define TGS_KERNEL_UNIT_TEST_INTERNAL_H

#include "TgS Common.h"

#include "TgS Ring 0 - Type.h"
#include "TgS Ring 2 - Type.h"

#include "TgS Collision.h"

#include "TgS Kernel.h"
#include "TgS Kernel [GPU].h"
#include "TgS KERNEL/TgS Kernel [GPU] [EXT].h"
#include "TgS Utility.h"

#include "../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h"

#define NULL 0
#include <string.h> /** memcmp, used for low level test comparisons */
#undef NULL

#include "TgS COMMON/TgS Common.inl"

#define TgS_UNIT_TEST__KERNEL
#define TgS_RING_LEVEL 2

TgEXTN TgVOID TEST__CLOSURE__FCN__KN( TgVOID );


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgVOID                               tgCM_Unit_Test_Register( TgVOID );

TgEXTN TgVOID                               tgCM_Unit_Test_Register_KERNEL( TgVOID );
TgEXTN TgVOID                               tgCM_Unit_Test_Register_KERNEL_GPU( TgVOID );
TgEXTN TgVOID                               tgCM_Unit_Test_Register_KERNEL_OS( TgVOID );


/* =============================================================================================================================================================================== */
#endif
