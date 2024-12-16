/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util ST - String.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_SP_STRING_H)
#define TGS_COMMON_UTIL_SP_STRING_H
#pragma once


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_UTIL_ST_STRING String
    @ingroup TGS_COMMON_UTILITY_ST
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

enum { KTgSTRING_STATIC_BUFFER_SIZE             = 16 };

TgTYPE_STRUCT(STg2_UT_ST__ST,)
{
    union
    {
        TgCHAR_U8                                   m_ambBuffer[KTgSTRING_STATIC_BUFFER_SIZE];
        TgCHAR_U8_CP                                m_mbzSrc;
        TgCHAR_U8_P                                 m_mbzDest;
    };
    TgRSIZE                                     m_nbyBuffer;
    TgRSIZE                                     m_nbyReserve;
};
TgCOMPILER_ASSERT( sizeof( STg2_UT_ST__ST ) == 32, 0 );


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/** @addtogroup TGS_COMMON_UTIL_ST_STRING */
/** @{ */

/** @brief Initialize an empty string utility object
    @param [out] OUT Pointer to a string utility object */
TgINLINE TgVOID
tgCM_UT_ST__ST__Init(
    STg2_UT_ST__ST_PC NONULL OUT );

/** @brief Free all resources used by the object and perform some sanity checks
    @param [in,out] ARG Pointer to a string utility object */
TgINLINE TgVOID
tgCM_UT_ST__ST__Free(
    STg2_UT_ST__ST_PC NONULL ARG );


/* -- Init ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Initialize ARG0 with the string starting at ARG1 and until null-termination
    @param [out] OUT0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a null-terminated string */
TgINLINE TgVOID
tgCM_UT_ST__ST__SZ_Init(
    STg2_UT_ST__ST_PC NONULL OUT0, TgCHAR_U8_CPC NONULL ARG1 );

/** @brief Initialize ARG0 with the string starting at ARG1 and a \b byte count of at most ARG2
    @param [out] OUT0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a null-terminated string
    @param [in] ARG2 Maximum number of \b >bytes< to read from ARG1 */
TgINLINE TgVOID
tgCM_UT_ST__ST__SN_Init(
    STg2_UT_ST__ST_PC NONULL OUT0, TgCHAR_U8_CPC NONULL ARG1, TgRSIZE_C ARG2 );

/** @brief Initialize ARG0 with the string in the range of [ARG1,ARG2)
    @param [out] OUT0 Pointer to a string utility object
    @param [in] ARG1 Pointer to the start of a string
    @param [in] ARG2 Pointer to the end of a string */
TgINLINE TgVOID
tgCM_UT_ST__ST__PT_Init(
    STg2_UT_ST__ST_PC NONULL OUT0, TgCHAR_U8_CPC NONULL ARG1, TgCHAR_U8_CPC NONULL ARG2 );

/** @brief Initialize ARG0 with the string utility object at ARG1
    @param [out] OUT0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a string utility object */
TgINLINE TgVOID
tgCM_UT_ST__ST__ST_Init(
    STg2_UT_ST__ST_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1 );

/** @brief Initialize ARG0 with the string utility object at ARG1 with offset ARG2
    @param [out] OUT0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG1 */
TgINLINE TgVOID
tgCM_UT_ST__ST__SO_Init(
    STg2_UT_ST__ST_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2 );

/** @brief Initialize ARG0 with the string utility object at ARG1 with offset ARG2 and maximum length ARG3
    @param [out] OUT0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG1
    @param [in] ARG3 Maximum number of \b >characters< to read from ARG1, starting at ARG2 */
TgINLINE TgVOID
tgCM_UT_ST__ST__SF_Init(
    STg2_UT_ST__ST_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );


/* -- Assign --------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Assign to ARG0 the string starting at ARG1 and until null-termination
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a null-terminated string */
TgINLINE TgVOID
tgCM_UT_ST__ST__SZ_Assign(
    STg2_UT_ST__ST_PC NONULL ARG0, TgCHAR_U8_CPC NONULL ARG1 );

/** @brief Assign to ARG0 the string starting at ARG1 and a byte count of at most ARG2
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a null-terminated string
    @param [in] ARG2 Maximum number of \b >bytes< to read from ARG1 */
TgINLINE TgVOID
tgCM_UT_ST__ST__SN_Assign(
    STg2_UT_ST__ST_PC NONULL ARG0, TgCHAR_U8_CPC NONULL ARG1, TgRSIZE_C ARG2 );

/** @brief Assign to ARG0 the string in the range of [ARG1,ARG2)
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to the start of a string
    @param [in] ARG2 Pointer to the end of a string */
TgINLINE TgVOID
tgCM_UT_ST__ST__PT_Assign(
    STg2_UT_ST__ST_PC NONULL ARG0, TgCHAR_U8_CPC NONULL ARG1, TgCHAR_U8_CPC NONULL ARG2 );

/** @brief Assign to ARG0 the string utility object at ARG1
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a string utility object */
TgINLINE TgVOID
tgCM_UT_ST__ST__ST_Assign(
    STg2_UT_ST__ST_PC NONULL ARG0, STg2_UT_ST__ST_CPC NONULL ARG1 );

/** @brief Assign to ARG0 the string utility object at ARG1 with offset ARG2
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG1 */
TgINLINE TgVOID
tgCM_UT_ST__ST__SO_Assign(
    STg2_UT_ST__ST_PC NONULL ARG0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2 );

/** @brief Assign to ARG0 the string utility object at ARG1 with offset ARG2 and maximum length ARG3
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG1
    @param [in] ARG3 Maximum number of \b >characters< to read from ARG1, starting at ARG2 */
TgEXTN TgVOID
tgCM_UT_ST__ST__SF_Assign(
    STg2_UT_ST__ST_PC NONULL ARG0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );


/* -- Append --------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Append to ARG0 the string starting at ARG1 and until null-termination
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a null-terminated string */
TgINLINE TgVOID
tgCM_UT_ST__ST__SZ_Append(
    STg2_UT_ST__ST_PC NONULL ARG0, TgCHAR_U8_CPC NONULL ARG1 );

/** @brief Append to ARG0 the string starting at ARG1 and a byte count of at most ARG2
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a null-terminated string
    @param [in] ARG2 Maximum number of \b >bytes< to read from ARG1 */
TgINLINE TgVOID
tgCM_UT_ST__ST__SN_Append(
    STg2_UT_ST__ST_PC NONULL ARG0, TgCHAR_U8_CPC NONULL ARG1, TgRSIZE_C ARG2 );

/** @brief Append to ARG0 the string in the range of [ARG1,ARG2)
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to the start of a string
    @param [in] ARG2 Pointer to the end of a string */
TgINLINE TgVOID
tgCM_UT_ST__ST__PT_Append(
    STg2_UT_ST__ST_PC NONULL ARG0, TgCHAR_U8_CPC NONULL ARG1, TgCHAR_U8_CPC NONULL ARG2 );

/** @brief Append to ARG0 the string utility object at ARG1
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a string utility object */
TgINLINE TgVOID
tgCM_UT_ST__ST__ST_Append(
    STg2_UT_ST__ST_PC NONULL ARG0, STg2_UT_ST__ST_CPC NONULL ARG1 );

/** @brief Append to ARG0 the string utility object at ARG1 with offset ARG2
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG1 */
TgINLINE TgVOID
tgCM_UT_ST__ST__SO_Append(
    STg2_UT_ST__ST_PC NONULL ARG0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2 );

/** @brief Append to ARG0 the string utility object at ARG1 with offset ARG2 and maximum length ARG3
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG1
    @param [in] ARG3 Maximum number of \b >characters< to read from ARG1, starting at ARG2 */
TgEXTN TgVOID
tgCM_UT_ST__ST__SF_Append(
    STg2_UT_ST__ST_PC NONULL ARG0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );


/* -- Insert --------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Insert into ARG0 at ARG1 the string starting at ARG2 and until null-termination
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 \b >character< index where to being the insertion
    @param [in] ARG2 Pointer to a null-terminated string */
TgINLINE TgVOID
tgCM_UT_ST__ST__SZ_Insert(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC NONULL ARG2 );

/** @brief Insert into ARG0 at ARG1 the string starting at ARG2 and a byte count of at most ARG3
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 \b >character< index where to being the insertion
    @param [in] ARG2 Pointer to a null-terminated string
    @param [in] ARG3 Maximum number of \b >bytes< to read from ARG1 */
TgINLINE TgVOID
tgCM_UT_ST__ST__SN_Insert(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC NONULL ARG2, TgRSIZE_C ARG3 );

/** @brief Insert into ARG0 at ARG1 the string in the range of [ARG2,ARG3)
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 \b >character< index where to being the insertion
    @param [in] ARG2 Pointer to the start of a string
    @param [in] ARG3 Pointer to the end of a string */
TgINLINE TgVOID
tgCM_UT_ST__ST__PT_Insert(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC NONULL ARG2, TgCHAR_U8_CPC NONULL ARG3 );

/** @brief Insert into ARG0 at ARG1 the string utility object at ARG2
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 \b >character< index where to being the insertion
    @param [in] ARG2 Pointer to a string utility object */
TgINLINE TgVOID
tgCM_UT_ST__ST__ST_Insert(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, STg2_UT_ST__ST_CPC NONULL ARG2 );

/** @brief Insert into ARG0 at ARG1 the string utility object at ARG2 with offset ARG3
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 \b >character< index where to being the insertion
    @param [in] ARG2 Pointer to a string utility object
    @param [in] ARG3 Starting offset in \b >characters< for ARG2 */
TgINLINE TgVOID
tgCM_UT_ST__ST__SO_Insert(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, STg2_UT_ST__ST_CPC NONULL ARG2, TgRSIZE_C ARG3 );

/** @brief Insert into ARG0 at ARG1 the string utility object at ARG2 with offset ARG3 and maximum length ARG4
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 \b >character< index where to being the insertion
    @param [in] ARG2 Pointer to a string utility object
    @param [in] ARG3 Starting offset in \b >characters< for ARG2
    @param [in] ARG4 Maximum number of \b >characters< to read from ARG2, starting at ARG3 */
TgINLINE TgVOID
tgCM_UT_ST__ST__SF_Insert(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, STg2_UT_ST__ST_CPC NONULL ARG2, TgRSIZE_C ARG3, TgRSIZE_C ARG4 );


/* -- Replace -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Replace [ARG1,ARG2) in ARG0 with the string starting at ARG3 and until null-termination
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 \b >character< index where to being the replacement [ARG1,ARG2)
    @param [in] ARG2 \b >character< index where to end the replacement [ARG1,ARG2)
    @param [in] ARG3 Pointer to a null-terminated string */
TgINLINE TgVOID
tgCM_UT_ST__ST__SZ_Replace( 
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3 );

/** @brief Replace [ARG1,ARG2) in ARG0 with the string starting at ARG3 and a byte count of at most ARG4
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 \b >character< index where to being the replacement [ARG1,ARG2)
    @param [in] ARG2 \b >character< index where to end the replacement [ARG1,ARG2)
    @param [in] ARG3 Pointer to a null-terminated string
    @param [in] ARG4 Maximum number of \b >bytes< to read from ARG1 */
TgINLINE TgVOID
tgCM_UT_ST__ST__SN_Replace(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3, TgRSIZE_C ARG4 );

/** @brief Replace [ARG1,ARG2) in ARG0 with the string in the range of [ARG3,ARG4)
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 \b >character< index where to being the replacement [ARG1,ARG2)
    @param [in] ARG2 \b >character< index where to end the replacement [ARG1,ARG2)
    @param [in] ARG3 Pointer to the start of a string
    @param [in] ARG4 Pointer to the end of a string */
TgINLINE TgVOID
tgCM_UT_ST__ST__PT_Replace(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3, TgCHAR_U8_CPC NONULL ARG4 );

/** @brief Replace [ARG1,ARG2) in ARG0 with the string utility object at ARG3
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 \b >character< index where to being the replacement [ARG1,ARG2)
    @param [in] ARG2 \b >character< index where to end the replacement [ARG1,ARG2)
    @param [in] ARG3 Pointer to a string utility object */
TgINLINE TgVOID
tgCM_UT_ST__ST__ST_Replace(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, STg2_UT_ST__ST_CPC NONULL ARG3 );

/** @brief Replace [ARG1,ARG2) in ARG0 with the string utility object at ARG3 with offset ARG4
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 \b >character< index where to being the replacement [ARG1,ARG2)
    @param [in] ARG2 \b >character< index where to end the replacement [ARG1,ARG2)
    @param [in] ARG3 Pointer to a string utility object
    @param [in] ARG4 Starting offset in \b >characters< for ARG3 */
TgINLINE TgVOID
tgCM_UT_ST__ST__SO_Replace(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, STg2_UT_ST__ST_CPC NONULL ARG3, TgRSIZE_C ARG4 );

/** @brief Replace [ARG1,ARG2) in ARG0 with the string utility object at ARG3 with offset ARG4 and maximum length ARG5
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 \b >character< index where to being the replacement [ARG1,ARG2)
    @param [in] ARG2 \b >character< index where to end the replacement [ARG1,ARG2)
    @param [in] ARG3 Pointer to a string utility object
    @param [in] ARG4 Starting offset in \b >characters< for ARG3
    @param [in] ARG5 Maximum number of \b >characters< to read from ARG3, starting at ARG4 */
TgEXTN TgVOID
tgCM_UT_ST__ST__SF_Replace(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, STg2_UT_ST__ST_CPC NONULL ARG3, TgRSIZE_C ARG4, TgRSIZE_C ARG5 );


/* -- Miscellaneous -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Erase the characters from offset ARG1 in ARG0 for ARG2 characters
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Starting offset in \b >characters< for ARG0
    @param [in] ARG2 Number of \b >characters< to be erased  */
TgEXTN TgVOID
tgCM_UT_ST__ST__Erase(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2 );

/** @brief Erase the characters from offset ARG1 in ARG0 for ARG2 characters
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Starting offset in \b >characters< for ARG0
    @param [in] ARG2 Number of \b >bytes< to be erased  */
TgEXTN TgVOID
tgCM_UT_ST__ST__Erase_U08(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2 );

/** @brief Clear all the characters from the string utility object and release any allocated memory
    @param [in,out] ARG0 Pointer to a string utility object */
TgINLINE TgVOID
tgCM_UT_ST__ST__Clear(
    STg2_UT_ST__ST_PC NONULL ARG0 );

/** @brief Convert the string contained at ARG0 to upper case
    @param [in,out] ARG0 Pointer to a string utility object */
TgINLINE TgRESULT
tgCM_UT_ST__ST__To_Upper(
    STg2_UT_ST__ST_PC NONULL ARG0 );

/** @brief Convert the string contained at ARG0 to lower case
    @param [in,out] ARG0 Pointer to a string utility object */
TgINLINE TgRESULT
tgCM_UT_ST__ST__To_Lower(
    STg2_UT_ST__ST_PC NONULL ARG0 );

/** @brief Store the results of printf processing of the arguments
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a printf string literal
    @param [in] ... printf variables */
TgEXTN TgVOID
tgCM_UT_ST__ST__Format(
    STg2_UT_ST__ST_PC NONULL ARG0, TgCHAR_U8_CPC NONULL ARG1, ... );

/** @brief Return the start of the string data in the object
    @param [in] ARG0 Pointer to a string utility object */
TgINLINE TgCHAR_U8_CP
tgCM_UT_ST__ST__Query_String(
    STg2_UT_ST__ST_CPC NONULL ARG0 );

/** @brief Return the result of an empty test on the string
    @param [in] ARG0 Pointer to a string utility object */
TgINLINE TgBOOL
tgCM_UT_ST__ST__Is_Empty(
    STg2_UT_ST__ST_CPC NONULL ARG0 );

/** @brief Return the total current capacity in \b >bytes< of the string object
    @param [in] ARG0 Pointer to a string utility object */
TgINLINE TgRSIZE
tgCM_UT_ST__ST__Capacity(
    STg2_UT_ST__ST_CPC NONULL ARG0 );

/** @brief Return the maximum possible size in \b >bytes< for the string object
    @param [in] ARG0 Pointer to a string utility object */
TgINLINE TgRSIZE
tgCM_UT_ST__ST__Max_Size(
    STg2_UT_ST__ST_CPC NONULL ARG0 );

/** @brief Return the current number of \b >bytes< consumed by the string, not including the null terminator
    @param [in] ARG0 Pointer to a string utility object */
TgINLINE TgRSIZE
tgCM_UT_ST__ST__Length_U08(
    STg2_UT_ST__ST_CPC NONULL ARG0 );

/** @brief Return the number of \b >characters< in the string, not including the null terminator
    @param [out] OUT0 Pointer to hold the result of the function on success
    @param [in] ARG1 Pointer to a string utility object */
TgINLINE TgRESULT
tgCM_UT_ST__ST__Length_Count(
    TgRSIZE_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1 );

/** @brief Resize the string utility object, filling it out with the character ARG2
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Number of \b >character< to be stored in the string
    @param [in] ARG2 Pointer to a narrow character value */
TgEXTN TgVOID
tgCM_UT_ST__ST__Resize_NCS(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1, TgCHAR_NC_C ARG2 );

/** @brief Establishes the amount of memory to reserve for the string utility object (capacity)
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Number of \b >bytes< to reserve */
TgINLINE TgVOID
tgCM_UT_ST__ST__Reserve(
    STg2_UT_ST__ST_PC NONULL ARG0, TgRSIZE_C ARG1 );

/** @brief Swap the data contained between the two string utility objects
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in,out] ARG1 Pointer to a string utility object */
TgINLINE TgVOID
tgCM_UT_ST__ST__Swap(
    STg2_UT_ST__ST_PC NONULL ARG0, STg2_UT_ST__ST_PC NONULL ARG1 );

/** @brief Return true if ARG1 in inside the owned range of the string utility object
    @param [in] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to null-terminated string */
TgINLINE TgBOOL
tgCM_UT_ST__ST__Is_Inside(
    STg2_UT_ST__ST_CPC NONULL ARG0, TgCHAR_U8_CPC NONULL ARG1 );


/* -- Compare -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Lexicographical comparison between ARG0 [0, \0) and ARG1 [0, \0)
    @param [out] OUT0 Holds a value that is negative if ARG0 is less than ARG1, zero if they are identical, and positive otherwise
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Pointer to a null-terminated string
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__ST_SZ_Compare(
    TgSINT_F08_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgCHAR_U8_CPC NONULL ARG2 );

/** @brief Lexicographical comparison between ARG0 [ARG1, ARG1 + ARG2) and ARG3 [0, ARG4)
    @param [out] OUT0 Holds a value that is negative if ARG0 is less than ARG1, zero if they are identical, and positive otherwise
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Pointer to a null-terminated string
    @param [in] ARG3 Maximum number of \b >bytes< to read from ARG2
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__ST_SN_Compare(
    TgSINT_F08_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgCHAR_U8_CPC NONULL ARG2, TgRSIZE_C ARG3 );

/** @brief Lexicographical comparison between ARG0 [0, \0) and ARG1 [0, \0)
    @param [out] OUT0 Holds a value that is negative if ARG0 is less than ARG1, zero if they are identical, and positive otherwise
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Pointer to a string utility object
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__ST_ST_Compare(
    TgSINT_F08_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, STg2_UT_ST__ST_CPC NONULL ARG2 );

/** @brief Lexicographical comparison between ARG0 [ARG1, ARG1 + ARG2) and ARG3 [ARG4, ARG4 + ARG5)
    @param [out] OUT0 Holds a value that is negative if ARG0 is less than ARG1, zero if they are identical, and positive otherwise
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Pointer to a string utility object
    @param [in] ARG3 Starting offset in \b >characters< for ARG2
    @param [in] ARG4 Maximum number of \b >characters< to read from ARG2, starting at ARG3
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__ST_SF_Compare(
    TgSINT_F08_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, STg2_UT_ST__ST_CPC NONULL ARG2, TgRSIZE_C ARG3, TgRSIZE_C ARG4 );

/** @brief Lexicographical comparison between ARG0 [ARG1, ARG1 + ARG2) and ARG3 [0, \0)
    @param [out] OUT0 Holds a value that is negative if ARG0 is less than ARG1, zero if they are identical, and positive otherwise
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG1
    @param [in] ARG3 Maximum number of \b >characters< to read from ARG1, starting at ARG2
    @param [in] ARG4 Pointer to a null-terminated string
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SF_SZ_Compare(
    TgSINT_F08_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, TgCHAR_U8_CPC NONULL ARG4 );

/** @brief Lexicographical comparison between ARG0 [ARG1, ARG1 + ARG2) and ARG3 [0, ARG4)
    @param [out] OUT0 Holds a value that is negative if ARG0 is less than ARG1, zero if they are identical, and positive otherwise
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG1
    @param [in] ARG3 Maximum number of \b >characters< to read from ARG1, starting at ARG2
    @param [in] ARG4 Pointer to a null-terminated string
    @param [in] ARG5 Maximum number of \b >bytes< to read from ARG4
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SF_SN_Compare(
    TgSINT_F08_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, TgCHAR_U8_CPC NONULL ARG4, TgRSIZE_C ARG5 );

/** @brief Lexicographical comparison between ARG0 [ARG1, ARG1 + ARG2) and ARG3 [0, \0)
    @param [out] OUT0 Holds a value that is negative if ARG0 is less than ARG1, zero if they are identical, and positive otherwise
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG1
    @param [in] ARG3 Maximum number of \b >characters< to read from ARG1, starting at ARG2
    @param [in] ARG4 Pointer to a string utility object
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SF_ST_Compare(
    TgSINT_F08_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, STg2_UT_ST__ST_CPC NONULL ARG4 );

/** @brief Lexicographical comparison between ARG0 [ARG1, ARG1 + ARG2) and ARG3 [ARG4, ARG4 + ARG5)
    @param [out] OUT0 Holds a value that is negative if ARG0 is less than ARG1, zero if they are identical, and positive otherwise
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG1
    @param [in] ARG3 Maximum number of \b >characters< to read from ARG1 and ARG4, starting at ARG2 and ARG5
    @param [in] ARG4 Pointer to a string utility object
    @param [in] ARG5 Starting offset in \b >characters< for ARG4
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SF_SF_Compare(
    TgSINT_F08_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, STg2_UT_ST__ST_CPC NONULL ARG4 , TgRSIZE_C ARG5 );


/* -- Find ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Find the string ARG2 [0, \0) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a null-terminated string
    @return The offset of the found string and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SZ_Find_String(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3 );

/** @brief Find the string ARG2 [0, ARG3) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a null-terminated string
    @param [in] ARG4 Maximum number of \b >bytes< to read from ARG3
    @return The offset of the found string and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SN_Find_String(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3, TgRSIZE_C ARG4 );

/** @brief Find the string ARG2 [0, \0) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a string utility object
    @return The offset of the found string and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_ST_Find_String(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, STg2_UT_ST__ST_CPC NONULL ARG3 );

/** @brief Find the string ARG2 [ARG3, ARG4) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a string utility object
    @param [in] ARG4 Starting offset in \b >characters< for ARG2
    @param [in] ARG5 Maximum number of \b >characters< to read from ARG3, starting at ARG4
    @return The offset of the found string and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SF_Find_String(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, STg2_UT_ST__ST_CPC NONULL ARG3, TgRSIZE_C ARG4, TgRSIZE_C ARG5 );


/* -- Find Set ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Find one of the characters in ARG2 [0, \0) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a null-terminated string
    @return The offset of the found character and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SZ_Find_Set(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3 );

/** @brief Find one of the characters in ARG2 [0, ARG3) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a null-terminated string
    @param [in] ARG4 Maximum number of \b >bytes< to read from ARG3
    @return The offset of the found character and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SN_Find_Set(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3, TgRSIZE_C ARG4 );

/** @brief Find one of the characters in ARG2 [0, \0) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a string utility object
    @return The offset of the found character and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_ST_Find_Set(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, STg2_UT_ST__ST_CPC NONULL ARG3 );

/** @brief Find a character not in ARG2 [0, \0) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a null-terminated string
    @return The offset of the found character and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SZ_Find_Not_Set(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3 );

/** @brief Find a character not in ARG2 [0, ARG3) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a null-terminated string
    @param [in] ARG4 Maximum number of \b >bytes< to read from ARG3
    @return The offset of the found character and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SN_Find_Not_Set(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3, TgRSIZE_C ARG4 );

/** @brief Find a character not in ARG2 [0, \0) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a string utility object
    @return The offset of the found character and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_ST_Find_Not_Set(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, STg2_UT_ST__ST_CPC NONULL ARG3 );


/* -- RFind ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Find the string ARG2 [0, \0) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a null-terminated string
    @return The offset of the found string and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SZ_RFind_String(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3 );

/** @brief Find the string ARG2 [0, ARG3) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a null-terminated string
    @param [in] ARG4 Maximum number of \b >bytes< to read from ARG3
    @return The offset of the found string and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SN_RFind_String(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3, TgRSIZE_C ARG4 );

/** @brief Find the string ARG2 [0, \0) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a string utility object
    @return The offset of the found string and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_ST_RFind_String(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, STg2_UT_ST__ST_CPC NONULL ARG3 );

/** @brief Find the string ARG2 [ARG3, ARG4) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a string utility object
    @param [in] ARG4 Starting offset in \b >characters< for ARG3
    @param [in] ARG5 Maximum number of \b >bytes< to read from ARG3, starting at ARG4
    @return The offset of the found string and KTgMAX_RSIZE otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SF_RFind_String(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, STg2_UT_ST__ST_CPC NONULL ARG3, TgRSIZE_C ARG4, TgRSIZE_C ARG5 );


/* -- RFind Set ------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

/** @brief Find one of the characters in ARG2 [0, \0) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a string utility object
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SZ_RFind_Set(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3 );

/** @brief Find one of the characters in ARG2 [0, ARG3) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a null-terminated string
    @param [in] ARG4 Maximum number of \b >bytes< to read from ARG3
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SN_RFind_Set(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3, TgRSIZE_C ARG4 );

/** @brief Find one of the characters in ARG2 [0, \0) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a string utility object
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_ST_RFind_Set(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, STg2_UT_ST__ST_CPC NONULL ARG3 );

/** @brief Find a character not in ARG2 [0, \0) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a string utility object
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SZ_RFind_Not_Set(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3 );

/** @brief Find a character not in ARG2 [0, ARG3) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a null-terminated string
    @param [in] ARG4 Maximum number of \b >bytes< to read from ARG3
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_SN_RFind_Not_Set(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, TgCHAR_U8_CPC NONULL ARG3, TgRSIZE_C ARG4 );

/** @brief Find a character not in ARG2 [0, \0) in ARG0 [ARG1, \0)
    @param [out] OUT0 Destination structure that will hold the offset location in bytes and characters on success
    @param [in] ARG1 Pointer to a string utility object
    @param [in] ARG2 Starting offset in \b >characters< for ARG0
    @param [in] ARG3 Pointer to a string utility object
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__ST__SO_ST_RFind_Not_Set(
    STg1_Text_Length_PC NONULL OUT0, STg2_UT_ST__ST_CPC NONULL ARG1, TgRSIZE_C ARG2, STg2_UT_ST__ST_CPC NONULL ARG3 );


/* -- Trim ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Remove all instances of the characters at ARG1 from the start of the string
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a null-terminated string
    @param [in] ARG2 Maximum number of \b >characters< in ARG1 for processing */
TgINLINE TgVOID
tgCM_UT_ST__ST__Trim_Start_Set(
    STg2_UT_ST__ST_PC NONULL ARG0, TgCHAR_U8_CPC NONULL ARG1, TgRSIZE_C ARG2 );

/** @brief Remove all instances of the characters at ARG1 from the end of the string
    @param [in,out] ARG0 Pointer to a string utility object
    @param [in] ARG1 Pointer to a null-terminated string
    @param [in] ARG2 Maximum number of \b >characters< in ARG1 for processing */
TgINLINE TgVOID
tgCM_UT_ST__ST__Trim_End_Set(
    STg2_UT_ST__ST_PC NONULL ARG0, TgCHAR_U8_CPC NONULL ARG1, TgRSIZE_C ARG2 );

/** @} TGS_COMMON_UTIL_ST_STRING */


/* =============================================================================================================================================================================== */
#endif
