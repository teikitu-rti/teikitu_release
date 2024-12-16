/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics [Unit Test] - Internal.h
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
#include "TgS Partition.h"
#include "TgS Kernel.h"
#include "TgS Kernel [GPU].h"

#include "TgS Collision.h"
#include "TgS Partition.h"
#include "TgS Path-AI.h"

#include "TgS Utility.h"

#include "TgS Animation.h"
#include "TgS Input.h"
#include "TgS Physics.h"
#include "TgS Render.h"
#include "TgS Sound.h"

#include "../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h"

#define NULL 0
#include <string.h> /** memcmp, used for low level test comparisons */
#undef NULL

#include "TgS COMMON/TgS Common.inl"

#define TgS_UNIT_TEST__PHYSICS
#define TgS_UNIT_TEST__INPUT /* Enable Input Processing for this demo/test. */
#define TgS_RING_LEVEL 2
#define KTgMAX_TEST_OBJECTS 128

TgEXTN TgVOID                               tgCM_Unit_Test_Register( TgVOID );

typedef struct
{
    TgVEC_S_F32_04_4                    m_mW2C, m_mC2S;
    TgVEC_S_F32_04_1                    scene_light_ambient;
    struct Light_Data
    {
        TgVEC_S_F32_04_1                    origin_and_range;
        TgVEC_S_F32_04_1                    colour;
    }                                   scene_lights[8];
    TgUINT_E32                          scene_num_lights;
} SceneConstantBuffer;

TgEXTN SceneConstantBuffer          g_sSceneConstantBuffer;
TgEXTN TgPH_WORLD_ID                g_tiPH_World;
TgEXTN TgPH_BODY_ID                 g_tiPH_BY0, g_tiPH_BY1, g_atiPH_BY2[KTgMAX_TEST_OBJECTS];
TgEXTN TgPH_FORM_ID                 g_atiPH_FM0[5], g_tiPH_FM1, g_atiPH_FM2[KTgMAX_TEST_OBJECTS];


/* =============================================================================================================================================================================== */
#endif

