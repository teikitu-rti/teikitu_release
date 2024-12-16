/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Trail - Render.c
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
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_FX__Trail__Render_Point,)
{
    /* --------------- Input --------------- */
    STg2_FX__Trail_P                            m_psTrail;
    STg2_FX_Trail__File_Data_CP                 m_psFile_Data;
    TgVEC_F32_04_1                              m_vCam_Forward;
    TgVEC_F32_04_1                              m_vCL;

    /* --------------- Output -------------- */
    TgVEC_F32_04_1                              m_vS0_W;
    TgVEC_F32_04_1                              m_vS1_W;
    TgVEC_F32_04_1                              m_vT0_W;
    TgVEC_F32_04_1                              m_vB0_W;
    TgVEC_F32_04_1                              m_vScale_U;
    TgVEC_F32_04_1                              m_vN0;
    TgUINT_F32                                  m_uiNext_Point;
    TgUINT_F32                                  m_uiPad0[3];
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgFX_Effect__Trail__Render_Calculate_Point(
    STg2_FX__Trail_P, STg2_FX__Trail__Render_Point_P, TgUINT_F32_C  );

TgFORCEINLINE TgBOOL
tgFX_Effect__Trail__Render_Calculate_Vertex_00(
    STg2_KN_GPU_Vertex_Particle_00_P, TgRSIZE_C, TgRSIZE_C, STg2_FX__Trail__Render_Point_P );

TgFORCEINLINE TgBOOL
tgFX_Effect__Trail__Render_Calculate_Vertex_01(
    STg2_KN_GPU_Vertex_Particle_01_P, TgRSIZE_C, TgRSIZE_C, STg2_FX__Trail__Render_Point_P );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgFX_Effect__Trail__Render_Quad_Count ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgFX_Effect__Trail__Render_Quad_Count( STg2_FX__Trail_P psTrail )
{
    STg2_FX__Trail__Extend_Data_P       psExtend;
    TgUINT_F32                          uiPoint;
    TgRSIZE                             nuiQuad;

    psExtend = &(psTrail->m_sExtend);
    if (psExtend->m_uiPoint_Head == psExtend->m_uiPoint_Tail)
    {
        return (0);
    };

    uiPoint = (psExtend->m_uiPoint_Head + KTgFX_MAX_POINTS_IN_TRAIL - 1) % KTgFX_MAX_POINTS_IN_TRAIL;
    nuiQuad = 0;
    if (uiPoint != psExtend->m_uiPoint_Tail)
    {
        uiPoint = (uiPoint + KTgFX_MAX_POINTS_IN_TRAIL - 1) % KTgFX_MAX_POINTS_IN_TRAIL;
        ++nuiQuad;
    };

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
static TgVOID tgFX_Effect__Trail__Render_Calculate_Point( STg2_FX__Trail_P psTrail, STg2_FX__Trail__Render_Point_P psPoint, TgUINT_F32_C uiPoint )
{
    STg2_FX__Trail__Extend_Data_P       psExtend;
    TgVEC_F32_04_1                    vPrev_S0_W;
    TgVEC_F32_04_1                    vPrev_T0_W;
    TgVEC_F32_04_1                    vSN0_W;
    TgVEC_F32_04_1                    vSN1_W;
    TgVEC_F32_04_1                    vQuad_BI;
    TgVEC_F32_04_1                    vB1;

    psExtend = &(psTrail->m_sExtend);
    vPrev_S0_W = psPoint->m_vS0_W;
    vPrev_T0_W = psPoint->m_vT0_W;

    psPoint->m_uiNext_Point = (uiPoint + KTgFX_MAX_POINTS_IN_TRAIL - 1) % KTgFX_MAX_POINTS_IN_TRAIL;
    vSN0_W = psExtend->m_vPos_N2W[uiPoint];
    vSN1_W = psExtend->m_vPos_N2W[psPoint->m_uiNext_Point];

    psPoint->m_vT0_W = tgMH_NORM_F32_04_1( tgMH_SUB_F32_04_1( vSN1_W, vSN0_W ) );
    psPoint->m_vB0_W = tgMH_UCX_F32_04_1( psPoint->m_vCam_Forward, psPoint->m_vT0_W );
    vQuad_BI = tgMH_MUL_F32_04_1( psPoint->m_vB0_W, psExtend->m_vWidth );
    psPoint->m_vScale_U = tgMH_MUL_F32_04_1( tgMH_SET1_F32_04_1( psExtend->m_fU[uiPoint] ), psTrail->m_psFile_Data->m_vScale_U );
    psPoint->m_vS0_W = tgMH_SUB_F32_04_1( vSN0_W, vQuad_BI );
    psPoint->m_vS1_W = tgMH_ADD_F32_04_1( vSN0_W, vQuad_BI );

    if (uiPoint != psExtend->m_uiPoint_Head)
    {
        vB1 = tgMH_NORM_F32_04_1( tgMH_SUB_F32_04_1( psPoint->m_vS1_W, vPrev_S0_W ) );
        psPoint->m_vN0 = tgMH_CX_F32_04_1( vPrev_T0_W, vB1 );
    };
}


/* ---- tgFX_Effect__Trail__Render_Calculate_Vertex_00 --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgBOOL tgFX_Effect__Trail__Render_Calculate_Vertex_00(
    STg2_KN_GPU_Vertex_Particle_00_P psVert, TgRSIZE_C uiPoint0, TgRSIZE_C uiPoint1, STg2_FX__Trail__Render_Point_P psPoint )
{
    TgBOOL                              bQuad_Camera_Facing;
    TgUN_V128                           uDirTest;

    uDirTest.m_vF32_04_1 = tgMH_DOT_F32_04_1( psPoint->m_vN0, psPoint->m_vCam_Forward );
    bQuad_Camera_Facing = tgCM_NR0_F32( uDirTest.m_vS_F32_04_1.x );
    if (bQuad_Camera_Facing)
    {
        psVert[uiPoint0].m_vS0 = psPoint->m_vS0_W;
        psVert[uiPoint0].m_vUV = tgMH_MAD_F32_04_1( psPoint->m_vScale_U, psPoint->m_psTrail->m_sExtend.m_vUV_01_Scale, psPoint->m_psTrail->m_sExtend.m_vUV_01_Constant );
        psVert[uiPoint1].m_vS0 = psPoint->m_vS1_W;
        psVert[uiPoint1].m_vUV = tgMH_MAD_F32_04_1( psPoint->m_psFile_Data->m_vScale_V, psPoint->m_psTrail->m_sExtend.m_vUV_01_Scale, psVert[uiPoint0].m_vUV );
    }
    else
    {
        psVert[uiPoint1].m_vS0 = psPoint->m_vS0_W;
        psVert[uiPoint1].m_vUV = tgMH_MAD_F32_04_1( psPoint->m_vScale_U, psPoint->m_psTrail->m_sExtend.m_vUV_01_Scale, psPoint->m_psTrail->m_sExtend.m_vUV_01_Constant );
        psVert[uiPoint0].m_vS0 = psPoint->m_vS1_W;
        psVert[uiPoint0].m_vUV = tgMH_MAD_F32_04_1( psPoint->m_psFile_Data->m_vScale_V, psPoint->m_psTrail->m_sExtend.m_vUV_01_Scale, psVert[uiPoint1].m_vUV );
    };

    psVert[uiPoint0].m_vCL = psPoint->m_vCL;
    psVert[uiPoint1].m_vCL = psPoint->m_vCL;

    return (bQuad_Camera_Facing);
}


/* ---- tgFX_Effect__Trail__Render_Calculate_Vertex_01 --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgBOOL tgFX_Effect__Trail__Render_Calculate_Vertex_01(
    STg2_KN_GPU_Vertex_Particle_01_P psVert, TgRSIZE_C uiPoint0, TgRSIZE_C uiPoint1, STg2_FX__Trail__Render_Point_P psPoint )
{
    TgBOOL                              bQuad_Camera_Facing;
    TgUN_V128                           uDirTest;

    uDirTest.m_vF32_04_1 = tgMH_DOT_F32_04_1( psPoint->m_vN0, psPoint->m_vCam_Forward );
    bQuad_Camera_Facing = tgCM_NR0_F32( uDirTest.m_vS_F32_04_1.x );
    if (bQuad_Camera_Facing)
    {
        psVert[uiPoint0].m_vS0 = psPoint->m_vS0_W;
        psVert[uiPoint0].m_vUV = tgMH_MAD_F32_04_1( psPoint->m_vScale_U, psPoint->m_psTrail->m_sExtend.m_vUV_01_Scale, psPoint->m_psTrail->m_sExtend.m_vUV_01_Constant );
        psVert[uiPoint1].m_vS0 = psPoint->m_vS1_W;
        psVert[uiPoint1].m_vUV = tgMH_MAD_F32_04_1( psPoint->m_psFile_Data->m_vScale_V, psPoint->m_psTrail->m_sExtend.m_vUV_01_Scale, psVert[uiPoint0].m_vUV );
    }
    else
    {
        psVert[uiPoint1].m_vS0 = psPoint->m_vS0_W;
        psVert[uiPoint1].m_vUV = tgMH_MAD_F32_04_1( psPoint->m_vScale_U, psPoint->m_psTrail->m_sExtend.m_vUV_01_Scale, psPoint->m_psTrail->m_sExtend.m_vUV_01_Constant );
        psVert[uiPoint0].m_vS0 = psPoint->m_vS1_W;
        psVert[uiPoint0].m_vUV = tgMH_MAD_F32_04_1( psPoint->m_psFile_Data->m_vScale_V, psPoint->m_psTrail->m_sExtend.m_vUV_01_Scale, psVert[uiPoint1].m_vUV );
    };

    psVert[uiPoint0].m_vT0 = psPoint->m_vT0_W;
    psVert[uiPoint0].m_vB0 = psPoint->m_vB0_W;
    psVert[uiPoint0].m_vCL = psPoint->m_vCL;
    psVert[uiPoint1].m_vT0 = psPoint->m_vT0_W;
    psVert[uiPoint1].m_vB0 = psPoint->m_vB0_W;
    psVert[uiPoint1].m_vCL = psPoint->m_vCL;

    return (bQuad_Camera_Facing);
}


/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* ---- T(tgFX__Render__Trail_Render_Generate_Particle) -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F32 T(tgFX__Render__Trail_Render_Generate_Particle)( STg2_FX_Rnd_Output_PC psRndOut, STg2_RN_Particle_Header_PC psHeader, STg2_FX__Trail_P psTrail )
{
    union
    {
        TgUINT_F08_P                        pui;
        T(STg2_KN_GPU_Vertex_Particle)*         ps;
    }                                   sVert;
    STg2_FX__Trail__Extend_Data_P       psExtend;
    TgRSIZE                             uiQuad_Size;
    TgRSIZE                             nuiMaxQuad;
    STg2_FX__Trail__Render_Point        sFirst_Point;
    STg2_FX__Trail__Render_Point        sPoint;
    TgUINT_F32                          uiPoint;
    TgRSIZE                             nuiQuad;
    TgBOOL                              bQuad_Camera_Facing;

    if (KTgMAX_RSIZE == psHeader->m_uiBuffer_Offset)
    {
        TgERROR(0 == psHeader->m_nbyVertex);
        return (0);
    };

    sVert.pui = psRndOut->m_puiBuffer + psHeader->m_uiBuffer_Offset;
    psExtend = &(psTrail->m_sExtend);
    uiQuad_Size = 4 * sizeof( T(STg2_KN_GPU_Vertex_Particle) );
    nuiMaxQuad = psHeader->m_nbyVertex / uiQuad_Size;
    TgERROR( nuiMaxQuad >= 1 );

    tgMM_Set_U08_0x00( &sFirst_Point, sizeof( sFirst_Point ) );
    sFirst_Point.m_psTrail = psTrail;
    sFirst_Point.m_psFile_Data = psTrail->m_psFile_Data;
    sFirst_Point.m_vCam_Forward = psRndOut->m_psCamera->m_vCam_Forward;
    sFirst_Point.m_vCL = psExtend->m_vColour;

    tgRN_Calc_UV_Animation_F32_04_1( &psExtend->m_vUV_01_Constant, &psExtend->m_vUV_01_Scale, psTrail->m_tiMaterial, psRndOut->m_uDT.m_vF32_04_1, psTrail->m_vLive_Time );

    uiPoint = psExtend->m_uiPoint_Head;
    TgERROR( uiPoint != psExtend->m_uiPoint_Tail );
    tgFX_Effect__Trail__Render_Calculate_Point( psTrail, &sFirst_Point, uiPoint );
    TgERROR(sFirst_Point.m_uiNext_Point != psExtend->m_uiPoint_Tail);
    uiPoint = sFirst_Point.m_uiNext_Point;
    sPoint = sFirst_Point;

    psTrail->m_vBA_Max_W = tgMH_MAX_F32_04_1( sPoint.m_vS0_W, sPoint.m_vS1_W );
    psTrail->m_vBA_Min_W = tgMH_MIN_F32_04_1( sPoint.m_vS0_W, sPoint.m_vS1_W );

    uiPoint = (uiPoint + KTgFX_MAX_POINTS_IN_TRAIL - 1) % KTgFX_MAX_POINTS_IN_TRAIL;

    nuiQuad = 0;
    bQuad_Camera_Facing = true;
    while ((nuiQuad < nuiMaxQuad) && (uiPoint != psExtend->m_uiPoint_Tail))
    {
        TgBOOL                              bNew_Quad_Camera_Facing;

        tgFX_Effect__Trail__Render_Calculate_Point( psTrail, &sPoint, uiPoint );
        uiPoint = sPoint.m_uiNext_Point;
        bNew_Quad_Camera_Facing = T(tgFX_Effect__Trail__Render_Calculate_Vertex)( sVert.ps, 4 * nuiQuad + 3, 4 * nuiQuad + 2, &sPoint );

        if (nuiQuad > 0)
        {
            if (bNew_Quad_Camera_Facing == bQuad_Camera_Facing)
            {
                sVert.ps[4 * nuiQuad + 0] = sVert.ps[4 * nuiQuad - 1];
                sVert.ps[4 * nuiQuad + 1] = sVert.ps[4 * nuiQuad - 2];
            }
            else
            {
                sVert.ps[4 * nuiQuad + 0] = sVert.ps[4 * nuiQuad - 2];
                sVert.ps[4 * nuiQuad + 1] = sVert.ps[4 * nuiQuad - 1];
            };
        }
        else
        {
            T(tgFX_Effect__Trail__Render_Calculate_Vertex)( sVert.ps, 0, 1, &sPoint );
        };

        bQuad_Camera_Facing = bNew_Quad_Camera_Facing;
        ++nuiQuad;

        psTrail->m_vBA_Max_W = tgMH_MAX_F32_04_1( psTrail->m_vBA_Max_W, tgMH_MAX_F32_04_1( sPoint.m_vS0_W, sPoint.m_vS1_W ) );
        psTrail->m_vBA_Min_W = tgMH_MIN_F32_04_1( psTrail->m_vBA_Min_W, tgMH_MIN_F32_04_1( sPoint.m_vS0_W, sPoint.m_vS1_W ) );

        uiPoint = (uiPoint + KTgFX_MAX_POINTS_IN_TRAIL - 1) % KTgFX_MAX_POINTS_IN_TRAIL;
        ++nuiQuad;
    };

    return (TgUINT_F32)(4 * nuiQuad);
}


/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* == Effect ===================================================================================================================================================================== */

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
