/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Path-AI [Unit Test] - Internal.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PLATFORM_EFFECT_UNITTEST_INTERNAL_H)
#define TGS_PLATFORM_EFFECT_UNITTEST_INTERNAL_H

#include "TgS Common.h"
#include "TgS Collision.h"

#include "../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h"

#define NULL 0
#include <string.h> /** memcmp, used for low level test comparisons */
#undef NULL

#include "TgS COMMON/TgS Common.inl"

#define TgS_UNIT_TEST__PATH_AI
#define TgS_RING_LEVEL 0

TgEXTN TgVOID                               tgCM_Unit_Test_Register( TgVOID );

/* =============================================================================================================================================================================== */
#endif

