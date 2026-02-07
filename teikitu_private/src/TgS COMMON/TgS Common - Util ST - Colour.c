/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util ST - Colour.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgALIGN(16) TgVEC_F32_04_1_C         KTg_BLACK_G10_P709_F32_04       = { 0.0F, 0.0F, 0.0F, 1.0F };
TgALIGN(16) TgVEC_F32_04_1_C         KTg_WHITE_G10_P709_F32_04       = { 1.0F, 1.0F, 1.0F, 1.0F };
TgALIGN(16) TgVEC_F32_04_1_C         KTg_RED_G10_P709_F32_04         = { 1.0F, 0.0F, 0.0F, 1.0F };
TgALIGN(16) TgVEC_F32_04_1_C         KTg_GREEN_G10_P709_F32_04       = { 0.0F, 1.0F, 0.0F, 1.0F };
TgALIGN(16) TgVEC_F32_04_1_C         KTg_BLUE_G10_P709_F32_04        = { 0.0F, 0.0F, 1.0F, 1.0F };
TgALIGN(16) TgVEC_F32_04_1_C         KTg_YELLOW_G10_P709_F32_04      = { 1.0F, 1.0F, 0.0F, 1.0F };
TgALIGN(16) TgVEC_F32_04_1_C         KTg_MAGENTA_G10_P709_F32_04     = { 1.0F, 0.0F, 1.0F, 1.0F };
TgALIGN(16) TgVEC_F32_04_1_C         KTg_CYAN_G10_P709_F32_04        = { 0.0F, 1.0F, 1.0F, 1.0F };

TgALIGN(16) TgCOLOUR32_C             KTg_BLACK_G10_P709_U32           = { TgCOLOUR_FROM_RGBA( 0x00u, 0x00u, 0x00u, 0xFFu ) };
TgALIGN(16) TgCOLOUR32_C             KTg_WHITE_G10_P709_U32           = { TgCOLOUR_FROM_RGBA( 0xFFu, 0xFFu, 0xFFu, 0xFFu ) };
TgALIGN(16) TgCOLOUR32_C             KTg_RED_G10_P709_U32             = { TgCOLOUR_FROM_RGBA( 0xFFu, 0x00u, 0x00u, 0xFFu ) };
TgALIGN(16) TgCOLOUR32_C             KTg_GREEN_G10_P709_U32           = { TgCOLOUR_FROM_RGBA( 0x00u, 0xFFu, 0x00u, 0xFFu ) };
TgALIGN(16) TgCOLOUR32_C             KTg_BLUE_G10_P709_U32            = { TgCOLOUR_FROM_RGBA( 0x00u, 0x00u, 0xFFu, 0xFFu ) };
TgALIGN(16) TgCOLOUR32_C             KTg_YELLOW_G10_P709_U32          = { TgCOLOUR_FROM_RGBA( 0xFFu, 0xFFu, 0x00u, 0xFFu ) };
TgALIGN(16) TgCOLOUR32_C             KTg_MAGENTA_G10_P709_U32         = { TgCOLOUR_FROM_RGBA( 0xFFu, 0x00u, 0xFFu, 0xFFu ) };
TgALIGN(16) TgCOLOUR32_C             KTg_CYAN_G10_P709_U32            = { TgCOLOUR_FROM_RGBA( 0x00u, 0xFFu, 0xFFu, 0xFFu ) };


/* ---- tgCM_CL_F32_Convert_HSV_To_RGB ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVEC_F32_04_1 tgCM_CL_F32_Convert_HSV_To_RGB( TgVEC_F32_04_1_C vCL )
{
    TgUN_V128                           uRGB;
    TgFLOAT32                           fC, fX, fM;
    TgSINT_E32                          iSector;

    uRGB.m_vF32_04_1 = vCL;

    /* Clamp inputs to valid ranges - allow HDR values for V component */
    uRGB.m_vS_F32_04_1.x = tgPM_FMOD_F32(uRGB.m_vS_F32_04_1.x, 360.0F);
    if (uRGB.m_vS_F32_04_1.x < 0.0F) uRGB.m_vS_F32_04_1.x += 360.0F;
    uRGB.m_vS_F32_04_1.y = tgCM_CLP_F32(uRGB.m_vS_F32_04_1.y, 0.0F, 1.0F);
    uRGB.m_vS_F32_04_1.z = tgCM_MAX_F32(uRGB.m_vS_F32_04_1.z, 0.0F); /* Only clamp negative values for V */

    if (uRGB.m_vS_F32_04_1.y <= 0.0F)
    {
        /* Achromatic case (grayscale) - preserve HDR brightness */
        uRGB.m_vS_F32_04_1.x = uRGB.m_vS_F32_04_1.y = uRGB.m_vS_F32_04_1.z;
        return (uRGB.m_vF32_04_1);
    }

    fC = uRGB.m_vS_F32_04_1.z * uRGB.m_vS_F32_04_1.y;
    fX = fC * (1.0F - tgPM_ABS_F32(tgPM_FMOD_F32(uRGB.m_vS_F32_04_1.x / 60.0F, 2.0F) - 1.0F));
    fM = uRGB.m_vS_F32_04_1.z - fC;

    iSector = (TgSINT_E32)(uRGB.m_vS_F32_04_1.x / 60.0F) % 6;


    /* After this point the original source information is no longer needed and we reuse the vector for a return result. In all cases alpha is returned without modification. */

    switch (iSector)
    {
        case 0: uRGB.m_vS_F32_04_1.x = fC; uRGB.m_vS_F32_04_1.y = fX; uRGB.m_vS_F32_04_1.z = 0.0F; break; /* Red to Yellow */
        case 1: uRGB.m_vS_F32_04_1.x = fX; uRGB.m_vS_F32_04_1.y = fC; uRGB.m_vS_F32_04_1.z = 0.0F; break; /* Yellow to Green */
        case 2: uRGB.m_vS_F32_04_1.x = 0.0F; uRGB.m_vS_F32_04_1.y = fC; uRGB.m_vS_F32_04_1.z = fX; break; /* Green to Cyan */
        case 3: uRGB.m_vS_F32_04_1.x = 0.0F; uRGB.m_vS_F32_04_1.y = fX; uRGB.m_vS_F32_04_1.z = fC; break; /* Cyan to Blue */
        case 4: uRGB.m_vS_F32_04_1.x = fX; uRGB.m_vS_F32_04_1.y = 0.0F; uRGB.m_vS_F32_04_1.z = fC; break; /* Blue to Magenta */
        case 5: uRGB.m_vS_F32_04_1.x = fC; uRGB.m_vS_F32_04_1.y = 0.0F; uRGB.m_vS_F32_04_1.z = fX; break; /* Magenta to Red */
        default: uRGB.m_vS_F32_04_1.x = uRGB.m_vS_F32_04_1.y = uRGB.m_vS_F32_04_1.z = 0.0F; break;
    }

    /* Add the brightness offset */
    uRGB.m_vS_F32_04_1.x += fM;
    uRGB.m_vS_F32_04_1.y += fM;
    uRGB.m_vS_F32_04_1.z += fM;

    return (uRGB.m_vF32_04_1);
}


/* ---- tgCM_CL_F32_Convert_RGB_To_HSV ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVEC_F32_04_1 tgCM_CL_F32_Convert_RGB_To_HSV( TgVEC_F32_04_1_C vCL )
{
    TgUN_V128                           uRGB, uResult;
    TgFLOAT32                           fMax, fMin, fDelta;

    uRGB.m_vF32_04_1 = vCL;

    /* Only clamp negative values to zero - allow HDR values > 1.0 */
    uRGB.m_vS_F32_04_1.x = tgCM_MAX_F32(uRGB.m_vS_F32_04_1.x, 0.0F);
    uRGB.m_vS_F32_04_1.y = tgCM_MAX_F32(uRGB.m_vS_F32_04_1.y, 0.0F);
    uRGB.m_vS_F32_04_1.z = tgCM_MAX_F32(uRGB.m_vS_F32_04_1.z, 0.0F);

    fMax = tgCM_MAX_F32(uRGB.m_vS_F32_04_1.x, tgCM_MAX_F32(uRGB.m_vS_F32_04_1.y, uRGB.m_vS_F32_04_1.z));
    fMin = tgCM_MIN_F32(uRGB.m_vS_F32_04_1.x, tgCM_MIN_F32(uRGB.m_vS_F32_04_1.y, uRGB.m_vS_F32_04_1.z));
    fDelta = fMax - fMin;


    /* After this point the original source information is no longer needed and we reuse the vector for a return result. In all cases alpha is returned without modification. */

    /* Calculate Value - preserve HDR range */
    uResult.m_vS_F32_04_1.z = fMax;
    uResult.m_vS_F32_04_1.w = uRGB.m_vS_F32_04_1.w;

    /* Calculate Saturation */
    if (fMax <= 0.0F)
    {
        uResult.m_vS_F32_04_1.y = 0.0F;
        uResult.m_vS_F32_04_1.x = 0.0F; /* Undefined hue for black */
        return (uResult.m_vF32_04_1);
    }
    uResult.m_vS_F32_04_1.y = fDelta / fMax;

    /* Calculate Hue */
    if (fDelta <= 0.0F)
    {
        uResult.m_vS_F32_04_1.x = 0.0F; /* Undefined hue for grayscale */
        return (uResult.m_vF32_04_1);
    }

    if (fMax == uRGB.m_vS_F32_04_1.x)
    {
        uResult.m_vS_F32_04_1.x = 60.0F * (tgPM_FMOD_F32((uRGB.m_vS_F32_04_1.y - uRGB.m_vS_F32_04_1.z) / fDelta, 6.0F));
    }
    else if (fMax == uRGB.m_vS_F32_04_1.y)
    {
        uResult.m_vS_F32_04_1.x = 60.0F * (((uRGB.m_vS_F32_04_1.z - uRGB.m_vS_F32_04_1.x) / fDelta) + 2.0F);
    }
    else /* fMax == uRGB.m_vS_F32_04_1.z */
    {
        uResult.m_vS_F32_04_1.x = 60.0F * (((uRGB.m_vS_F32_04_1.x - uRGB.m_vS_F32_04_1.y) / fDelta) + 4.0F);
    }

    if (uResult.m_vS_F32_04_1.x < 0.0F)
    {
        uResult.m_vS_F32_04_1.x += 360.0F;
    }

    return (uResult.m_vF32_04_1);
}
