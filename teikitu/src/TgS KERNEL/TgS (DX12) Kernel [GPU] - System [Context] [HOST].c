/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (DX12) Kernel - System [GPU] [Context] [HOST].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

// Precompiled shaders.
CLANG_WARN_DISABLE_PUSH(missing-variable-declarations)
#include "Standard_Particle_00_PS_FX_vs.hlsl.h"
#include "Standard_Particle_01_PS_FX_vs.hlsl.h"
#include "Standard_Debug_Geom_00_PS_P_vs.hlsl.h"
#include "Standard_Debug_Geom_01_PS_PC_vs.hlsl.h"
#include "Standard_Debug_Geom_02_PS_PNC_vs.hlsl.h"
#include "Standard_Debug_Geom_02I_PS_PNC_vs.hlsl.h"
#include "Standard_Debug_Geom_03_PS_PNC_vs.hlsl.h"
#include "Standard_Debug_Line_PS_PC_vs.hlsl.h"
#include "Standard_Debug_UI_PS_UI_vs.hlsl.h"
#include "Standard_Debug_UI_Text_PS_UIT_vs.hlsl.h"

#include "Standard_FX_ps.hlsl.h"
#include "Standard_Debug_P_ps.hlsl.h"
#include "Standard_Debug_PC_ps.hlsl.h"
#include "Standard_Debug_PCG_ps.hlsl.h"
#include "Standard_Debug_PN_ps.hlsl.h"
#include "Standard_Debug_PNC_ps.hlsl.h"
#include "Standard_Debug_UI_ps.hlsl.h"
#include "Standard_Debug_UIG_ps.hlsl.h"
#include "Standard_Debug_UIT_ps.hlsl.h"
#include "Standard_Test_PNC_ps.hlsl.h"
CLANG_WARN_DISABLE_POP(missing-variable-declarations)
#define _MACRO_LOAD_SHADER(A,B,C) A.m_puiData = g_uiStandard_##B##_Compiled; A.m_nuiData = sizeof(g_uiStandard_##B##_Compiled); A.m_uszName = u8##C
#define MACRO_LOAD_SHADER(A,B) _MACRO_LOAD_SHADER(A,B,#B)




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU_EXT__Host__Init ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Host__Init( TgVOID )
{
    STg2_KN_GPU_VS_DESC                 sVS_DESC;
    STg2_KN_GPU_PS_DESC                 sPS_DESC;

    MACRO_LOAD_SHADER( sVS_DESC, Debug_UI_PS_UI_VS );
    g_sKN_GPU_CXT_HOST.m_atiVS[ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_UI] = tgKN_GPU_VS__Load_From_Memory( &sVS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sVS_DESC, Debug_Line_PS_PC_VS );
    g_sKN_GPU_CXT_HOST.m_atiVS[ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_LINE] = tgKN_GPU_VS__Load_From_Memory( &sVS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sVS_DESC, Debug_Geom_00_PS_P_VS );
    g_sKN_GPU_CXT_HOST.m_atiVS[ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_GEOM_00] = tgKN_GPU_VS__Load_From_Memory( &sVS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sVS_DESC, Debug_Geom_01_PS_PC_VS );
    g_sKN_GPU_CXT_HOST.m_atiVS[ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_GEOM_01] = tgKN_GPU_VS__Load_From_Memory( &sVS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sVS_DESC, Debug_Geom_02_PS_PNC_VS );
    g_sKN_GPU_CXT_HOST.m_atiVS[ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_GEOM_02] = tgKN_GPU_VS__Load_From_Memory( &sVS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sVS_DESC, Debug_Geom_03_PS_PNC_VS );
    g_sKN_GPU_CXT_HOST.m_atiVS[ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_GEOM_03] = tgKN_GPU_VS__Load_From_Memory( &sVS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sVS_DESC, Particle_00_PS_FX_VS );
    g_sKN_GPU_CXT_HOST.m_atiVS[ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_00] = tgKN_GPU_VS__Load_From_Memory( &sVS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sVS_DESC, Particle_01_PS_FX_VS );
    g_sKN_GPU_CXT_HOST.m_atiVS[ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_01] = tgKN_GPU_VS__Load_From_Memory( &sVS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );

    MACRO_LOAD_SHADER( sVS_DESC, Debug_UI_Text_PS_UIT_VS );
    g_sKN_GPU_CXT_HOST.m_atiVS[ETgKN_GPU_DEFAULT_INPUT_LAYOUT_INSTANCE_VERTEX_UI_TEXT] = tgKN_GPU_VS__Load_From_Memory( &sVS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sVS_DESC, Debug_Geom_02I_PS_PNC_VS );
    g_sKN_GPU_CXT_HOST.m_atiVS[ETgKN_GPU_DEFAULT_INPUT_LAYOUT_INSTANCE_VERTEX_GEOM_02] = tgKN_GPU_VS__Load_From_Memory( &sVS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );

    MACRO_LOAD_SHADER( sPS_DESC, FX_PS );
    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_PARTICLE_00] = tgKN_GPU_PS__Load_From_Memory( &sPS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_PARTICLE_01] = tgKN_GPU_PS__IncRef( g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_PARTICLE_00] );
    MACRO_LOAD_SHADER( sPS_DESC, Debug_UI_PS );
    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_UI] = tgKN_GPU_PS__Load_From_Memory( &sPS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sPS_DESC, Debug_UIG_PS );
    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_UI_WITH_GAMMA] = tgKN_GPU_PS__Load_From_Memory( &sPS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sPS_DESC, Debug_UIT_PS );
    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_TEXT] = tgKN_GPU_PS__Load_From_Memory( &sPS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sPS_DESC, Debug_PC_PS );
    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_LINE] = tgKN_GPU_PS__Load_From_Memory( &sPS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sPS_DESC, Debug_P_PS );
    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_00] = tgKN_GPU_PS__Load_From_Memory( &sPS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sPS_DESC, Debug_PCG_PS );
    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_01_WITH_GAMMA] = tgKN_GPU_PS__Load_From_Memory( &sPS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sPS_DESC, Debug_PNC_PS );
    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_02] = tgKN_GPU_PS__Load_From_Memory( &sPS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );
    MACRO_LOAD_SHADER( sPS_DESC, Test_PNC_PS );
    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_UNIT_TEST_SCENE] = tgKN_GPU_PS__Load_From_Memory( &sPS_DESC, ETgKN_GPU_ALLOCATOR__MAIN_MEMORY );

    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_01] = tgKN_GPU_PS__IncRef( g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_LINE] );
    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_02_INSTANCE] = tgKN_GPU_PS__IncRef( g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_02] );
    g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_03] = tgKN_GPU_PS__IncRef( g_sKN_GPU_CXT_HOST.m_atiPS[ETgKN_GPU_DEFAULT_PSO_DEBUG_GEOM_02] );

    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT_Context__Free_Data ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Host__Free( TgVOID )
{
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiPS); ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiPS[uiIndex].m_uiKI) {
            tgKN_GPU_PS__Release( g_sKN_GPU_CXT_HOST.m_atiPS[uiIndex] );
            g_sKN_GPU_CXT_HOST.m_atiPS[uiIndex] = KTgKN_GPU_PS_ID__INVALID;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiVS); ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiVS[uiIndex].m_uiKI) {
            tgKN_GPU_VS__Release( g_sKN_GPU_CXT_HOST.m_atiVS[uiIndex] );
            g_sKN_GPU_CXT_HOST.m_atiVS[uiIndex] = KTgKN_GPU_VS_ID__INVALID;
        }
    }

    tgKN_GPU_EXT_Enumerate_Free_Resources();
    tgMM_Set_U08_0x00( &g_sKN_GPU_EXT_CXT_HOST, sizeof( STg2_KN_GPU_EXT_CXT_HOST ) );
}
