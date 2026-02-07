/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Utils.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_Init_Camera ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_Init_Camera( STg2_KN_GPU_Camera_PC psCamera, STg2_KN_GPU_Camera_Configuration_CPC psConfiguration, TgVEC_F32_04_1_C vUp )
{
    TgUN_V128_C                         uUp = { .m_vF32_04_1 = vUp };
    STg2_KN_GPU_Camera_Shared_P         psCamera_Shared;
    TgVEC_UN_F32_04_4                   uM0;

    TgPARAM_CHECK( nullptr != psCamera );
    TgPARAM_CHECK( nullptr != psConfiguration );

    if (&psCamera->m_sConfiguration != psConfiguration)
    {
        psCamera->m_sConfiguration = *psConfiguration;
    }

    psCamera_Shared = &psCamera->m_sCamera_Shared;

    /* Calculate the reference frame, view and projection matrices */
    tgMH_PProj_FoVLH_S_F32_04_4( &uM0.m_mS_F32_04_4, psConfiguration->m_fFoV, psConfiguration->m_fAspect_Ratio, psConfiguration->m_fNear, psConfiguration->m_fFar );
    psCamera_Shared->m_avC2S = uM0.m_mF32_04_4;
    tgMH_INV_F32_04_4( &psCamera_Shared->m_avS2C, &psCamera_Shared->m_avC2S );

    tgMH_LookLH_S_F32_04_4( &uM0.m_mS_F32_04_4, psConfiguration->m_uCamera_Position.m_vS_F32_04_1, psConfiguration->m_uCamera_Target.m_vS_F32_04_1, uUp.m_vS_F32_04_1 );
    psCamera_Shared->m_avW2C = uM0.m_mF32_04_4;
    tgMH_INV_F32_04_4(&psCamera_Shared->m_avC2W, &psCamera_Shared->m_avW2C);

    tgMH_CAT_F32_04_4( &psCamera_Shared->m_avW2S, &psCamera_Shared->m_avW2C, &psCamera_Shared->m_avC2S );
    tgMH_INV_F32_04_4( &psCamera_Shared->m_avS2W, &psCamera_Shared->m_avW2S );

    psCamera_Shared->m_vCam_Right = tgMH_Query_Axis_0_F32_04_4( &psCamera_Shared->m_avW2C );
    psCamera_Shared->m_vCam_Up = tgMH_Query_Axis_1_F32_04_4( &psCamera_Shared->m_avW2C );
    psCamera_Shared->m_vCam_Forward = tgMH_Query_Axis_2_F32_04_4( &psCamera_Shared->m_avW2C );

   /* Bound #1: Axis Aligned Bounding Box - This is an average bounding volume for the frustum.  It is used to compute the spherical bounding volume and is used as part */
   /* of the shadow culling process.  Ideally the shadow system would use a convex hull or a k-dop; however, simple aggregation of an axis aligned bounding box is easy */
   /* and may only have minimal impact given the other forms of culling that take place. */

   {
        /* Step #1 - Reverse project a unit cube from screen space back into the world.  This will give us the camera frustum. */

        TgVEC_F32_04_1_C                  vPPP = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1(+1.0F, +1.0F, +1.0F), &psCamera_Shared->m_avS2W );
        TgVEC_F32_04_1_C                  vPPN = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1(+1.0F, +1.0F, -1.0F), &psCamera_Shared->m_avS2W );
        TgVEC_F32_04_1_C                  vPNP = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1(+1.0F, -1.0F, +1.0F), &psCamera_Shared->m_avS2W );
        TgVEC_F32_04_1_C                  vPNN = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1(+1.0F, -1.0F, -1.0F), &psCamera_Shared->m_avS2W );
        TgVEC_F32_04_1_C                  vNPP = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1(-1.0F, +1.0F, +1.0F), &psCamera_Shared->m_avS2W );
        TgVEC_F32_04_1_C                  vNPN = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1(-1.0F, +1.0F, -1.0F), &psCamera_Shared->m_avS2W );
        TgVEC_F32_04_1_C                  vNNP = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1(-1.0F, -1.0F, +1.0F), &psCamera_Shared->m_avS2W );
        TgVEC_F32_04_1_C                  vNNN = tgMH_TX_F32_04_4( tgMH_Init_Point_ELEM_F32_04_1(-1.0F, -1.0F, -1.0F), &psCamera_Shared->m_avS2W );

        /* Step #2 - Take the per axis min and max values from the collection of eight points to construct the AABB. */

        TgVEC_F32_04_1_C                  vMin01 = tgMH_MIN_F32_04_1( vPPP, vPPN );
        TgVEC_F32_04_1_C                  vMin23 = tgMH_MIN_F32_04_1( vPNP, vPNN );
        TgVEC_F32_04_1_C                  vMin45 = tgMH_MIN_F32_04_1( vNPP, vNPN );
        TgVEC_F32_04_1_C                  vMin67 = tgMH_MIN_F32_04_1( vNNP, vNNN );
        TgVEC_F32_04_1_C                  vMin03 = tgMH_MIN_F32_04_1( vMin01, vMin23 );
        TgVEC_F32_04_1_C                  vMin47 = tgMH_MIN_F32_04_1( vMin45, vMin67 );

        TgVEC_F32_04_1_C                  vMax01 = tgMH_MAX_F32_04_1( vPPP, vPPN );
        TgVEC_F32_04_1_C                  vMax23 = tgMH_MAX_F32_04_1( vPNP, vPNN );
        TgVEC_F32_04_1_C                  vMax45 = tgMH_MAX_F32_04_1( vNPP, vNPN );
        TgVEC_F32_04_1_C                  vMax67 = tgMH_MAX_F32_04_1( vNNP, vNNN );
        TgVEC_F32_04_1_C                  vMax03 = tgMH_MAX_F32_04_1( vMax01, vMax23 );
        TgVEC_F32_04_1_C                  vMax47 = tgMH_MAX_F32_04_1( vMax45, vMax67 );

        psCamera_Shared->m_vFrustum_Min_BA = tgMH_MIN_F32_04_1( vMin03, vMin47 );
        psCamera_Shared->m_vFrustum_Max_BA = tgMH_MAX_F32_04_1( vMax03, vMax47 );
   }

    /* Bound #2: Sphere Bounding Volume - This is the minimal/fastest representation for BSP perusal.  This is now easily calculated from the axis aligned bounding box. */

    psCamera_Shared->m_vFrustum_Centroid = tgMH_MUL_F32_04_1( tgMH_SET1_F32_04_1(0.5F), tgMH_ADD_F32_04_1( psCamera_Shared->m_vFrustum_Min_BA, psCamera_Shared->m_vFrustum_Max_BA ) );
    psCamera_Shared->m_vFrustum_Radius_Squared = tgMH_LSQ_F32_04_1( tgMH_SUB_F32_04_1( psCamera_Shared->m_vFrustum_Max_BA, psCamera_Shared->m_vFrustum_Centroid ) );

    /* Bound #3: Frustum Half-Space.  This is a four element vector (similar to a plane equation) that divides space into two half spaces.  The construction is such that */
    /* the scalar product is strictly positive in one half space and strictly negative in the other half space.  It is a non-normalized plane equation; thus, the scale */
    /* value is not a distance function but it can still be used to test for half space intersection. */

    {
        TgVEC_F32_04_1_C                  vAxis0 = tgMH_Query_Axis_0_F32_04_4( &psCamera_Shared->m_avW2C );
        TgVEC_F32_04_1_C                  vAxis1 = tgMH_Query_Axis_1_F32_04_4( &psCamera_Shared->m_avW2C );
        TgVEC_F32_04_1_C                  vAxis2 = tgMH_Query_Axis_2_F32_04_4( &psCamera_Shared->m_avW2C );
        TgVEC_F32_04_1_C                  vAxis3 = tgMH_Query_Axis_3_F32_04_4( &psCamera_Shared->m_avW2C );

        psCamera_Shared->m_avFrustum_PN[ETgFRUSTUM_PLANE__NEAR] = tgMH_NORM_F32_04_1( tgMH_ADD_F32_04_1( vAxis3, vAxis2 ) );
        psCamera_Shared->m_avFrustum_PN[ETgFRUSTUM_PLANE__FAR] = tgMH_NORM_F32_04_1( tgMH_SUB_F32_04_1( vAxis3, vAxis2 ) );
        psCamera_Shared->m_avFrustum_PN[ETgFRUSTUM_PLANE__LEFT] = tgMH_NORM_F32_04_1( tgMH_ADD_F32_04_1( vAxis3, vAxis0 ) );
        psCamera_Shared->m_avFrustum_PN[ETgFRUSTUM_PLANE__RIGHT] = tgMH_NORM_F32_04_1( tgMH_SUB_F32_04_1( vAxis3, vAxis0 ) );
        psCamera_Shared->m_avFrustum_PN[ETgFRUSTUM_PLANE__TOP] = tgMH_NORM_F32_04_1( tgMH_SUB_F32_04_1( vAxis3, vAxis1 ) );
        psCamera_Shared->m_avFrustum_PN[ETgFRUSTUM_PLANE__BOTTOM] = tgMH_NORM_F32_04_1( tgMH_ADD_F32_04_1( vAxis3, vAxis1 ) );
    }
}


/* ---- tgKN_GPU_Colour_Grading_CPU ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVEC_S_F32_04_1 tgKN_GPU_Colour_Grading_CPU( TgVEC_S_F32_04_1 vColour, STg2_KN_GPU_Output_DESC_CPC psOutput_DESC )
{
    if (nullptr == psOutput_DESC)
        return (vColour);

    if (ETgKN_GPU_HLSL_COLOUR_SPACE_G2084_P2020 == psOutput_DESC->m_iColour_Space)
    {
        TgVEC_S_F32_04_4_C                  mConversion =
        {
            .m_vC0 = { { 0.627402F, 0.329292F, 0.043306F, 0.0F } },
            .m_vC1 = { { 0.069095F, 0.919544F, 0.011360F, 0.0F } },
            .m_vC2 = { { 0.016394F, 0.088028F, 0.895578F, 0.0F } },
            .m_vC3 = { { 0.0F, 0.0F, 0.0F, 1.0F } }
        };

        TgFLOAT32_C                         m2 = 2523.0F / 4096.0F * 128.0F;
        TgFLOAT32_C                         c3 = 2392.0F / 4096.0F * 32.0F;
        TgVEC_S_F32_04_1                    cp;

        /* Render buffer is 10bit per channel, normalized, or 1 is max brightness. To match the SDR rendering, we need to scale down the brightness of the colour, similar to
            how we scale up the colour value (for similar reasons) for the scRGB F16 clear colour. */

        /* P709 to P2020 */

        vColour = tgMH_TX_S_F32_04_4( vColour, &mConversion );

        /* Adjust for max nits in ST2084 (max nits of 10,000), and SDR content on HDR monitor set to 50% in Windows Settings. */

        vColour.r *= psOutput_DESC->m_fSDR_In_HDR_Nits_Level / 10000.0F;
        vColour.g *= psOutput_DESC->m_fSDR_In_HDR_Nits_Level / 10000.0F;
        vColour.b *= psOutput_DESC->m_fSDR_In_HDR_Nits_Level / 10000.0F;

        /* Transfer to ST2084 */

        cp.r = tgPM_POW_F32( tgPM_ABS_F32( vColour.r ), (2610.0F / 4096.0F / 4.0F) );
        cp.g = tgPM_POW_F32( tgPM_ABS_F32( vColour.g ), (2610.0F / 4096.0F / 4.0F) );
        cp.b = tgPM_POW_F32( tgPM_ABS_F32( vColour.b ), (2610.0F / 4096.0F / 4.0F) );

        vColour.r = tgPM_POW_F32( ((3424.0F / 4096.0F) + (2413.0F / 4096.0F * 32.0F) * cp.r) / (1.0F + c3 * cp.r), m2 );
        vColour.g = tgPM_POW_F32( ((3424.0F / 4096.0F) + (2413.0F / 4096.0F * 32.0F) * cp.g) / (1.0F + c3 * cp.g), m2 );
        vColour.b = tgPM_POW_F32( ((3424.0F / 4096.0F) + (2413.0F / 4096.0F * 32.0F) * cp.b) / (1.0F + c3 * cp.b), m2 );
    }
    else if (ETgKN_GPU_HLSL_COLOUR_SPACE_G10_P709 == psOutput_DESC->m_iColour_Space)
    {
        /* scRGB (1,1,1) is considered to be D65 at 80 nits. Since HDR is scene referred, we can directly scale the RGB values according to the current OS configuration. */
        vColour.r *= psOutput_DESC->m_fSDR_In_HDR_Nits_Level / 80.0F;
        vColour.g *= psOutput_DESC->m_fSDR_In_HDR_Nits_Level / 80.0F;
        vColour.b *= psOutput_DESC->m_fSDR_In_HDR_Nits_Level / 80.0F;
    }
    else if (ETgKN_GPU_HLSL_COLOUR_SPACE_G22_P709 == psOutput_DESC->m_iColour_Space)
    {
        /* Transform to G22 as needed for the Colour Spaces in Gamma 2.2 */
        vColour.r = vColour.r < 0.0031308F ? 12.92F * vColour.r : 1.055F * tgPM_POW_F32( tgPM_ABS_F32( vColour.r ), 1.0F / 2.4F ) - 0.055F;
        vColour.g = vColour.g < 0.0031308F ? 12.92F * vColour.g : 1.055F * tgPM_POW_F32( tgPM_ABS_F32( vColour.g ), 1.0F / 2.4F ) - 0.055F;
        vColour.b = vColour.b < 0.0031308F ? 12.92F * vColour.b : 1.055F * tgPM_POW_F32( tgPM_ABS_F32( vColour.b ), 1.0F / 2.4F ) - 0.055F;
    }

    return (vColour);
}
