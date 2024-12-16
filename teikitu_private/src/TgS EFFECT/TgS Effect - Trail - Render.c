/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Trail - Render.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS Effect - Render.inl"


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_FX__Trail__Render_Point,)
{
    /* --------------- Input --------------- */
    STg2_FX__Trail_P                            m_psTrail;
    STg2_FX_Trail__File_Data_CP                 m_psFile_Data;
    TgVEC_F32_04_1                              m_vCam_Up;
    TgVEC_F32_04_1                              m_vCam_Forward;
    TgVEC_F32_04_1                              m_vCL;

    /* --------------- Output -------------- */
    TgVEC_F32_04_1                              m_vS0_W;
    TgVEC_F32_04_1                              m_vS1_W;
    TgVEC_F32_04_1                              m_vT0_W;
    TgVEC_F32_04_1                              m_vB0_W;
    TgVEC_F32_04_1                              m_vScale_U;
    TgVEC_F32_04_1                              m_vN0;
    TgUINT_E32                                  m_uiNext_Point;
    TgUINT_E32                                  m_uiPad0[3];
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgFX_Effect__Trail__Render_Calculate_Point(
    STg2_FX__Trail_P, STg2_FX__Trail__Render_Point_P, TgUINT_E32_C  );

TgFORCEINLINE TgBOOL
tgFX_Effect__Trail__Render_Calculate_Vertex_00(
    STg2_KN_GPU_Vertex_Particle_00_P, STg2_FX__Trail__Render_Point_P );

TgFORCEINLINE TgBOOL
tgFX_Effect__Trail__Render_Calculate_Vertex_01(
    STg2_KN_GPU_Vertex_Particle_01_P, STg2_FX__Trail__Render_Point_P );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgFX_Effect__Trail__Render_Quad_Count ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgFX_Effect__Trail__Render_Quad_Count( STg2_FX__Trail_P psTrail )
{
    STg2_FX__Trail__Extend_Data_P       psExtend;
    TgUINT_E32                          uiPoint;
    TgRSIZE                             nuiQuad;

    psExtend = &(psTrail->m_sExtend);
    if (psExtend->m_uiPoint_Head == psExtend->m_uiPoint_Tail)
    {
        return (0);
    };

    uiPoint = (psExtend->m_uiPoint_Head + KTgFX_MAX_POINTS_IN_TRAIL - 1) % KTgFX_MAX_POINTS_IN_TRAIL;
    nuiQuad = 0;
    while (uiPoint != psExtend->m_uiPoint_Tail)
    {
        ++nuiQuad;
        uiPoint = (uiPoint + KTgFX_MAX_POINTS_IN_TRAIL - 1) % KTgFX_MAX_POINTS_IN_TRAIL;
    };

    TgERROR(nuiQuad < KTgFX_MAX_POINTS_IN_TRAIL);
    return (nuiQuad);
}


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#define ENABLE_RELOAD_GUARD
#define T(A) A##_00
#include __FILE__
#undef T
#define T(A) A##_01
#include __FILE__
#undef T
#undef ENABLE_RELOAD_GUARD




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Effect__Trail__Render_Calculate_Point ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX_Effect__Trail__Render_Calculate_Point( STg2_FX__Trail_P psTrail, STg2_FX__Trail__Render_Point_P psPoint, TgUINT_E32_C uiPoint )
{
    STg2_FX__Trail__Extend_Data_P       psExtend;
    TgVEC_F32_04_1                      vSN0_W;
    TgVEC_F32_04_1                      vSN1_W;
    TgVEC_F32_04_1                      vB1;

    psExtend = &(psTrail->m_sExtend);

    psPoint->m_uiNext_Point = (uiPoint + KTgFX_MAX_POINTS_IN_TRAIL - 1) % KTgFX_MAX_POINTS_IN_TRAIL;
    vSN0_W = psExtend->m_avPos_N2W[uiPoint];
    vSN1_W = psExtend->m_avPos_N2W[psPoint->m_uiNext_Point];

    psPoint->m_vT0_W = tgMH_NORM_F32_04_1( tgMH_SUB_F32_04_1( vSN1_W, vSN0_W ) );
    psPoint->m_vB0_W = tgMH_UCX_F32_04_1( psPoint->m_vCam_Forward, psPoint->m_vT0_W );
    psPoint->m_vScale_U = tgMH_MUL_F32_04_1( tgMH_SET1_F32_04_1( psExtend->m_afU[uiPoint] ), psTrail->m_psFile_Data->m_vScale_U );

    if (uiPoint != psExtend->m_uiPoint_Head)
    {
        TgVEC_F32_04_1_C                    vPrev_S0_W = psPoint->m_vS0_W;
        TgVEC_F32_04_1_C                    vPrev_T0_W = psPoint->m_vT0_W;
        TgVEC_F32_04_1                      vQuad_BI = tgMH_MUL_F32_04_1( psPoint->m_vB0_W, psExtend->m_vWidth );

        psPoint->m_vS0_W = tgMH_ADD_F32_04_1( vSN0_W, vQuad_BI );
        psPoint->m_vS1_W = tgMH_SUB_F32_04_1( vSN0_W, vQuad_BI );
        vB1 = tgMH_NORM_F32_04_1( tgMH_SUB_F32_04_1( psPoint->m_vS1_W, vPrev_S0_W ) );
        psPoint->m_vN0 = tgMH_CX_F32_04_1( vPrev_T0_W, vB1 );
    }
    else
    {
        TgVEC_F32_04_1                      vQuad_BI = tgMH_MUL_F32_04_1( psPoint->m_vB0_W, psExtend->m_vWidth );

        psPoint->m_vS0_W = tgMH_ADD_F32_04_1( vSN0_W, vQuad_BI );
        psPoint->m_vS1_W = tgMH_SUB_F32_04_1( vSN0_W, vQuad_BI );
    };
}


/* ---- tgFX_Effect__Trail__Render_Calculate_Vertex_00 --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgBOOL tgFX_Effect__Trail__Render_Calculate_Vertex_00( STg2_KN_GPU_Vertex_Particle_00_P psVert, STg2_FX__Trail__Render_Point_P psPoint )
{
    STg2_FX_Trail__File_Data_CPC        psFile_Data = psPoint->m_psTrail->m_psFile_Data;
    STg2_FX__Trail__Extend_Data_CPC     psExtend = &psPoint->m_psTrail->m_sExtend;
    TgBOOL                              bQuad_Camera_Facing;
    TgUN_V128                           uDirTest;

    uDirTest.m_vF32_04_1 = tgMH_DOT_F32_04_1( psPoint->m_vN0, psPoint->m_vCam_Forward );
    bQuad_Camera_Facing = tgCM_NR0_F32( uDirTest.m_vS_F32_04_1.x );
    if (bQuad_Camera_Facing)
    {
        psVert[0].m_vS0 = psPoint->m_vS0_W;
        psVert[0].m_vUV = tgMH_MAD_F32_04_1( psPoint->m_vScale_U, psExtend->m_vUV_01_Scale, psExtend->m_vUV_01_Constant );
        psVert[1].m_vS0 = psPoint->m_vS1_W;
        psVert[1].m_vUV = tgMH_MAD_F32_04_1( psFile_Data->m_vScale_V, psExtend->m_vUV_01_Scale, psVert[0].m_vUV );
    }
    else
    {
        psVert[1].m_vS0 = psPoint->m_vS0_W;
        psVert[1].m_vUV = tgMH_MAD_F32_04_1( psPoint->m_vScale_U, psExtend->m_vUV_01_Scale, psExtend->m_vUV_01_Constant );
        psVert[0].m_vS0 = psPoint->m_vS1_W;
        psVert[0].m_vUV = tgMH_MAD_F32_04_1( psFile_Data->m_vScale_V, psExtend->m_vUV_01_Scale, psVert[1].m_vUV );
    };

    psVert[0].m_vCL = psPoint->m_vCL;
    psVert[1].m_vCL = psPoint->m_vCL;

    return (bQuad_Camera_Facing);
}


/* ---- tgFX_Effect__Trail__Render_Calculate_Vertex_01 --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgBOOL tgFX_Effect__Trail__Render_Calculate_Vertex_01( STg2_KN_GPU_Vertex_Particle_01_P psVert, STg2_FX__Trail__Render_Point_P psPoint )
{
    STg2_FX_Trail__File_Data_CPC        psFile_Data = psPoint->m_psTrail->m_psFile_Data;
    STg2_FX__Trail__Extend_Data_CPC     psExtend = &psPoint->m_psTrail->m_sExtend;
    TgBOOL                              bQuad_Camera_Facing;
    TgUN_V128                           uDirTest;

    uDirTest.m_vF32_04_1 = tgMH_DOT_F32_04_1( psPoint->m_vN0, psPoint->m_vCam_Forward );
    bQuad_Camera_Facing = tgCM_NR0_F32( uDirTest.m_vS_F32_04_1.x );
    if (bQuad_Camera_Facing)
    {
        psVert[0].m_vS0 = psPoint->m_vS0_W;
        psVert[0].m_vUV = tgMH_MAD_F32_04_1( psPoint->m_vScale_U, psExtend->m_vUV_01_Scale, psExtend->m_vUV_01_Constant );
        psVert[1].m_vS0 = psPoint->m_vS1_W;
        psVert[1].m_vUV = tgMH_MAD_F32_04_1( psFile_Data->m_vScale_V, psExtend->m_vUV_01_Scale, psVert[0].m_vUV );
    }
    else
    {
        psVert[1].m_vS0 = psPoint->m_vS0_W;
        psVert[1].m_vUV = tgMH_MAD_F32_04_1( psPoint->m_vScale_U, psExtend->m_vUV_01_Scale, psExtend->m_vUV_01_Constant );
        psVert[0].m_vS0 = psPoint->m_vS1_W;
        psVert[0].m_vUV = tgMH_MAD_F32_04_1( psFile_Data->m_vScale_V, psExtend->m_vUV_01_Scale, psVert[1].m_vUV );
    };

    psVert[0].m_vT0 = psPoint->m_vT0_W;
    psVert[0].m_vB0 = psPoint->m_vB0_W;
    psVert[0].m_vCL = psPoint->m_vCL;
    psVert[1].m_vT0 = psPoint->m_vT0_W;
    psVert[1].m_vB0 = psPoint->m_vB0_W;
    psVert[1].m_vCL = psPoint->m_vCL;

    return (bQuad_Camera_Facing);
}


/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* ---- T(tgFX__Render__Trail_Render_Generate_Particle) -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_E32 T(tgFX__Render__Trail_Render_Generate_Particle)( STg2_FX_Rnd_Output_PC psRndOut, STg2_RN_Particle_Header_PC psHeader, STg2_FX__Trail_P psTrail )
{
    union
    {
        TgUINT_E08_P                        pui;
        T(STg2_KN_GPU_Vertex_Particle)*         ps;
    }                                   sVert;
    STg2_FX__Trail__Extend_Data_P       psExtend;
    TgRSIZE                             uiQuad_Size;
    TgRSIZE                             nuiMaxQuad;
    STg2_FX__Trail__Render_Point        sPoint;
    TgRSIZE                             nuiQuad;
    TgBOOL                              bQuad_Camera_Facing;

    /* If there was no room in the buffer, then the error value would be set as the offset value. */
    if (KTgMAX_RSIZE == psHeader->m_uiBuffer_Offset)
    {
        TgERROR(0 == psHeader->m_nbyVertex);
        return (0);
    };

    sVert.pui = psRndOut->m_puiBuffer + psHeader->m_uiBuffer_Offset;
    psExtend = &(psTrail->m_sExtend);
    uiQuad_Size = 6 * sizeof( T(STg2_KN_GPU_Vertex_Particle) );
    nuiMaxQuad = psHeader->m_nbyVertex / uiQuad_Size;

    /* This should not happen, but do not proceed if there is insufficient memory to hold a single quad.*/
    if (0 == nuiMaxQuad)
    {
        TgWARNING(nuiMaxQuad > 0);
        return (0);
    };

    tgRN_Calc_UV_Animation_F32_04_1( &psExtend->m_vUV_01_Constant, &psExtend->m_vUV_01_Scale, psTrail->m_tiMaterial, psRndOut->m_uDT.m_vF32_04_1, psTrail->m_vLive_Time );

    tgMM_Set_U08_0x00( &sPoint, sizeof( sPoint ) );
    sPoint.m_psTrail = psTrail;
    sPoint.m_psFile_Data = psTrail->m_psFile_Data;
    sPoint.m_vCam_Up = psRndOut->m_psCamera->m_vCam_Up;
    sPoint.m_vCam_Forward = psRndOut->m_psCamera->m_vCam_Forward;
    sPoint.m_vCL = psExtend->m_vColour;

    tgFX_Effect__Trail__Render_Calculate_Point( psTrail, &sPoint, psExtend->m_uiPoint_Head );
    TgERROR(sPoint.m_uiNext_Point != psExtend->m_uiPoint_Tail);

    bQuad_Camera_Facing = T(tgFX_Effect__Trail__Render_Calculate_Vertex)( sVert.ps, &sPoint );

    psTrail->m_vBA_Max_W = tgMH_MAX_F32_04_1( sPoint.m_vS0_W, sPoint.m_vS1_W );
    psTrail->m_vBA_Min_W = tgMH_MIN_F32_04_1( sPoint.m_vS0_W, sPoint.m_vS1_W );

    for (nuiQuad = 0; (nuiQuad < nuiMaxQuad) && (sPoint.m_uiNext_Point != psExtend->m_uiPoint_Tail); )
    {
        TgBOOL                              bNew_Quad_Camera_Facing;

        tgFX_Effect__Trail__Render_Calculate_Point( psTrail, &sPoint, sPoint.m_uiNext_Point );
        bNew_Quad_Camera_Facing = T(tgFX_Effect__Trail__Render_Calculate_Vertex)( sVert.ps + nuiQuad * 6 + 2, &sPoint );

        if (nuiQuad > 0)
        {
            /* If we already have the first quad, then for future iterations, use the preceding two vertices and the generated two vertices to create a quad. */
            if (bNew_Quad_Camera_Facing == bQuad_Camera_Facing)
            {
                sVert.ps[6 * nuiQuad + 0] = sVert.ps[6 * nuiQuad - 4];
                sVert.ps[6 * nuiQuad + 1] = sVert.ps[6 * nuiQuad - 3];
            }
            else
            {
                sVert.ps[6 * nuiQuad + 0] = sVert.ps[6 * nuiQuad - 3];
                sVert.ps[6 * nuiQuad + 1] = sVert.ps[6 * nuiQuad - 4];
            };
        };

        if (bNew_Quad_Camera_Facing == bQuad_Camera_Facing)
        {
            sVert.ps[6 * nuiQuad + 4] = sVert.ps[6 * nuiQuad + 2];
            sVert.ps[6 * nuiQuad + 5] = sVert.ps[6 * nuiQuad + 1];
        }
        else
        {
            sVert.ps[6 * nuiQuad + 4] = sVert.ps[6 * nuiQuad + 1];
            sVert.ps[6 * nuiQuad + 5] = sVert.ps[6 * nuiQuad + 2];
        };

        ++nuiQuad;
        bQuad_Camera_Facing = bNew_Quad_Camera_Facing;

        psTrail->m_vBA_Max_W = tgMH_MAX_F32_04_1( psTrail->m_vBA_Max_W, tgMH_MAX_F32_04_1( sPoint.m_vS0_W, sPoint.m_vS1_W ) );
        psTrail->m_vBA_Min_W = tgMH_MIN_F32_04_1( psTrail->m_vBA_Min_W, tgMH_MIN_F32_04_1( sPoint.m_vS0_W, sPoint.m_vS1_W ) );
    };

    TgVERIFY(nuiQuad == nuiMaxQuad);
    return (TgUINT_E32)(6 * nuiQuad);
}


/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* == Effect ===================================================================================================================================================================== */

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
