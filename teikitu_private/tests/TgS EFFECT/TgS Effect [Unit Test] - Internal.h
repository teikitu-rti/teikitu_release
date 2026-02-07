/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect [Unit Test] - Internal.h
    »Author«    Andrew Aye (EMail: mailto:andrew.aye@gmail.com, Web: http://www.andrewaye.com)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS_EFFECT_UNIT_TEST_INTERNAL_H)
#define TGS_EFFECT_UNIT_TEST_INTERNAL_H

#include "TgS Common.h"

#include "TgS Collision.h"
#include "TgS Partition.h"
#include "TgS Path-AI.h"

#include "TgS Kernel.h"
#include "TgS Kernel [GPU].h"
#include "TgS Utility.h"

#include "TgS Animation.h"
#include "TgS Input.h"
#include "TgS Physics.h"
#include "TgS Render.h"
#include "TgS Sound.h"

#include "TgS Script.h"
#include "TgS Object.h"
#include "TgS Set.h"
#include "TgS Effect.h"

#include "../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h"

#define NULL 0
#include <string.h> /** memcmp, used for low level test comparisons */
#undef NULL

#include "TgS COMMON/TgS Common.inl"

#define TgS_UNIT_TEST__EFFECT
#define TgS_RING_LEVEL 3

TgEXTN TgVOID                               tgCM_Unit_Test_Register( TgVOID );

typedef struct
{
    TgVEC_S_F32_04_4                    m_avW2C, m_avC2S;
    TgVEC_S_F32_04_1                    scene_light_ambient;
    struct Light_Data
    {
        TgVEC_S_F32_04_1                    origin_and_range;
        TgVEC_S_F32_04_1                    colour;
    }                                   scene_lights[8];
    TgUINT_E32                          scene_num_lights;
} SceneConstantBuffer;

TgEXTN SceneConstantBuffer g_sSceneConstantBuffer;


/* =============================================================================================================================================================================== */
#endif

