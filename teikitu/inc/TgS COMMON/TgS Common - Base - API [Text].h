/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - API [Text].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_API_TEXT_H)

#if !defined(TGS_COMMON_BASE_API_TEXT_H__ONCE)
#define TGS_COMMON_BASE_API_TEXT_H__ONCE


/* == Common ===================================================================================================================================================================== */

/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_BASE_API_TEXT Text Functions
    @ingroup TGS_COMMON_BASE
    @details String - Traditional "C" style strings which are assumed to be encoded as either ASCII or in a wide character format. These are all assumed to be null-terminated
    without any bounds or error checking. (There is no way to validate the capacity or size of the memory allocated to the string.) The functionality is included primarily for
    backwards compatibility and for simple non-user interactions. It is heavily encouraged to use the text objects in all cases, and to provide full support for unicode encoding
    everywhere.
    @details Text - Multibyte text support - generally assumed to be UTF8, UTF16 or UTF32. However, the text object can store any text encoding that matches a "C" standard locale.
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Used to describe both the character count and byte size of a string */
TgTYPE_STRUCT(STg1_Text_Length,)
{
    TgRSIZE                                     m_nuiCharacters;
    TgRSIZE                                     m_nbyCharacters;
};


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/** @addtogroup TGS_COMMON_BASE_API_TEXT */
/** @{ */

/** @brief Set the "C" runtime locale */
TgEXTN TgVOID
tgTXT_Set_Local_Global(
    TgCHAR_NC_CP ARG0 );

/** @brief Return a pointer to the location in the string where the ARG1 character begins
    @param [in] ARG0 String to be processed
    @param [in] ARG1 Maximum size in \b >bytes< of the string in ARG0
    @param [in] ARG2 Offset into the string as a count of \b >characters<
    @return Location in the array of the select character */
TgEXTN TgCHAR_U8_CP
tgUSZ_Query_At(
    TgCHAR_U8_CPU ARG0, TgRSIZE ARG1, TgRSIZE ARG2 );

/** @brief Return a pointer to the location in the string where the ARG1 character begins
    @param [in] ARG0 String to be processed
    @param [in] ARG1 Maximum size in \b >bytes< of the string in ARG0
    @param [in] ARG2 Offset into the string as a count of \b >characters<
    @return Location in the array of the select character */
TgINLINE TgCHAR_U8_P
tgUSZ_Get_At(
    TgCHAR_U8_PU ARG0, TgRSIZE ARG1, TgRSIZE ARG2 );

/** @brief Return a pointer to the last character in the string at ARG
    @param [in] ARG0 String to be processed
    @param [in] ARG1 Maximum size in \b >bytes< of the string in ARG0
    @param [in] ARG2 Maximum number of \b >characters< to read 
    @return Location in the array of the last character, or nullptr if string is empty */
TgEXTN TgCHAR_U8_CP
tgUSZ_Query_Last(
    TgCHAR_U8_CPU ARG0, TgRSIZE ARG1, TgRSIZE ARG2 );

/** @brief Return a pointer to the last character in the string at ARG
    @param [in] ARG0 String to be processed
    @param [in] ARG1 Maximum size in \b >bytes< of the string in ARG0
    @param [in] ARG2 Maximum number of \b >characters< to read 
    @return Location in the array of the last character, or nullptr if string is empty */
TgINLINE TgCHAR_U8_P
tgUSZ_Get_Last(
    TgCHAR_U8_PU ARG0, TgRSIZE ARG1, TgRSIZE ARG2 );

/** @brief Return a pointer to the null terminator in the string at ARG
    @param [in] ARG0 String to be processed
    @param [in] ARG1 Maximum size in \b >bytes< of the string in ARG0
    @param [in] ARG2 Maximum number of \b >characters< to read 
    @return Location in the array of the null terminator */
TgEXTN TgCHAR_U8_CP
tgUSZ_Query_End(
    TgCHAR_U8_CPU ARG0, TgRSIZE ARG1, TgRSIZE ARG2 );

/** @brief Return a pointer to the null terminator in the string at ARG
    @param [in] ARG0 String to be processed
    @param [in] ARG1 Maximum size in \b >bytes< of the string in ARG0
    @param [in] ARG2 Maximum number of \b >characters< to read 
    @return Location in the array of the null terminator */
TgINLINE TgCHAR_U8_P
tgUSZ_Get_End(
    TgCHAR_U8_PU ARG0, TgRSIZE ARG1, TgRSIZE ARG2 );

/** @brief Output the begin and end pointers for a string region
    @param [in] ARG0 Pointer to a string location
    @param [in] ARG1 Pointer to a string location
    @param [in] ARG2 String to be processed
    @param [in] ARG3 Maximum size in \b >bytes< of the string in ARG2
    @param [in] ARG4 Offset into the string as a count of \b characters
    @param [in] ARG5 Maximum number of \b >characters< to be contained in the region
    @return Location in the array of the null terminator */
TgINLINE TgRESULT
tgUSZ_Query_Region(
    TgCHAR_U8_CPP ARG0, TgCHAR_U8_CPP ARG1, TgCHAR_U8_CP ARG2, TgRSIZE ARG3, TgRSIZE ARG4, TgRSIZE ARG5 );

/** @brief Output the begin and end pointers for a string region
    @param [in] ARG0 Pointer to a string location
    @param [in] ARG1 Pointer to a string location
    @param [in] ARG2 String to be processed
    @param [in] ARG3 Maximum size in \b >bytes< of the string in ARG2
    @param [in] ARG4 Offset into the string as a count of \b characters
    @param [in] ARG5 Maximum number of \b >characters< to be contained in the region
    @return Location in the array of the null terminator */
TgINLINE TgRESULT
tgUSZ_Get_Region(
    TgCHAR_U8_PP ARG0, TgCHAR_U8_PP ARG1, TgCHAR_U8_P ARG2, TgRSIZE ARG3, TgRSIZE ARG4, TgRSIZE ARG5 );

/** @brief Determine the number bytes needed to convert the string to upper case
    @param [in] ARG0 Source string for processing
    @param [in] ARG1 Maximum capacity of the string in ARG2
    @return Number of bytes needed for the conversion on success or KTgMAX_RSIZE otherwise */
TgEXTN TgRSIZE
tgUSZ_To_Upper_Length_U08( 
    TgCHAR_U8_CP ARG0, TgRSIZE ARG1 );

/** @brief Determine the number bytes needed to convert the string to lower case
    @param [in] ARG0 Source string for processing
    @param [in] ARG1 Maximum capacity of the string in ARG2
    @return Number of bytes needed for the conversion on success or KTgMAX_RSIZE otherwise */
TgEXTN TgRSIZE
tgUSZ_To_Lower_Length_U08(
    TgCHAR_U8_CP ARG0, TgRSIZE ARG1 );

/** @} */


/*# !defined(TGS_COMMON_BASE_API_TEXT_H__ONCE) */
#endif




#if defined(TEMPLATE_TYPE_EXPANSION__RELOAD)

/* == Common ===================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Text].h_inc"


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */


/* ---- Character ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Test to see if a character is considered to be in the set of a printable characters
    @param [in] ARG Character to be processed
    @return True if the character is considered to be part of the functions criteria, and false otherwise */
TgEXTN TgBOOL
FCN_CHAR(Is_Print)(
    CHAR(CP) NONULL ARG );

/** @brief Test to see if a character is considered to be in the set white space*/
/** @param [in] ARG Character to be processed
    @return True if the character is considered to be part of the functions criteria, and false otherwise */
TgEXTN TgBOOL
FCN_CHAR(Is_Space)(
    CHAR(CP) NONULL ARG );

/** @brief Convert a string to lower case
    @param [out] OUT0 Output location for the converted string (assumed to be large enough for the operation)
    @param [in] ARG1 String to be processed */
TgEXTN TgVOID
FCN_CHAR(To_Lower)(
    CHAR(P) NONULL OUT0, CHAR(CP) NONULL ARG1 );

/** @brief Convert a string to upper case
    @param [out] OUT0 Output location for the converted string (assumed to be large enough for the operation)
    @param [in] ARG1 String to be processed */
TgEXTN TgVOID
FCN_CHAR(To_Upper)(
    CHAR(P) NONULL OUT0, CHAR(CP) NONULL ARG1 );


/* ---- String ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Generate a consistent hash for the string in ARG0
    @param [out] OUT0 Destination pointer to hold the hash value on success
    @param [in] ARG1 String to be processed
    @param [in] ARG2 Maximum capacity in \b bytes of the string in ARG0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(Hash)(
    TgUINT_MAX_P NONULL OUT0, CHAR(CPC) NONULL ARG1, TgRSIZE_C ARG2 );

/** @brief Output a string representation of the value in ARG2
    @param [out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Numeric value to be converted
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(From_U08)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgUINT_F08_C ARG2 );

/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(From_U16)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgUINT_F16_C ARG2 );

/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(From_U32)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgUINT_F32_C ARG2 );

/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(From_U64)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgUINT_F64_C ARG2 );

/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(From_S08)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgSINT_F08_C ARG2 );

/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(From_S16)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgSINT_F16_C ARG2 );

/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(From_S32)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgSINT_F32_C ARG2 );

/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(From_S64)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgSINT_F64_C ARG2 );


/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(From_F32)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgFLOAT32_C ARG2 );

/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(From_F64)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgFLOAT64_C ARG2 );


/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(Formatted_From_U32)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgUINT_F32_C ARG2 );

/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(Formatted_From_U64)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgUINT_F64_C ARG2 );

/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(Formatted_From_S32)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgSINT_F32_C ARG2 );

/** @copydoc tgUSZ_From_U08 */
TgEXTN TgRESULT
FCN(Formatted_From_S64)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgSINT_F64_C ARG2 );


/** @brief Convert a string representation of a number into its numeric value
    @param [in] ARG0 String containing the number to be converted
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgBOOL
FCN(To_Bool)(
    CHAR(CPC) NONULL ARG0, TgRSIZE_C ARG1 );

/** @copydoc tgUSZ_To_Bool */
TgINLINE TgUINT_F08
FCN(To_U08)(
    CHAR(CPC) NONULL ARG0, TgRSIZE_C ARG1 );

/** @copydoc tgUSZ_To_Bool */
TgINLINE TgUINT_F16
FCN(To_U16)(
    CHAR(CPC) NONULL ARG0, TgRSIZE_C ARG1 );

/** @copydoc tgUSZ_To_Bool */
TgEXTN TgUINT_F32
FCN(To_U32)(
    CHAR(CPC) NONULL ARG0, TgRSIZE_C ARG1 );

/** @copydoc tgUSZ_To_Bool */
TgEXTN TgUINT_F64
FCN(To_U64)(
    CHAR(CPC) NONULL ARG0, TgRSIZE_C ARG1 );

/** @copydoc tgUSZ_To_Bool */
TgINLINE TgSINT_F08
FCN(To_S08)(
    CHAR(CPC) NONULL ARG0, TgRSIZE_C ARG1 );

/** @copydoc tgUSZ_To_Bool */
TgINLINE TgSINT_F16
FCN(To_S16)(
    CHAR(CPC) NONULL ARG0, TgRSIZE_C ARG1 );

/** @copydoc tgUSZ_To_Bool */
TgEXTN TgSINT_F32
FCN(To_S32)(
    CHAR(CPC) NONULL ARG0, TgRSIZE_C ARG1 );

/** @copydoc tgUSZ_To_Bool */
TgEXTN TgSINT_F64
FCN(To_S64)(
    CHAR(CPC) NONULL ARG0, TgRSIZE_C ARG1 );


/** @copydoc tgUSZ_To_Bool */
TgEXTN TgFLOAT32
FCN(To_F32)(
    CHAR(CPC) NONULL ARG0, TgRSIZE_C ARG1 );

/** @copydoc tgUSZ_To_Bool */
TgEXTN TgFLOAT64
FCN(To_F64)(
    CHAR(CPC) NONULL ARG0, TgRSIZE_C ARG1 );


/** @brief Output the number of characters in the string at ARG0
    @param [out] OUT0 Destination for function result on success, the number of characters in the string at ARG0
    @param [in] ARG1 String to be processed
    @param [in] ARG2 Maximum capacity in \b bytes of the string in ARG1
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(Length_Count)(
    TgRSIZE_P NONULL OUT0, CHAR(CP) NONULL ARG1, TgRSIZE ARG2 );

/** @return The number of bytes in the string at ARG0
    @param [in] ARG0 String to be processed
    @param [in] ARG1 Maximum capacity in \b bytes of the string in ARG0 */
TgEXTN TgRSIZE
FCN(Length_U08)(
    CHAR(CPC) NONULL ARG0, TgRSIZE_C ARG1 );

/** @brief Output the number of bytes and the count of characters in the string at ARG0
    @param [out] OUT0 Destination structure that holds both the count of characters and size in bytes
    @param [in] ARG1 String to be processed
    @param [in] ARG2 Maximum capacity in \b bytes of the string in ARG1
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(Length)(
    STg1_Text_Length_P NONULL OUT0, CHAR(CP) NONULL ARG1, TgRSIZE ARG2 );



/** Comparison Table                Function Result                 Lexical Result
            As          Aster       Zero                            Negative (Aster is longer)
            Apple       apple       Negative Result (A < a)         Negative                        */

/** @brief Perform a lexicographical comparison of two strings up to the minimum of ARG3 and ARG6
    @param [out] OUT0 Negative if ARG0 appears before ARG2 in lexicographical order, zero if they compare equal, and negative otherwise
    @param [in] ARG1 String parameter
    @param [in] ARG2 Maximum number of \b >bytes< to read from ARG1, including the data leading to ARG3
    @param [in] ARG3 Starting offset in \b >characters< for ARG1
    @param [in] ARG4 String parameter
    @param [in] ARG5 Maximum number of \b >bytes< to read from ARG5, including the data leading to ARG6
    @param [in] ARG6 Starting offset in \b >characters< for ARG5
    @return KTgS_OK on success and KTgE_FAIL or other error code otherwise */
TgINLINE TgRESULT
FCN(Compare)(
    TgSINT_F08_P NONULL OUT0, CHAR(CPC) NONULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, CHAR(CPC) NONULL ARG4, TgRSIZE_C ARG5, TgRSIZE_C ARG6 );

/** @brief Perform a case insensitive lexicographical comparison of two strings up to the minimum of ARG3 and ARG6
    @param [out] OUT0 Negative if ARG0 appears before ARG2 in lexicographical order, zero if they compare equal, and negative otherwise
    @param [in] ARG1 String parameter
    @param [in] ARG2 Maximum number of \b >bytes< to read from ARG1, including the data leading to ARG3
    @param [in] ARG3 Starting offset in \b >characters< for ARG1
    @param [in] ARG4 String parameter
    @param [in] ARG5 Maximum number of \b >bytes< to read from ARG5, including the data leading to ARG6
    @param [in] ARG6 Starting offset in \b >characters< for ARG5
    @return KTgS_OK on success and KTgE_FAIL or other error code otherwise */
TgINLINE TgRESULT
FCN(Compare_NoCase)(
    TgSINT_F08_P NONULL OUT0, CHAR(CPC) NONULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, CHAR(CPC) NONULL ARG4, TgRSIZE_C ARG5, TgRSIZE_C ARG6 );

/** @brief Perform a lexicographical comparison of two strings up to ARG5 number of bytes
    @param [out] OUT0 Negative if ARG0 appears before ARG2 in lexicographical order, zero if they compare equal, and negative otherwise
    @param [in] ARG1 String parameter
    @param [in] ARG2 Maximum number of \b >bytes< to read from ARG1, including the data leading to ARG3
    @param [in] ARG3 Starting offset in \b >characters< for ARG1
    @param [in] ARG4 String parameter
    @param [in] ARG5 Maximum number of \b >bytes< to read from ARG5, including the data leading to ARG6
    @param [in] ARG6 Starting offset in \b >characters< for ARG5
    @param [in] ARG7 Maximum number of \b >characters< to read from ARG1 and ARG3, starting from ARG2 and ARG4
    @return KTgS_OK on success and KTgE_FAIL or other error code otherwise */
TgINLINE TgRESULT
FCN(CompareN)(
    TgSINT_F08_P NONULL OUT0, CHAR(CPC) NONULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, CHAR(CPC) NONULL ARG4, TgRSIZE_C ARG5, TgRSIZE_C ARG6, TgRSIZE_C ARG7 );

/** @brief Perform a case insensitive lexicographical comparison of two strings up to ARG5 number of bytes
    @param [out] OUT0 Negative if ARG0 appears before ARG2 in lexicographical order, zero if they compare equal, and negative otherwise
    @param [in] ARG1 String parameter
    @param [in] ARG2 Maximum number of \b >bytes< to read from ARG1, including the data leading to ARG3
    @param [in] ARG3 Starting offset in \b >characters< for ARG1
    @param [in] ARG4 String parameter
    @param [in] ARG5 Maximum number of \b >bytes< to read from ARG5, including the data leading to ARG6
    @param [in] ARG6 Starting offset in \b >characters< for ARG5
    @param [in] ARG7 Maximum number of \b >characters< to read from ARG1 and ARG3, starting from ARG2 and ARG4
    @return KTgS_OK on success and KTgE_FAIL or other error code otherwise */
TgINLINE TgRESULT
FCN(CompareN_NoCase)(
    TgSINT_F08_P NONULL OUT0, CHAR(CPC) NONULL ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, CHAR(CPC) NONULL ARG4, TgRSIZE_C ARG5, TgRSIZE_C ARG6, TgRSIZE_C ARG7 );



/** @brief Convert the string in ARG2 to upper case and outputs it into ARG0
    @param [out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string for processing
    @param [in] ARG3 Maximum capacity in \b bytes of the string in ARG2
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(To_Upper)(
    CHAR(P) NONULL OUT0, TgRSIZE ARG1, CHAR(CP) NONULL ARG2, TgRSIZE ARG3 );

/** @brief Convert the string in ARG2 to lower case and outputs it into ARG0
    @param [out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string for processing
    @param [in] ARG3 Maximum capacity in \b bytes of the string in ARG2
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(To_Lower)(
    CHAR(P) NONULL OUT0, TgRSIZE ARG1, CHAR(CP) NONULL ARG2, TgRSIZE ARG3 );



/** @brief Copy the string in ARG2 to ARG0
    @param [out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string
    @param [in] ARG3 Maximum capacity in \b bytes of the string in ARG2
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(Copy)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, CHAR(CPC) NONULL ARG2, TgRSIZE_C ARG3 );

/** @brief Append the string at ARG2 to the string at ARG0
    @param [in,out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string
    @param [in] ARG3 Maximum capacity in \b bytes of the string in ARG2
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(Append)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, CHAR(CPC) NONULL ARG2, TgRSIZE_C ARG3 );

/** @brief Copy the string in ARG2 to ARG0, up to a maximum of ARG4 characters
    @param [out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string
    @param [in] ARG3 Maximum capacity in \b bytes of the string in ARG2
    @param [in] ARG4 Number of \b characters to be copied (not including null-term)
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(CopyN)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, CHAR(CPC) NONULL ARG2, TgRSIZE_C ARG3, TgRSIZE_C ARG4 );

/** @brief Append the string in ARG2 to ARG0, up to a maximum of ARG4 characters
    @param [in,out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string
    @param [in] ARG3 Maximum capacity in \b bytes of the string in ARG2
    @param [in] ARG4 Number of \b characters to be copied (not including null-term)
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(AppendN)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, CHAR(CPC) NONULL ARG2, TgRSIZE_C ARG3, TgRSIZE_C ARG4 );



/** @brief Find the next token in ARG1 separated by characters in ARG2 and output it in ARG0
    @param [out] OUT0 Used to store a pointer to the next token or nullptr otherwise
    @param [in,out] ARG1 String to tokenize (will be modified)
    @param [in] ARG2 Remaining size of the string in ARG0 to evaluate, updated as an output of the function call
    @param [in] ARG3 A string containing a list of delimiters
    @param [in,out] ARG4 Used by the function to store internal state
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(Token)(
    CHAR(PP) OUT0, CHAR(PC) OKNULL ARG1, TgRSIZE_P NONULL ARG2, CHAR(CPC) NONULL ARG3, CHAR(PP) NONULL ARG4 );

/** @brief Finds the first occurrence of the character ARG1 in the string at ARG0
    @param [out] OUT0 Offset in ARG1 to the first instance of the string in ARG3
    @param [in] ARG1 Source string
    @param [in] ARG2 Maximum capacity in \b bytes of the string in ARG1
    @param [in] ARG3 Character used for matching
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(StrChr)(
    TgRSIZE_P NONULL OUT0, CHAR(CPC) NONULL ARG1, TgRSIZE_C ARG2, CHAR(C) ARG3 );

/** @brief Finds the first occurrence of the string pointed at ARG1 in the string at ARG0
    @param [out] OUT0 Offset in ARG1 to the first instance of the string in ARG3
    @param [in] ARG1 Source string
    @param [in] ARG2 Maximum capacity in \b bytes of the string in ARG1
    @param [in] ARG3 String used for matching
    @param [in] ARG4 Maximum capacity in \b bytes of the string in ARG3
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(StrStr)(
    TgRSIZE_P NONULL OUT0, CHAR(CPC) NONULL ARG1, TgRSIZE_C ARG2, CHAR(CPC) NONULL ARG3, TgRSIZE_C ARG4 );

/** @brief Parse the source string taking into account c-style comments, and quotations
    @param [out] OUT0 Array of token pointers
    @param [in] ARG1 Max count of token pointers in ARG1
    @param [in] ARG2 Source string to tokenize (will be modified)
    @param [in] ARG3 Maximum capacity in \b bytes of the string in ARG2
    @return Number of tokens written into the array at ARG1 */
TgEXTN TgSINT_F32
FCN(Token_List)(
    CHAR(PP) NONULL OUT0, TgSINT_F32_C ARG1, CHAR(PC) NONULL ARG2, TgRSIZE_C ARG3 );



/** @brief Process a printf-style string and return the resultant length of it
    @param [out] OUT0 Contains the resultant length of the string
    @param [in] ARG1 String optionally containing printf markers
    @param [in] ARG2 Variable argument list
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(LengthVF_Count)(
    TgRSIZE_P NONULL OUT0, CHAR(CPC) NONULL ARG1, va_list ARG2 );

/** @brief Outputs the result of processing ARG2 into the string at ARG0
    @param [out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string for processing using printf notation
    @param [in] ARG3 Variable argument list
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(PrintVF)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, CHAR(CPC) NONULL ARG2, va_list ARG3 );

/** @brief Appends the resultant output of processing ARG2 to the end of the string in ARG0
    @param [in,out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string for processing using printf notation
    @param [in] ARG3 Variable argument list
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(AppendVF)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, CHAR(CPC) NONULL ARG2, va_list ARG3 );

/** @brief Outputs the result of processing ARG2 into the string at ARG0
    @param [out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string for processing using printf notation
    @param [in] ARG3 Optional list of arguments for use in ARG2 processing
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(PrintF)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, CHAR(CPC) NONULL ARG2, ... );

/** @brief Appends the resultant output of processing ARG2 to the end of the string in ARG0
    @param [in,out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string for processing using printf notation
    @param [in] ARG3 Optional list of arguments for use in ARG2 processing
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(AppendF)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, CHAR(CPC) NONULL ARG2, ... );



/** @brief Converts the string in ARG2 into the format for OUT0
    @param [out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string
    @param [in] ARG3 Maximum capacity in \b bytes of the string in ARG2
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(Convert_NSZ)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgCHAR_NC_CPC NONULL ARG2, TgRSIZE_C ARG3 );

/** @brief Converts the string in ARG2 into the format for OUT0
    @param [out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string
    @param [in] ARG3 Maximum capacity in \b bytes of the string in ARG2
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(Convert_WSZ)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgCHAR_WC_CPC NONULL ARG2, TgRSIZE_C ARG3 );

/** @brief Converts the string in ARG2 into the format for OUT0
    @param [out] OUT0 Destination for resulting output
    @param [in] ARG1 Maximum capacity in \b bytes of the string in OUT0
    @param [in] ARG2 Source string
    @param [in] ARG3 Maximum capacity in \b bytes of the string in ARG2
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
FCN(Convert_USZ)(
    CHAR(PC) NONULL OUT0, TgRSIZE_C ARG1, TgCHAR_U8_CPC NONULL ARG2, TgRSIZE_C ARG3 );


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Text].h_inc"

/* =============================================================================================================================================================================== */


/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #define GENERATE__USZ
    #include __FILE__

    #define GENERATE__WSZ
    #include __FILE__

    #define GENERATE__NSZ
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TGS_COMMON_BASE_API_TEXT_H

/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COMMON_BASE_API_TEXT_H) */
#endif
