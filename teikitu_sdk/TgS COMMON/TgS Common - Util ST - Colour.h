/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util ST - Colour.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_ST_COLOUR_H)
#define TGS_COMMON_UTIL_ST_COLOUR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_UTIL_ST_COLOUR Colour APIs
    @ingroup TGS_COMMON_UTILITY_ST
*/

    /** @defgroup TGS_COMMON_UTIL_ST_COLOUR_F32 Four Element Floating-Point
        @ingroup TGS_COMMON_UTIL_ST_COLOUR
    */

    /** @defgroup TGS_COMMON_UTIL_ST_COLOUR_U32 32bit Hexadecimal
        @ingroup TGS_COMMON_UTIL_ST_COLOUR
    */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTg_BLACK_G10_P709_F32_04;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTg_WHITE_G10_P709_F32_04;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTg_RED_G10_P709_F32_04;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTg_GREEN_G10_P709_F32_04;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTg_BLUE_G10_P709_F32_04;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTg_YELLOW_G10_P709_F32_04;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTg_MAGENTA_G10_P709_F32_04;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTg_CYAN_G10_P709_F32_04;

TgEXTN TgALIGN(16) TgCOLOUR32_C             KTg_BLACK_G10_P709_U32;
TgEXTN TgALIGN(16) TgCOLOUR32_C             KTg_WHITE_G10_P709_U32;
TgEXTN TgALIGN(16) TgCOLOUR32_C             KTg_RED_G10_P709_U32;
TgEXTN TgALIGN(16) TgCOLOUR32_C             KTg_GREEN_G10_P709_U32;
TgEXTN TgALIGN(16) TgCOLOUR32_C             KTg_BLUE_G10_P709_U32;
TgEXTN TgALIGN(16) TgCOLOUR32_C             KTg_YELLOW_G10_P709_U32;
TgEXTN TgALIGN(16) TgCOLOUR32_C             KTg_MAGENTA_G10_P709_U32;
TgEXTN TgALIGN(16) TgCOLOUR32_C             KTg_CYAN_G10_P709_U32;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- TgFCOLOUR ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/*# NOTE: All colours should also be matched with a colour space enumeration */
/** @addtogroup TGS_COMMON_UTIL_ST_COLOUR_F32 */
/** @{ */

/** @brief Initialize a colour value using four floating point values (co-ordinate values in the colour space)
    @param [in] ARG1 Red co-ordinate for the colour
    @param [in] ARG2 Green co-ordinate for the colour
    @param [in] ARG3 blue co-ordinate for the colour
    @param [in] ARG4 Alpha co-ordinate for the colour
    @return Four element floating-point vector */
TgINLINE TgVEC_F32_04_1
tgCM_CL_F32_Init_F32(
    TgFLOAT32_C ARG1, TgFLOAT32_C ARG2, TgFLOAT32_C ARG3, TgFLOAT32_C ARG4 );

/** @brief Initialize a colour value using a single 32bit hexadecimal colour (co-ordinate values in the colour space)
    @param [in] ARG1 32-bit hexadecimal colour value
    @return Four element floating-point vector */
TgINLINE TgVEC_F32_04_1
tgCM_CL_F32_Init_U32(
    TgUINT_E32_C ARG1 );


/** @brief Calculate the brightness of the colour (the average of the three colour values)
    @param [in] ARG Four element floating-point vector
    @return The result of calculating the brightness of the colour (as an unsigned 16bit value)*/
TgINLINE TgUINT_E16
tgCM_CL_F32_Brightness_U16(
    TgVEC_F32_04_1_C ARG );

/** @brief Calculate the brightness of the colour (the average of the three colour values)
    @param [in] ARG Four element floating-point vector
    @return The result of calculating the brightness of the colour (floating-point value able to represent HDR results)*/
TgINLINE TgFLOAT32
tgCM_CL_F32_Brightness_F32(
    TgVEC_F32_04_1_C ARG );

/** @brief Calculate the brightness of the colour (the average of the max and min of the colour values)
    @param [in] ARG Four element floating-point vector
    @return The result of calculating the lightness of the colour */
TgINLINE TgFLOAT32
tgCM_CL_F32_Lightness(
    TgVEC_F32_04_1_C ARG );

/** @brief Calculate the luminance of the colour (NTSC weighted balance of the colour values)
    @param [in] ARG Four element floating-point vector
    @return The result of calculating the luminance of the colour */
TgINLINE TgFLOAT32
tgCM_CL_F32_Luminance(
    TgVEC_F32_04_1_C ARG );

/** @brief Convert a colour from HSV to RGB color representation.
    @param [in,out] ARG Four element floating-point vector. On input the H, S, and V values are stored in the x, y, and z elements respectively.
                        On output the R, G, and B values are stored in the x, y, and z elements respectively. The w element is unchanged. */
TgEXTN TgVEC_F32_04_1
tgCM_CL_F32_Convert_HSV_To_RGB(
    TgVEC_F32_04_1_C ARG );

/** @brief Convert a colour from RGB to HSV color representation.
    @param [in,out] ARG Four element floating-point vector. On input the R, G, and B values are stored in the x, y, and z elements respectively.
                        On output the H, S, and V values are stored in the x, y, and z elements respectively. The w element is unchanged. */
TgEXTN TgVEC_F32_04_1
tgCM_CL_F32_Convert_RGB_To_HSV(
    TgVEC_F32_04_1_C ARG );


/** @brief Return the red co-ordinate of the colour
    @param [in] ARG Four element floating-point vector
    @return The red co-ordinate of the colour */
TgINLINE TgFLOAT32
tgCM_CL_F32_Query_R_F32(
    TgVEC_F32_04_1_C ARG );

/** @brief Return the green co-ordinate of the colour
    @param [in] ARG Four element floating-point vector
    @return The green co-ordinate of the colour */
TgINLINE TgFLOAT32
tgCM_CL_F32_Query_G_F32(
    TgVEC_F32_04_1_C ARG );

/** @brief Return the blue co-ordinate of the colour
    @param [in] ARG Four element floating-point vector
    @return The blue co-ordinate of the colour */
TgINLINE TgFLOAT32
tgCM_CL_F32_Query_B_F32(
    TgVEC_F32_04_1_C ARG );

/** @brief Return the alpha co-ordinate of the colour
    @param [in] ARG Four element floating-point vector
    @return The alpha co-ordinate of the colour */
TgINLINE TgFLOAT32
tgCM_CL_F32_Query_A_F32(
    TgVEC_F32_04_1_C ARG );

/** @} TGS_COMMON_UTIL_ST_COLOUR_F32 */


/* ---- TgCOLOUR32 --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/*# NOTE: All colours should also be matched with a colour space enumeration */
/** @addtogroup TGS_COMMON_UTIL_ST_COLOUR_U32 */
/** @{ */

/** @brief Initialize a colour value using four bytes (co-ordinate values in the colour space)
    @param [in] ARG1 Red co-ordinate for the colour
    @param [in] ARG2 Green co-ordinate for the colour
    @param [in] ARG3 blue co-ordinate for the colour
    @param [in] ARG4 Alpha co-ordinate for the colour
    @return A 32-bit unsigned integer used to store a hexadecimal colour value */
TgINLINE TgCOLOUR32
tgCM_CL_U32_Init_U08(
    TgUINT_E08_C ARG1, TgUINT_E08_C ARG2, TgUINT_E08_C ARG3, TgUINT_E08_C ARG4 );

/** @brief Initialize a colour value using a single 32bit hexadecimal colour (co-ordinate values in the colour space)
    @param [in] ARG1 32-bit hexadecimal colour value
    @return A 32-bit unsigned integer used to store a hexadecimal colour value */
TgINLINE TgCOLOUR32
tgCM_CL_U32_Init_U32(
    TgUINT_E32_C ARG1 );

/** @brief Initialize a colour value using a four element floating-point vector (co-ordinate values in the colour space)
    @param [in] ARG1 Four element floating-point vector
    @return A 32-bit unsigned integer used to store a hexadecimal colour value */
TgINLINE TgCOLOUR32
tgCM_CL_U32_Init_F32(
    TgVEC_F32_04_1_C ARG1 );


/** @brief Calculate the brightness of the colour (the average of the three colour values)
    @param [in] ARG 32-bit unsigned integer used to store a hexadecimal colour value
    @return The result of calculating the brightness of the colour (as an unsigned 16bit value)*/
TgINLINE TgUINT_E16
tgCM_CL_U32_Brightness_U16(
    TgCOLOUR32_C ARG );

/** @brief Calculate the brightness of the colour (the average of the three colour values)
    @param [in] ARG 32-bit unsigned integer used to store a hexadecimal colour value
    @return The result of calculating the brightness of the colour (floating-point value able to represent HDR results)*/
TgINLINE TgFLOAT32
tgCM_CL_U32_Brightness_F32(
    TgCOLOUR32_C ARG );

/** @brief Calculate the brightness of the colour (the average of the max and min of the colour values)
    @param [in] ARG 32-bit unsigned integer used to store a hexadecimal colour value
    @return The result of calculating the lightness of the colour */
TgINLINE TgFLOAT32
tgCM_CL_U32_Lightness(
    TgCOLOUR32_C ARG );

/** @brief Calculate the luminance of the colour (NTSC weighted balance of the colour values)
    @param [in] ARG 32-bit unsigned integer used to store a hexadecimal colour value
    @return The result of calculating the luminance of the colour */
TgINLINE TgFLOAT32
tgCM_CL_U32_Luminance(
    TgCOLOUR32_C ARG );


/** @brief Return the red co-ordinate of the colour
    @param [in] ARG 32-bit unsigned integer used to store a hexadecimal colour value
    @return The red co-ordinate of the colour */
TgINLINE TgUINT_E08
tgCM_CL_U32_Query_R_U32(
    TgCOLOUR32_C ARG );

/** @brief Return the green co-ordinate of the colour
    @param [in] ARG 32-bit unsigned integer used to store a hexadecimal colour value
    @return The green co-ordinate of the colour */
TgINLINE TgUINT_E08
tgCM_CL_U32_Query_G_U32(
    TgCOLOUR32_C ARG );

/** @brief Return the blue co-ordinate of the colour
    @param [in] ARG 32-bit unsigned integer used to store a hexadecimal colour value
    @return The blue co-ordinate of the colour */
TgINLINE TgUINT_E08
tgCM_CL_U32_Query_B_U32(
    TgCOLOUR32_C ARG );

/** @brief Return the alpha co-ordinate of the colour
    @param [in] ARG 32-bit unsigned integer used to store a hexadecimal colour value
    @return The alpha co-ordinate of the colour */
TgINLINE TgUINT_E08
tgCM_CL_U32_Query_A_U32(
    TgCOLOUR32_C ARG );


/** @brief Return the red co-ordinate of the colour
    @param [in] ARG 32-bit unsigned integer used to store a hexadecimal colour value
    @return The red co-ordinate of the colour */
TgINLINE TgFLOAT32
tgCM_CL_U32_Query_R_F32(
    TgCOLOUR32_C ARG );

/** @brief Return the green co-ordinate of the colour
    @param [in] ARG 32-bit unsigned integer used to store a hexadecimal colour value
    @return The green co-ordinate of the colour */
TgINLINE TgFLOAT32
tgCM_CL_U32_Query_G_F32(
    TgCOLOUR32_C ARG );

/** @brief Return the blue co-ordinate of the colour
    @param [in] ARG 32-bit unsigned integer used to store a hexadecimal colour value
    @return The blue co-ordinate of the colour */
TgINLINE TgFLOAT32
tgCM_CL_U32_Query_B_F32(
    TgCOLOUR32_C ARG );

/** @brief Return the alpha co-ordinate of the colour
    @param [in] ARG 32-bit unsigned integer used to store a hexadecimal colour value
    @return The alpha co-ordinate of the colour */
TgINLINE TgFLOAT32
tgCM_CL_U32_Query_A_F32(
    TgCOLOUR32_C ARG );

/** @} TGS_COMMON_UTIL_ST_COLOUR_U32 */


/* =============================================================================================================================================================================== */
#endif
