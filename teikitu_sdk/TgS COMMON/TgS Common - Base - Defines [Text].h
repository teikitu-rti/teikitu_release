/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Defines [Text].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_DEFINES_TEXT_H)
#define TGS_COMMON_BASE_DEFINES_TEXT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  String Literals for Testing                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define KTgNC_LIT_TEST__ENGLISH             "Test"

#define KTgU8_LIT_TEST__ENGLISH             u8"Test"
#define KTgU8_LIT_TEST__JAPANESE            u8"\U000030c6\U000030b9\U000030c8"
#define KTgU8_LIT_TEST__CHINESE_SIMPLIFIED  u8"\U00006d4b\U00008bd5"
#define KTgU8_LIT_TEST__RUSSIAN             u8"\U00000442\U00000435\U00000441\U00000442\U0000043e\U00000432\U0000043e\U00000435 \U00000437\U00000430\U00000434\U00000430\U0000043d\U00000438"
#define KTgU8_LIT_TEST__BURMESE             u8"\U00001005\U00001019\U0000103a\U00001038\U0000101e\U00001015\U0000103a\U00001019\U0000103e\U0000102f"
#define KTgU8_LIT_TEST__KOREAN              u8"\U0000d14c\U0000c2a4\U0000d2b8"

#define KTgWC_LIT_TEST__ENGLISH             L"Test"
#define KTgWC_LIT_TEST__JAPANESE            L"\U000030c6\U000030b9\U000030c8"
#define KTgWC_LIT_TEST__CHINESE_SIMPLIFIED  L"\U00006d4b\U00008bd5"
#define KTgWC_LIT_TEST__RUSSIAN             L"\U00000442\U00000435\U00000441\U00000442\U0000043e\U00000432\U0000043e\U00000435 \U00000437\U00000430\U00000434\U00000430\U0000043d\U00000438"
#define KTgWC_LIT_TEST__BURMESE             L"\U00001005\U00001019\U0000103a\U00001038\U0000101e\U00001015\U0000103a\U00001019\U0000103e\U0000102f"
#define KTgWC_LIT_TEST__KOREAN              L"\U0000d14c\U0000c2a4\U0000d2b8"




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Unicode Macros                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TgMACRO_IS_UTF08_MB_SEQ_START(A)    (0xC0 == ((A) & 0xC0))
#define TgMACRO_IS_UTF08_MB_SEQ(A)          (0x80 == ((A) & 0xC0))


/* =============================================================================================================================================================================== */
#endif
