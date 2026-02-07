/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (VULKAN) Kernel [GPU] - System [Context] [HOST].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    Models:     Claude 3.7, Claude 4.0
    ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

// Precompiled shaders.
TgCLANG_WARN_DISABLE_PUSH(missing-variable-declarations)
TgMSVC_WARN_DISABLE_PUSH(5103)
#include "Default_VLKN_Particle_SC_VWC_00_vert.glsl.h"
#include "Default_VLKN_Particle_SC_VWC_01_vert.glsl.h"
#include "Default_VLKN_Test_SN_VWNC_vert.glsl.h"
#include "Default_VLKN_Particle_VWC_frag.glsl.h"
#include "Default_VLKN_Test_VWNC_frag.glsl.h"
#include "Default_VLKN_Colour_Correction_comp.glsl.h"
#include "Default_VLKN_Luminance_Histogram_comp.glsl.h"
TgMSVC_WARN_DISABLE_POP(5103)
TgCLANG_WARN_DISABLE_POP(missing-variable-declarations)

#define _MACRO_LOAD_SHADER(A,B,C,D) \
{ \
    STg2_KN_GPU_##C##_DESC s##C##_DESC; \
    TgVERIFY(g_sKN_GPU_CXT_HOST.m_nui##C == (TgRSIZE)B); \
    s##C##_DESC.m_puiData = (TgUINT_E08_CP)g_uiDefault_VLKN_##A##_Compiled; \
    s##C##_DESC.m_nuiData = sizeof(g_uiDefault_VLKN_##A##_Compiled); \
    s##C##_DESC.m_uszName = u8##D; \
    g_sKN_GPU_CXT_HOST.m_ati##C[g_sKN_GPU_CXT_HOST.m_nui##C++] = tgKN_GPU_##C##__Load_From_Memory( & s##C##_DESC, ETgKN_GPU_RESOURCE_DESCRIPTOR__MAIN_MEMORY ); \
}
#define MACRO_LOAD_SHADER(A,B,C)        _MACRO_LOAD_SHADER(A,B,C,#B)
#define MACRO_LOAD_SHADER_VS(A,B)       MACRO_LOAD_SHADER(A,B,VS)
#define MACRO_LOAD_SHADER_FS(A,B)       MACRO_LOAD_SHADER(A,B,FS)
#define MACRO_LOAD_SHADER_CS(A,B)       MACRO_LOAD_SHADER(A,B,CS)




/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_EXT__Host__Init ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_EXT__Host__Init( TgVOID )
{
    tgCM_UT_LF__RW__Enter_Write_Spin_Block( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );

    MACRO_LOAD_SHADER_VS( Particle_SC_VWC_00_VERT, ETgKN_GPU_SHADER_VS_PARTICLE_SC_VWC_00 )
    MACRO_LOAD_SHADER_VS( Particle_SC_VWC_01_VERT, ETgKN_GPU_SHADER_VS_PARTICLE_SC_VWC_01 )
    MACRO_LOAD_SHADER_VS( Test_SN_VWNC_VERT, ETgKN_GPU_SHADER_VS_TEST_SN_VWNC )

    MACRO_LOAD_SHADER_FS( Particle_VWC_FRAG, ETgKN_GPU_SHADER_FS_PARTICLE_VWC )
    MACRO_LOAD_SHADER_FS( Test_VWNC_FRAG, ETgKN_GPU_SHADER_FS_TEST_VWNC )

    MACRO_LOAD_SHADER_CS( Colour_Correction_COMP, ETgKN_GPU_SHADER_CS_COLOUR_CORRECTION )
    MACRO_LOAD_SHADER_CS( Luminance_Histogram_COMP, ETgKN_GPU_SHADER_CS_LUMINANCE_HISTOGRAM )

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    if (TgFAILED(tgKN_GPU__Host__Init_Debug()))
    {
        tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
        return (KTgE_FAIL);
    }
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
    return (KTgS_OK);
}


/* ---- tgKN_GPU_EXT__Host__Free ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_EXT__Host__Free( TgVOID )
{
    TgRSIZE                             uiIndex;

    tgCM_UT_LF__RW__Enter_Write_Spin_Block( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)
    tgKN_GPU__Host__Free_Debug();
/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiCS); ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiCS[uiIndex].m_uiKI) {
            tgKN_GPU_CS__Release( g_sKN_GPU_CXT_HOST.m_atiCS[uiIndex] );
            g_sKN_GPU_CXT_HOST.m_atiCS[uiIndex] = KTgKN_GPU_CS_ID__INVALID;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiFS); ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiFS[uiIndex].m_uiKI) {
            tgKN_GPU_FS__Release(g_sKN_GPU_CXT_HOST.m_atiFS[uiIndex]);
            g_sKN_GPU_CXT_HOST.m_atiFS[uiIndex] = KTgKN_GPU_FS_ID__INVALID;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiMS); ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiMS[uiIndex].m_uiKI) {
            tgKN_GPU_MS__Release(g_sKN_GPU_CXT_HOST.m_atiMS[uiIndex]);
            g_sKN_GPU_CXT_HOST.m_atiMS[uiIndex] = KTgKN_GPU_MS_ID__INVALID;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiTS); ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiTS[uiIndex].m_uiKI) {
            tgKN_GPU_TS__Release(g_sKN_GPU_CXT_HOST.m_atiTS[uiIndex]);
            g_sKN_GPU_CXT_HOST.m_atiTS[uiIndex] = KTgKN_GPU_TS_ID__INVALID;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiGS); ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiGS[uiIndex].m_uiKI) {
            tgKN_GPU_GS__Release(g_sKN_GPU_CXT_HOST.m_atiGS[uiIndex]);
            g_sKN_GPU_CXT_HOST.m_atiGS[uiIndex] = KTgKN_GPU_GS_ID__INVALID;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiTES); ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiTES[uiIndex].m_uiKI) {
            tgKN_GPU_TES__Release(g_sKN_GPU_CXT_HOST.m_atiTES[uiIndex]);
            g_sKN_GPU_CXT_HOST.m_atiTES[uiIndex] = KTgKN_GPU_TES_ID__INVALID;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiTCS); ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiTCS[uiIndex].m_uiKI) {
            tgKN_GPU_TCS__Release(g_sKN_GPU_CXT_HOST.m_atiTCS[uiIndex]);
            g_sKN_GPU_CXT_HOST.m_atiTCS[uiIndex] = KTgKN_GPU_TCS_ID__INVALID;
        }
    }

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_sKN_GPU_CXT_HOST.m_atiVS); ++uiIndex)
    {
        if (g_sKN_GPU_CXT_HOST.m_atiVS[uiIndex].m_uiKI) {
            tgKN_GPU_VS__Release(g_sKN_GPU_CXT_HOST.m_atiVS[uiIndex]);
            g_sKN_GPU_CXT_HOST.m_atiVS[uiIndex] = KTgKN_GPU_VS_ID__INVALID;
        }
    }

    tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
    tgKN_GPU_Enumerate_Free_Resources();
    tgMM_Set_U08_0x00( &g_sKN_GPU_EXT_CXT_HOST, sizeof( STg2_KN_GPU_VLKN_CXT_HOST ) );
}
