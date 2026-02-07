/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision [Unit Test] - Internal.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   4.51 | »GUID« A9981407-3EC9-42AF-8B6F-8BE6DD919615                                                                                                                 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_UNIT_TEST_INTERNAL_H)
#define TGS_COLLISION_UNIT_TEST_INTERNAL_H

#include "TgS Collision.h"

#include "../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h"

#define NULL 0
#include <string.h> /** memcmp, used for low level test comparisons */
#undef NULL

#include "TgS COMMON/TgS Common.inl"

#define TgS_UNIT_TEST__COMMON
#define TgS_UNIT_TEST__COLLISION
#define TgS_RING_LEVEL -1

TgEXTN TgVOID                               tgCM_Unit_Test_Register( TgVOID );


/* =============================================================================================================================================================================== */
#endif

