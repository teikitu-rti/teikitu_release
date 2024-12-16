/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Billboard - Render.c
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

TgTYPE_STRUCT(STg2_FX__Billboard__Render_Point,)
{
    /* --------------- Input --------------- */
    STg2_FX__Billboard_P                        m_psBillboard;
    STg2_FX_Billboard__File_Data_CP             m_psFile_Data;
    TgVEC_F32_04_1                              m_vCam_Pos_W;
    TgVEC_F32_04_1                              m_vCam_Up;
    TgVEC_F32_04_1                              m_vCam_Forward;
    TgVEC_F32_04_1                              m_vUV_Mask[4];
    TgVEC_F32_04_1                              m_vBase_CL;

    /* --------------- Output -------------- */
    TgVEC_F32_04_1                              m_avPos_W[4];
    TgVEC_F32_04_1                              m_avBasis[2];
    TgVEC_F32_04_1                              m_vCL;
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgFX_Effect__Billboard__Render_Init_Point(
    STg2_FX__Billboard__Render_Point_P, STg2_FX_Rnd_Output_PC );

static TgBOOL
tgFX_Effect__Billboard__Render_Common(
    STg2_FX__Billboard__Render_Point_P, TgVEC_F32_04_1 );

static TgVOID
tgFX_Effect__Billboard__Render_Reference_Frame(
    STg2_FX__Billboard__Render_Point_P );

TgFORCEINLINE TgVOID
tgFX_Effect__Billboard__Render_Write_Quad_00(
    STg2_KN_GPU_Vertex_Particle_00_P, STg2_FX__Billboard__Render_Point_P );

TgFORCEINLINE TgVOID
tgFX_Effect__Billboard__Render_Write_Quad_01(
    STg2_KN_GPU_Vertex_Particle_01_P, STg2_FX__Billboard__Render_Point_P );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Effect__Billboard__Render_Init_Point -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX_Effect__Billboard__Render_Init_Point( STg2_FX__Billboard__Render_Point_P psPoint, STg2_FX_Rnd_Output_PC psRndOut )
{
    psPoint->m_psFile_Data = psPoint->m_psBillboard->m_psFile_Data;
    psPoint->m_vCam_Pos_W = psRndOut->m_psCamera->m_sCamera.m_uCam_Position.m_vF32_04_1;
    psPoint->m_vCam_Up = psRndOut->m_psCamera->m_vCam_Up;
    psPoint->m_vCam_Forward = psRndOut->m_psCamera->m_vCam_Forward;

    psPoint->m_vUV_Mask[0] = tgMH_Init_ELEM_F32_04_1( 0.0F, 0.0F, 0.0F, 0.0F );
    psPoint->m_vUV_Mask[1] = tgMH_Init_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F, 1.0F );
    psPoint->m_vUV_Mask[2] = tgMH_Init_ELEM_F32_04_1( 1.0F, 1.0F, 1.0F, 1.0F );
    psPoint->m_vUV_Mask[3] = tgMH_Init_ELEM_F32_04_1( 1.0F, 0.0F, 1.0F, 0.0F );

    psPoint->m_vBase_CL = psPoint->m_psBillboard->m_sExtend.m_vColour;
}


/* ---- tgFX_Effect__Billboard__Render_Common ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL tgFX_Effect__Billboard__Render_Common( STg2_FX__Billboard__Render_Point_P psPoint, TgVEC_F32_04_1 vdT )
{
    STg2_FX_Billboard__File_Data_CP     psBillboard_File_Data;
    TgUN_V128                           vAlpha;
    TgFLOAT32                           fAlpha;

    psBillboard_File_Data = psPoint->m_psFile_Data;

    vAlpha.m_vF32_04_1 = psPoint->m_vBase_CL;
    fAlpha = vAlpha.m_vF32_04_1.m_aData[3];

    /* Calculate the alpha value of the psBillboard */
    if (0 != (psBillboard_File_Data->m_uiFlags & ETgFX_BILLBOARD_FLAGS__HAS_FADE_ANGLE))
    {
        TgVEC_F32_04_1                    vView;
        TgVEC_F32_04_1                    vView_N;
        TgVEC_F32_04_1                    vDot_Angle;
        TgUN_V128                           vFade_Percent;

        vView = tgMH_SUB_F32_04_1( psPoint->m_vCam_Pos_W, psPoint->m_psBillboard->m_vPos_N2W );
        vView_N = tgMH_NORM_F32_04_1( vView );

        if (psBillboard_File_Data->m_enOrientation == ETgFX_BILLBOARD_ORIENTATION__NONE)
        {
            TgVEC_F32_04_1                    vFace_Direction;

            vFace_Direction = tgMH_QT_TX_F32_04_1( psBillboard_File_Data->m_vPlnZ, psPoint->m_psBillboard->m_qRot_N2W );
            vDot_Angle = tgMH_DOT_F32_04_1( vView_N, vFace_Direction );
            vFade_Percent.m_vF32_04_1 = tgMH_SUB_F32_04_1( vDot_Angle, psBillboard_File_Data->m_vFade_Start );
            vFade_Percent.m_vF32_04_1 = tgMH_DIV_F32_04_1( vFade_Percent.m_vF32_04_1, psBillboard_File_Data->m_vFade_RNG );
            vFade_Percent.m_vF32_04_1 = tgMH_SUB_F32_04_1( KTgONE_V128.m_vF32_04_1, tgMH_SAT_F32_04_1( vFade_Percent.m_vF32_04_1 ) );
            fAlpha = fAlpha * vFade_Percent.m_vS_F32_04_1.x;
        }
        else
        {
            vDot_Angle = tgMH_DOT_F32_04_1( vView_N, psPoint->m_vCam_Forward );
            vFade_Percent.m_vF32_04_1 = tgMH_SUB_F32_04_1( vDot_Angle, psBillboard_File_Data->m_vFade_Start );
            vFade_Percent.m_vF32_04_1 = tgMH_DIV_F32_04_1( vFade_Percent.m_vF32_04_1, psBillboard_File_Data->m_vFade_RNG );
            fAlpha = fAlpha * vFade_Percent.m_vS_F32_04_1.x;
        };
    };

    vAlpha.m_vF32_04_1 = tgMH_SET1_F32_04_1( fAlpha );
    psPoint->m_vCL = tgMH_SEL_F32_04_1( psPoint->m_psBillboard->m_sExtend.m_vColour, vAlpha.m_vF32_04_1, KTg000F_V128.m_vF32_04_1 );

    tgRN_Calc_UV_Animation_F32_04_1( /* Output */ &psPoint->m_psBillboard->m_sExtend.m_vUV_01_Constant, &psPoint->m_psBillboard->m_sExtend.m_vUV_01_Scale,
                              /* Input */ psPoint->m_psBillboard->m_tiMaterial, vdT, psPoint->m_psBillboard->m_vLive_Time );

    tgFX_Effect__Billboard__Render_Reference_Frame( psPoint );

    return (tgCM_NR0_F32( fAlpha ) ? false : true);
}


/* ---- tgFX_Effect__Billboard__Render_Reference_Frame --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX_Effect__Billboard__Render_Reference_Frame( STg2_FX__Billboard__Render_Point_P psPoint )
{
    STg2_FX_Billboard__File_Data_CP     psBillboard_File_Data;
    STg2_FX_Calc_Quad                   sData;
    TgVEC_F32_04_1                    vSize;

    psBillboard_File_Data = psPoint->m_psBillboard->m_psFile_Data;

    vSize = tgMH_MUL_F32_04_1( psPoint->m_psBillboard->m_sExtend.m_vSize, psPoint->m_psBillboard->m_vScale );

    sData.m_vPivot_X = psBillboard_File_Data->m_vPivot_X;
    sData.m_vPivot_Y = psBillboard_File_Data->m_vPivot_Y;
    sData.m_vSize_X = tgMH_SPX_F32_04_1( vSize );
    sData.m_vSize_Y = tgMH_SPY_F32_04_1( vSize );
    sData.m_vPos_W = tgMH_Init_Point_F32_04_1( psPoint->m_psBillboard->m_vPos_N2W );

    switch (psBillboard_File_Data->m_enOrientation)
    {
        case ETgFX_BILLBOARD_ORIENTATION__CAMERA_FACE_SPHERE:
        {
            TgVEC_F32_04_1                    vLook_At;
            TgVEC_F32_04_1                    vNorm_Look_At;
            TgVEC_F32_04_1                    vNorm_Right;

            vLook_At = tgMH_SUB_F32_04_1( psPoint->m_vCam_Pos_W, psPoint->m_psBillboard->m_vPos_N2W );
            vNorm_Look_At = tgMH_NORM_F32_04_1( vLook_At );
            vNorm_Right = tgMH_UCX_F32_04_1( psPoint->m_vCam_Up, vNorm_Look_At );

            sData.m_vDir_Right = vNorm_Right;
            sData.m_vDir_Up = tgMH_UCX_F32_04_1( vNorm_Look_At, vNorm_Right );
            break;
        };

        case ETgFX_BILLBOARD_ORIENTATION__CAMERA_FACE_SPHERE__FIXED_Y:
        {
            TgUN_V128                           vLook_At;
            TgVEC_F32_04_1                      vNorm_Look_At;

            vLook_At.m_vF32_04_1 = tgMH_SUB_F32_04_1( psPoint->m_vCam_Pos_W, psPoint->m_psBillboard->m_vPos_N2W );
            vLook_At.m_vF32_04_1.m_aData[1] = 0.0F;
            vNorm_Look_At = tgMH_NORM_F32_04_1( vLook_At.m_vF32_04_1 );

            sData.m_vDir_Up = KTgUNIT_Y_V128.m_vF32_04_1;
            sData.m_vDir_Right = tgMH_UCX_F32_04_1( sData.m_vDir_Up, vNorm_Look_At );
            break;
        };

        case ETgFX_BILLBOARD_ORIENTATION__CAMERA_FACE_PLANE:
        case ETgFX_BILLBOARD_ORIENTATION__CAMERA_FACE_PLANE__FIXED_Y:
        case ETgFX_BILLBOARD_ORIENTATION__NONE:
            sData.m_vDir_Right = tgMH_QT_TX_F32_04_1( psBillboard_File_Data->m_vPlnX, psPoint->m_psBillboard->m_qRot_N2W );
            sData.m_vDir_Up = tgMH_QT_TX_F32_04_1( psBillboard_File_Data->m_vPlnY, psPoint->m_psBillboard->m_qRot_N2W );
            break;

        default:
            TgS_NO_DEFAULT( break );
    }

    tgFX_Calc_Quad( /* Output */ psPoint->m_avPos_W, psPoint->m_avBasis, /* Input */ psPoint->m_psBillboard->m_sExtend.m_fSpin, &sData );
}


/* ---- tgFX_Effect__Billboard__Render_Write_Quad_00 ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgVOID tgFX_Effect__Billboard__Render_Write_Quad_00( STg2_KN_GPU_Vertex_Particle_00_P psVert, STg2_FX__Billboard__Render_Point_P psPoint )
{
    unsigned short                      sIndex_Gradient[] = { 0, 1, 2, 3, 0, 2 };
    TgVEC_F32_04_1                      vUV;
    TgRSIZE                             uiIndex, uiVert;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(sIndex_Gradient); ++uiIndex)
    {
        uiVert = sIndex_Gradient[uiIndex];
        vUV = tgMH_MAD_F32_04_1( psPoint->m_vUV_Mask[uiVert], psPoint->m_psBillboard->m_sExtend.m_vUV_01_Scale, psPoint->m_psBillboard->m_sExtend.m_vUV_01_Constant );

        psVert[uiIndex].m_vS0 = psPoint->m_avPos_W[uiVert];
        psVert[uiIndex].m_vUV = vUV;
        psVert[uiIndex].m_vCL = psPoint->m_vCL;
    };
}


/* ---- tgFX_Effect__Billboard__Render_Write_Quad_01 ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgVOID tgFX_Effect__Billboard__Render_Write_Quad_01( STg2_KN_GPU_Vertex_Particle_01_P psVert, STg2_FX__Billboard__Render_Point_P psPoint )
{
    unsigned short                      sIndex_Gradient[] = { 0, 1, 2, 3, 0, 2 };
    TgVEC_F32_04_1                      vUV;
    TgRSIZE                             uiIndex, uiVert;

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(sIndex_Gradient); ++uiIndex)
    {
        uiVert = sIndex_Gradient[uiIndex];
        vUV = tgMH_MAD_F32_04_1( psPoint->m_vUV_Mask[uiVert], psPoint->m_psBillboard->m_sExtend.m_vUV_01_Scale, psPoint->m_psBillboard->m_sExtend.m_vUV_01_Constant );

        psVert[uiIndex].m_vS0 = psPoint->m_avPos_W[uiVert];
        psVert[uiIndex].m_vT0 = psPoint->m_avBasis[0];
        psVert[uiIndex].m_vB0 = psPoint->m_avBasis[1];
        psVert[uiIndex].m_vUV = vUV;
        psVert[uiIndex].m_vCL = psPoint->m_vCL;
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

/* ---- T(tgFX__Render__Billboard_Render_Generate_Particle) ---------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F32 T(tgFX__Render__Billboard_Render_Generate_Particle)( STg2_FX_Rnd_Output_PC psRndOut, STg2_RN_Particle_Header_PC psHeader, STg2_FX__Billboard_P psBillboard )
{
    union
    {
        TgUINT_F08_P                        pui;
        T(STg2_KN_GPU_Vertex_Particle)*     ps;
    }                                   sVert;
    STg2_FX__Billboard__Render_Point    sPoint;
    TgRSIZE                             uiVert;

    if (KTgMAX_RSIZE == psHeader->m_uiBuffer_Offset)
    {
        return (0);
    };
    sVert.pui = psRndOut->m_puiBuffer + psHeader->m_uiBuffer_Offset;

    tgMM_Set_U08_0x00( &sPoint, sizeof( sPoint ) );
    sPoint.m_psBillboard = psBillboard;
    tgFX_Effect__Billboard__Render_Init_Point( &sPoint, psRndOut );

    if (!tgFX_Effect__Billboard__Render_Common( &sPoint, psRndOut->m_uDT.m_vF32_04_1 ))
    {
        return (0);
    }

    psBillboard->m_vBA_Max_W = tgMH_SET1_F32_04_1( -FLT_MAX );
    psBillboard->m_vBA_Min_W = tgMH_SET1_F32_04_1( FLT_MAX );

    T(tgFX_Effect__Billboard__Render_Write_Quad)( sVert.ps, &sPoint );

    for (uiVert = 0; uiVert < 6; ++uiVert)
    {
        psBillboard->m_vBA_Max_W = tgMH_MAX_F32_04_1( psBillboard->m_vBA_Max_W, sPoint.m_avPos_W[uiVert] );
        psBillboard->m_vBA_Min_W = tgMH_MIN_F32_04_1( psBillboard->m_vBA_Min_W, sPoint.m_avPos_W[uiVert] );
    };

    return (6);
}


/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* == Effect ===================================================================================================================================================================== */

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif

