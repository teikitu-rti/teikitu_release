/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Beam - Render.c
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

TgTYPE_STRUCT(STg2_FX__Beam__Render_Point,)
{
    /* --------------- Input --------------- */
    TgVEC_F32_04_1                              m_vBeam_End_Position_N;
    TgVEC_F32_04_1                              m_vCam_Forward;
    STg2_FX__Beam_CP                            m_psBeam;
    TgRSIZE                                     m_uiPrev_Frame, m_uiNext_Frame;
    TgFLOAT32                                   m_fShape_Fraction;
    TgUINT_E08                                  m_uiPad[4];

    /* ----------- Configuration ----------- */
    TgVEC_F32_04_1                              m_vSG_W; ///< Current end point of the beam segment in world reference frame.
    TgVEC_F32_04_1                              m_vCL; ///< Colour of the beam

    /* --------------- Output -------------- */
    TgVEC_F32_04_1                              m_vS0_W; ///< 1st generated point for the quad.
    TgVEC_F32_04_1                              m_vS1_W; ///< 2nd generated point for the quad.
    TgVEC_F32_04_1                              m_vN0_W; ///< Basis vector (normal)
    TgVEC_F32_04_1                              m_vT0_W; ///< Basis vector (tangent)
    TgVEC_F32_04_1                              m_vT1_W; ///< Basis vector (tangent)
    TgVEC_F32_04_1                              m_vScale_U; ///< Current scale multiplier for the quads that form the beam render.
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgFX_Effect__Beam__Render_Init_Point(
    STg2_FX__Beam__Render_Point_P, STg2_FX_Rnd_Output_PC, STg2_FX__Beam_P );

static TgVOID
tgFX_Effect__Beam__Render_Common(
    STg2_FX__Beam__Render_Point_P );

TgFORCEINLINE TgBOOL
tgFX_Effect__Beam__Render_Calculate_Vertex_00(
    STg2_KN_GPU_Vertex_Particle_00_P, STg2_FX__Beam__Render_Point_P );

TgFORCEINLINE TgBOOL
tgFX_Effect__Beam__Render_Calculate_Vertex_01(
    STg2_KN_GPU_Vertex_Particle_01_P, STg2_FX__Beam__Render_Point_P );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgFX_Effect__Beam__Render_Quad_Count ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgFX_Effect__Beam__Render_Quad_Count( STg2_FX__Beam_P psBeam )
{
    STg2_FX_Beam__File_Data_CPC         psFile_Data = psBeam->m_psFile_Data;
    STg2_FX__Beam__Extend_Data_CPC      psExtend = &psBeam->m_sExtend;
    TgFLOAT32_CPC                       pfShape_Normalized_T = psFile_Data->m_sShape.m_sData.m_pfShape_Normalized_T;

    TgUINT_F32                          uiStart_Frame, uiEnd_Frame;

    /* In the shape key-frame lists, skip until the start of the beam is within the range of a set of key frames. */
    for (uiStart_Frame = 0; uiStart_Frame + 1 < psFile_Data->m_nuiPoints && pfShape_Normalized_T[uiStart_Frame + 1] <= psExtend->m_fShape_Start_Fraction; ++uiStart_Frame) {};
    for (uiEnd_Frame = uiStart_Frame; uiEnd_Frame + 1 < psFile_Data->m_nuiPoints && pfShape_Normalized_T[uiEnd_Frame + 1] <= psExtend->m_fShape_End_Fraction; ++uiEnd_Frame) {};

    /* Validate that we are within the key frames for the shape data. */
    if (pfShape_Normalized_T[uiStart_Frame] > psExtend->m_fShape_Start_Fraction)
    {
        return (0);
    };

    if (pfShape_Normalized_T[uiEnd_Frame] > psExtend->m_fShape_End_Fraction)
    {
        return (0);
    };

    /* Generate all the quads between the first two vertices and the last two vertices. */
    return (uiEnd_Frame - uiStart_Frame + 1);
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

/* ---- tgFX_Effect__Beam__Render_Init_Point ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX_Effect__Beam__Render_Init_Point( STg2_FX__Beam__Render_Point_P psPoint, STg2_FX_Rnd_Output_PC psRndOut, STg2_FX__Beam_P psBeam )
{
    psPoint->m_psBeam = psBeam;
    psPoint->m_vBeam_End_Position_N = tgMH_Init_Point_F32_04_1( tgMH_ADD_F32_04_1( tgMH_Init_Vector_F32_04_1( psBeam->m_sExtend.m_vEnd_Position ), psBeam->m_sExtend.m_vEnd_Variance ) );
    psPoint->m_vCam_Forward = psRndOut->m_psCamera->m_vCam_Forward;
    psPoint->m_vSG_W = psBeam->m_vPos_N2W;
}


/* ---- tgFX_Effect__Beam__Render_Common ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX_Effect__Beam__Render_Common( STg2_FX__Beam__Render_Point_P psPoint )
{
    STg2_FX_Beam__File_Data_CPC         psFile_Data = psPoint->m_psBeam->m_psFile_Data;
    TgVEC_F32_04_1_CPC                  pvShape_Colour = psFile_Data->m_sShape.m_sData.m_pvShape_Colour;
    TgVEC_F32_04_1_CPC                  pvShape_Offset = psFile_Data->m_sShape.m_sData.m_pvShape_Offset;
    TgFLOAT32_CPC                       pfShape_Width = psFile_Data->m_sShape.m_sData.m_pfShape_Width;
    TgFLOAT32_CPC                       pfShape_Fraction = psFile_Data->m_sShape.m_sData.m_pfShape_Fraction;
    TgFLOAT32_CPC                       pfShape_Normalized_T = psFile_Data->m_sShape.m_sData.m_pfShape_Normalized_T;

    TgVEC_F32_04_1                      vPrev_Pos_W;
    TgVEC_F32_04_1                      vSegment_Offset_N;

    TgFLOAT32                           fWidth;
    TgFLOAT32                           fShape_Fraction;
    TgVEC_F32_04_1                      vShape_Fraction;
    TgVEC_F32_04_1                      vShape_Pos_N;
    TgUN_V128                           uLength;
    TgVEC_F32_04_1                      vQuad_BI;

    vPrev_Pos_W = tgMH_Init_Point_F32_04_1( psPoint->m_vSG_W );

    if (psPoint->m_uiNext_Frame != psPoint->m_uiPrev_Frame)
    {
        TgFLOAT32                           fRange;
        TgFLOAT32                           fRelative_Position_In_Range;
        TgFLOAT32                           fFraction_Of_Range;
        TgVEC_F32_04_1                      vFraction_Of_Range;

        /* Calculate the interpolation value (fraction) to be used with the other key-frame values. */
        fRange = pfShape_Normalized_T[psPoint->m_uiNext_Frame] - pfShape_Normalized_T[psPoint->m_uiPrev_Frame];
        fRelative_Position_In_Range = psPoint->m_fShape_Fraction - pfShape_Normalized_T[psPoint->m_uiPrev_Frame];
        fFraction_Of_Range = (!tgCM_NR0_F32( fRange )) ? fRelative_Position_In_Range / fRange : 0.0F;
        vFraction_Of_Range = tgMH_SET1_F32_04_1( fFraction_Of_Range );

        /* Interpolate the values from the key-frame data. */
        vSegment_Offset_N = tgMH_MAD_F32_04_1( pvShape_Offset[psPoint->m_uiNext_Frame], vFraction_Of_Range, pvShape_Offset[psPoint->m_uiPrev_Frame] );
        vSegment_Offset_N = tgMH_NMS_F32_04_1( vFraction_Of_Range, pvShape_Offset[psPoint->m_uiPrev_Frame], vSegment_Offset_N );
        fWidth = tgCM_LRP_F32( pfShape_Width[psPoint->m_uiPrev_Frame], pfShape_Width[psPoint->m_uiNext_Frame], fFraction_Of_Range );
        fShape_Fraction = tgCM_LRP_F32( pfShape_Fraction[psPoint->m_uiPrev_Frame], pfShape_Fraction[psPoint->m_uiNext_Frame], fFraction_Of_Range );
        psPoint->m_vCL = tgMH_MAD_F32_04_1( pvShape_Colour[psPoint->m_uiNext_Frame], vFraction_Of_Range, pvShape_Colour[psPoint->m_uiPrev_Frame] );
        psPoint->m_vCL = tgMH_NMS_F32_04_1( vFraction_Of_Range, pvShape_Colour[psPoint->m_uiPrev_Frame], psPoint->m_vCL );

    }
    else
    {
        vSegment_Offset_N = pvShape_Offset[psPoint->m_uiPrev_Frame];
        fWidth = pfShape_Width[psPoint->m_uiPrev_Frame];
        fShape_Fraction = pfShape_Fraction[psPoint->m_uiPrev_Frame];
        psPoint->m_vCL = pvShape_Colour[psPoint->m_uiPrev_Frame];
    };

    /* Having determined the amount of the line that has completed, calculate the current end point in the world reference frame. */
    vShape_Fraction = tgMH_SET1_F32_04_1( fShape_Fraction );
    vShape_Pos_N = tgMH_Init_Point_F32_04_1( tgMH_MAD_F32_04_1( psPoint->m_vBeam_End_Position_N, vShape_Fraction, vSegment_Offset_N ) );
    psPoint->m_vSG_W = tgMH_ADD_F32_04_1( psPoint->m_psBeam->m_vPos_N2W, tgMH_QT_TX_F32_04_1( vShape_Pos_N, psPoint->m_psBeam->m_qRot_N2W ) );

    /* Quad tangent is assumed to be the normalized vector between the current world position and the previous world position. */
    psPoint->m_vT0_W = tgMH_NORM_LEN_F32_04_1( &uLength.m_vF32_04_1, tgMH_SUB_F32_04_1( psPoint->m_vSG_W, vPrev_Pos_W ) );
    if (tgCM_NR0_F32( uLength.m_vS_F32_04_1.x ))
    {
        psPoint->m_vT0_W = tgMH_SET1_F32_04_1( 0.0F );
        psPoint->m_vT1_W = tgMH_SET1_F32_04_1( 0.0F );
        psPoint->m_vN0_W = tgMH_SET1_F32_04_1( 0.0F );
    }
    else
    {
        /* If the resulting vector is valid, create the remaining two basis vectors. */
        psPoint->m_vT1_W = tgMH_UCX_F32_04_1( psPoint->m_vCam_Forward, psPoint->m_vT0_W );
        psPoint->m_vN0_W = tgMH_CX_F32_04_1( psPoint->m_vT0_W, psPoint->m_vT1_W );
    }

    /* Construct */
    vQuad_BI = tgMH_MUL_F32_04_1( psPoint->m_vT1_W, tgMH_SET1_F32_04_1( fWidth ) );
    psPoint->m_vS0_W = tgMH_ADD_F32_04_1( psPoint->m_vSG_W, vQuad_BI );
    psPoint->m_vS1_W = tgMH_SUB_F32_04_1( psPoint->m_vSG_W, vQuad_BI );
    psPoint->m_vScale_U = tgMH_MUL_F32_04_1( psPoint->m_psBeam->m_psFile_Data->m_vScale_U, vShape_Fraction );

#if TgS_DEBUG__EFFECT
    {
        TgBOOL                              bDraw;
        if ((tgCN_Var_Query_Bool( &bDraw, g_tiFX_Debug__Beam__Draw_Debug )) && (bDraw))
        {
            tgRN_DBG_Sphere( KTg_YELLOW_G10_P709_U32, psPoint->m_vSG_W, 0.1F );
            tgRN_DBG_Line( psPoint->m_vS0_W, KTg_GREEN_G10_P709_U32, psPoint->m_vS1_W, KTg_GREEN_G10_P709_U32 );
        };
    }
/*# TgS_DEBUG__EFFECT */
#endif
}


/* ---- tgFX_Effect__Beam__Render_Calculate_Vertex_00 ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgBOOL tgFX_Effect__Beam__Render_Calculate_Vertex_00( STg2_KN_GPU_Vertex_Particle_00_P psVert, STg2_FX__Beam__Render_Point_P psPoint )
{
    STg2_FX_Beam__File_Data_CPC         psFile_Data = psPoint->m_psBeam->m_psFile_Data;
    STg2_FX__Beam__Extend_Data_CPC      psExtend = &psPoint->m_psBeam->m_sExtend;
    TgBOOL                              bQuad_Camera_Facing;
    TgUN_V128                           uDirTest;

    tgFX_Effect__Beam__Render_Common( psPoint );

    uDirTest.m_vF32_04_1 = tgMH_DOT_F32_04_1( psPoint->m_vN0_W, psPoint->m_vCam_Forward );
    bQuad_Camera_Facing = tgCM_NR0_F32( uDirTest.m_vS_F32_04_1.x );
    //bQuad_Camera_Facing = uDirTest.m_vS_F32_04_1.x <= 0.0F;
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


/* ---- tgFX_Effect__Beam__Render_Calculate_Vertex_01 ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgBOOL tgFX_Effect__Beam__Render_Calculate_Vertex_01( STg2_KN_GPU_Vertex_Particle_01_P psVert, STg2_FX__Beam__Render_Point_P psPoint )
{
    STg2_FX_Beam__File_Data_CPC         psFile_Data = psPoint->m_psBeam->m_psFile_Data;
    STg2_FX__Beam__Extend_Data_CPC      psExtend = &psPoint->m_psBeam->m_sExtend;
    TgBOOL                              bQuad_Camera_Facing;
    TgUN_V128                           uDirTest;

    tgFX_Effect__Beam__Render_Common( psPoint );

    uDirTest.m_vF32_04_1 = tgMH_DOT_F32_04_1( psPoint->m_vN0_W, psPoint->m_vCam_Forward );
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
    psVert[0].m_vB0 = psPoint->m_vT1_W;
    psVert[0].m_vCL = psPoint->m_vCL;
    psVert[1].m_vT0 = psPoint->m_vT0_W;
    psVert[1].m_vB0 = psPoint->m_vT1_W;
    psVert[1].m_vCL = psPoint->m_vCL;

    return (bQuad_Camera_Facing);
}


#else

/* ---- T(tgFX__Render__Beam_Render_Generate_Particle) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F32 T(tgFX__Render__Beam_Render_Generate_Particle)( STg2_FX_Rnd_Output_PC psRndOut, STg2_RN_Particle_Header_PC psHeader, STg2_FX__Beam_P psBeam )
{
    STg2_FX_Beam__File_Data_CPC         psFile_Data = psBeam->m_psFile_Data;
    STg2_FX__Beam__Extend_Data_PC       psExtend = &psBeam->m_sExtend;
    TgFLOAT32_CPC                       pfShape_Normalized_T = psBeam->m_psFile_Data->m_sShape.m_sData.m_pfShape_Normalized_T;
    union
    {
        TgUINT_F08_P                        pui;
        T(STg2_KN_GPU_Vertex_Particle)*     ps;
    }                                   sVert;
    TgRSIZE                             uiQuad_Size;
    TgRSIZE                             nuiMaxQuad;
    STg2_FX__Beam__Render_Point         sPoint;
    TgUINT_F32                          uiStart_Frame, uiEnd_Frame, uiFrame;
    TgRSIZE                             nuiQuad;
    TgBOOL                              bQuad_Camera_Facing;

    /* If there was no room in the buffer, then the error value would be set as the offset value. */
    if (KTgMAX_RSIZE == psHeader->m_uiBuffer_Offset)
    {
        TgERROR(0 == psHeader->m_nbyVertex);
        return (0);
    };

    sVert.pui = psRndOut->m_puiBuffer + psHeader->m_uiBuffer_Offset;
    uiQuad_Size = 6 * sizeof( T(STg2_KN_GPU_Vertex_Particle) );
    nuiMaxQuad = psHeader->m_nbyVertex / uiQuad_Size;

    /* This should not happen, but do not proceed if there is insufficient memory to hold a single quad.*/
    if (0 == nuiMaxQuad)
    {
        TgWARNING(nuiMaxQuad > 0);
        return (0);
    };

    /* Initialize a local cache for critical rendering fields for this particular beam instance. */
    tgMM_Set_U08_0x00( &sPoint, sizeof( sPoint ) );
    tgFX_Effect__Beam__Render_Init_Point( &sPoint, psRndOut, psBeam );

    /* Calculate the UV parameters for the Beam based on the animation parameters. */
    tgRN_Calc_UV_Animation_F32_04_1( &psExtend->m_vUV_01_Constant, &psExtend->m_vUV_01_Scale, psBeam->m_tiMaterial, psRndOut->m_uDT.m_vF32_04_1, psBeam->m_vLive_Time );

    /* In the shape key-frame lists, skip until the start of the beam is within the range of a set of key frames. */
    for (uiStart_Frame = 0; uiStart_Frame + 1 < psFile_Data->m_nuiPoints && pfShape_Normalized_T[uiStart_Frame + 1] <= psExtend->m_fShape_Start_Fraction; ++uiStart_Frame) {};
    for (uiEnd_Frame = uiStart_Frame; uiEnd_Frame + 1 < psFile_Data->m_nuiPoints && pfShape_Normalized_T[uiEnd_Frame + 1] <= psExtend->m_fShape_End_Fraction; ++uiEnd_Frame) {};

    /* Validate that we are within the key frames for the shape data. */
    if (pfShape_Normalized_T[uiStart_Frame] > psExtend->m_fShape_Start_Fraction)
    {
        return (0);
    };

    if (pfShape_Normalized_T[uiEnd_Frame] > psExtend->m_fShape_End_Fraction)
    {
        return (0);
    };

    /* Need to prime the loop by creating the first two set of vertices for the quads. */
    TgVERIFY(0 == uiStart_Frame || pfShape_Normalized_T[uiStart_Frame - 1] <= psExtend->m_fShape_Start_Fraction);
    TgVERIFY(pfShape_Normalized_T[uiStart_Frame] <= psExtend->m_fShape_Start_Fraction);
    sPoint.m_uiPrev_Frame = uiStart_Frame;
    sPoint.m_uiNext_Frame = uiStart_Frame + 1;
    sPoint.m_fShape_Fraction = psExtend->m_fShape_Start_Fraction;
    bQuad_Camera_Facing = T(tgFX_Effect__Beam__Render_Calculate_Vertex)( sVert.ps, &sPoint );

    /* Generate all the quads between the first two vertices and the last two vertices. */
    for (nuiQuad = 0, uiFrame = uiStart_Frame == uiEnd_Frame ? uiStart_Frame : uiStart_Frame + 1; (nuiQuad < nuiMaxQuad); ++uiFrame)
    {
        TgBOOL                              bNew_Quad_Camera_Facing;

        /* Calculate a new set of two vertices. */
        if (nuiQuad + 1 == nuiMaxQuad)
        {
            sPoint.m_uiPrev_Frame = uiStart_Frame == uiEnd_Frame ? uiFrame : uiFrame - 1;
            sPoint.m_uiNext_Frame = tgCM_MIN_UMAX( uiStart_Frame == uiEnd_Frame ? uiFrame + 1 : uiFrame, psFile_Data->m_nuiPoints - 1 );
            sPoint.m_fShape_Fraction = psExtend->m_fShape_End_Fraction;
            TgVERIFY(psFile_Data->m_sShape.m_sData.m_pfShape_Fraction[sPoint.m_uiPrev_Frame] <= psExtend->m_fShape_End_Fraction);
            TgVERIFY(psFile_Data->m_sShape.m_sData.m_pfShape_Fraction[sPoint.m_uiNext_Frame] >= psExtend->m_fShape_End_Fraction);
        }
        else
        {
            sPoint.m_uiPrev_Frame = uiFrame;
            sPoint.m_uiNext_Frame = uiFrame;
            sPoint.m_fShape_Fraction = pfShape_Normalized_T[uiFrame];
        }
        bNew_Quad_Camera_Facing = T(tgFX_Effect__Beam__Render_Calculate_Vertex)( sVert.ps + nuiQuad * 6 + 2, &sPoint );

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

        psBeam->m_vBA_Max_W = tgMH_MAX_F32_04_1( psBeam->m_vBA_Max_W, tgMH_MAX_F32_04_1( sPoint.m_vS0_W, sPoint.m_vS1_W ) );
        psBeam->m_vBA_Min_W = tgMH_MIN_F32_04_1( psBeam->m_vBA_Min_W, tgMH_MIN_F32_04_1( sPoint.m_vS0_W, sPoint.m_vS1_W ) );
    };

    return (TgUINT_F32)(nuiQuad*6);
}


/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* == Effect ===================================================================================================================================================================== */

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
