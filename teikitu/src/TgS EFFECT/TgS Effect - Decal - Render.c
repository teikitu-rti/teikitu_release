/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Decal - Render.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS Effect - Render.inl"


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgFORCEINLINE TgVOID
tgFX_Effect__Decal__Render_Write_Quad_00(
    STg2_KN_GPU_Vertex_Particle_00_P, STg2_FX__Decal_CP, TgRSIZE_C  );

TgFORCEINLINE TgVOID
tgFX_Effect__Decal__Render_Write_Quad_01(
    STg2_KN_GPU_Vertex_Particle_01_P, STg2_FX__Decal_CP, TgRSIZE_C  );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Effect__Decal__Render_Write_Quad_00 --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgVOID tgFX_Effect__Decal__Render_Write_Quad_00( STg2_KN_GPU_Vertex_Particle_00_P psVert, STg2_FX__Decal_CP psDecal, TgRSIZE_C nuiMaxVert )
{
    for (TgRSIZE uiVert = 0; uiVert < nuiMaxVert; ++uiVert)
    {
        TgVEC_F32_04_1                    vUV;

        vUV = tgMH_MAD_F32_04_1( psDecal->m_sExtend.m_psVert[uiVert].m_vUV_A, psDecal->m_sExtend.m_vUV_01_Scale, psDecal->m_sExtend.m_vUV_01_Constant );

        psVert[uiVert].m_vS0 = psDecal->m_sExtend.m_psVert[uiVert].m_vS0_W;
        psVert[uiVert].m_vUV = vUV;
        psVert[uiVert].m_vCL = psDecal->m_sExtend.m_vColour;
    };
}


/* ---- tgFX_Effect__Decal__Render_Write_Quad_00 --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgVOID tgFX_Effect__Decal__Render_Write_Quad_01( STg2_KN_GPU_Vertex_Particle_01_P psVert, STg2_FX__Decal_CP psDecal, TgRSIZE_C nuiMaxVert )
{
    for (TgRSIZE uiVert = 0; uiVert < nuiMaxVert; ++uiVert)
    {
        TgVEC_F32_04_1                    vUV;

        vUV = tgMH_MAD_F32_04_1( psDecal->m_sExtend.m_psVert[uiVert].m_vUV_A, psDecal->m_sExtend.m_vUV_01_Scale, psDecal->m_sExtend.m_vUV_01_Constant );

        psVert[uiVert].m_vS0 = psDecal->m_sExtend.m_psVert[uiVert].m_vS0_W;
        psVert[uiVert].m_vT0 = psDecal->m_sExtend.m_psVert[uiVert].m_vT0;
        psVert[uiVert].m_vB0 = psDecal->m_sExtend.m_psVert[uiVert].m_vB0;
        psVert[uiVert].m_vUV = vUV;
        psVert[uiVert].m_vCL = psDecal->m_sExtend.m_vColour;
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define ENABLE_RELOAD_GUARD
#define T(A) A##_00
#include __FILE__
#undef T
#define T(A) A##_01
#include __FILE__
#undef T
#undef ENABLE_RELOAD_GUARD

#else

/* ---- T(tgFX__Render__Decal_Render_Generate_Particle) -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F32 T(tgFX__Render__Decal_Render_Generate_Particle)( STg2_FX_Rnd_Output_PC psRndOut, STg2_RN_Particle_Header_PC psHeader, STg2_FX__Decal_P psDecal )
{
    union
    {
        TgUINT_F08_P                        pui;
        T(STg2_KN_GPU_Vertex_Particle)*         ps;
    }                                   sVert;
    TgUINT_F32                          nuiMaxVert;

    sVert.pui = psRndOut->m_puiBuffer + psHeader->m_uiBuffer_Offset;
    nuiMaxVert = (TgUINT_F32)(psHeader->m_nbyVertex / sizeof( T(STg2_KN_GPU_Vertex_Particle) ));
    TgERROR( nuiMaxVert >= 3 );

    nuiMaxVert = tgCM_MIN_U32( nuiMaxVert, (TgUINT_F32)psDecal->m_sExtend.m_nuiVert );

    tgRN_Calc_UV_Animation_F32_04_1( &psDecal->m_sExtend.m_vUV_01_Constant, &psDecal->m_sExtend.m_vUV_01_Scale, psDecal->m_tiMaterial, psRndOut->m_uDT.m_vF32_04_1, psDecal->m_vLive_Time );
    T(tgFX_Effect__Decal__Render_Write_Quad)( sVert.ps, psDecal, nuiMaxVert );

    return (nuiMaxVert);
}


/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* == Effect ===================================================================================================================================================================== */

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
