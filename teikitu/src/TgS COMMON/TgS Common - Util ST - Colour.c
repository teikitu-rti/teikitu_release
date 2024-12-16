/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util ST - Colour.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
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
