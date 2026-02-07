/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (POSIX) Input - Keyboard.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COMMON/TgS Common - Util MT - LA Ring Buffer SRSW.inl"


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Constants                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static const GUID                           MS_GUID_Key = { 0x55728220L, 0xD33C, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };

TgMSVC_WARN_DISABLE_PUSH( 4820 )

static const struct
{
    TgUINT_E32                                  m_uiDIK;
    ETgPROP_KEYBOARD                            m_enProp;
    TgCHAR_U8                                   m_uiChar;
}                                           s_auiKEY_DIK[] =
{
    { 0x02, ETgPROP_KEY_MAX, '1' },
    { 0x03, ETgPROP_KEY_MAX, '2' },
    { 0x04, ETgPROP_KEY_MAX, '3' },
    { 0x05, ETgPROP_KEY_MAX, '4' },
    { 0x06, ETgPROP_KEY_MAX, '5' },
    { 0x07, ETgPROP_KEY_MAX, '6' },
    { 0x08, ETgPROP_KEY_MAX, '7' },
    { 0x09, ETgPROP_KEY_MAX, '8' },
    { 0x0A, ETgPROP_KEY_MAX, '9' },
    { 0x0B, ETgPROP_KEY_MAX, '0' },
    { 0x0C, ETgPROP_KEY_MAX, '-' },
    { 0x0D, ETgPROP_KEY_MAX, '=' },
    { 0x10, ETgPROP_KEY_MAX, 'Q' },
    { 0x11, ETgPROP_KEY_MAX, 'W' },
    { 0x12, ETgPROP_KEY_MAX, 'E' },
    { 0x13, ETgPROP_KEY_MAX, 'R' },
    { 0x14, ETgPROP_KEY_MAX, 'T' },
    { 0x15, ETgPROP_KEY_MAX, 'Y' },
    { 0x16, ETgPROP_KEY_MAX, 'U' },
    { 0x17, ETgPROP_KEY_MAX, 'I' },
    { 0x18, ETgPROP_KEY_MAX, 'O' },
    { 0x19, ETgPROP_KEY_MAX, 'P' },
    { 0x1A, ETgPROP_KEY_MAX, '[' },
    { 0x1B, ETgPROP_KEY_MAX, ']' },
    { 0x1E, ETgPROP_KEY_MAX, 'A' },
    { 0x1F, ETgPROP_KEY_MAX, 'S' },
    { 0x20, ETgPROP_KEY_MAX, 'D' },
    { 0x21, ETgPROP_KEY_MAX, 'F' },
    { 0x22, ETgPROP_KEY_MAX, 'G' },
    { 0x23, ETgPROP_KEY_MAX, 'H' },
    { 0x24, ETgPROP_KEY_MAX, 'J' },
    { 0x25, ETgPROP_KEY_MAX, 'K' },
    { 0x26, ETgPROP_KEY_MAX, 'L' },
    { 0x27, ETgPROP_KEY_MAX, ';' },
    { 0x28, ETgPROP_KEY_MAX, '\'' },
    { 0x2B, ETgPROP_KEY_MAX, '\\' },
    { 0x2C, ETgPROP_KEY_MAX, 'Z' },
    { 0x2D, ETgPROP_KEY_MAX, 'X' },
    { 0x2E, ETgPROP_KEY_MAX, 'C' },
    { 0x2F, ETgPROP_KEY_MAX, 'V' },
    { 0x30, ETgPROP_KEY_MAX, 'B' },
    { 0x31, ETgPROP_KEY_MAX, 'N' },
    { 0x32, ETgPROP_KEY_MAX, 'M' },
    { 0x33, ETgPROP_KEY_MAX, ',' },
    { 0x34, ETgPROP_KEY_MAX, '.' },
    { 0x35, ETgPROP_KEY_MAX, '/' },
    { 0x39, ETgPROP_KEY_MAX, ' ' },
    { 0x3B, ETgPROP_KEY_F1, '\0' },
    { 0x3C, ETgPROP_KEY_F2, '\0' },
    { 0x3D, ETgPROP_KEY_F3, '\0' },
    { 0x3E, ETgPROP_KEY_F4, '\0' },
    { 0x3F, ETgPROP_KEY_F5, '\0' },
    { 0x40, ETgPROP_KEY_F6, '\0' },
    { 0x41, ETgPROP_KEY_F7, '\0' },
    { 0x42, ETgPROP_KEY_F8, '\0' },
    { 0x43, ETgPROP_KEY_F9, '\0' },
    { 0x44, ETgPROP_KEY_F10, '\0' },
    { 0x57, ETgPROP_KEY_F11, '\0' },
    { 0x58, ETgPROP_KEY_F12, '\0' },
    { 0x52, ETgPROP_KEY_NUMPAD_0, '\0' },
    { 0x4F, ETgPROP_KEY_NUMPAD_1, '\0' },
    { 0x50, ETgPROP_KEY_NUMPAD_2, '\0' },
    { 0x51, ETgPROP_KEY_NUMPAD_3, '\0' },
    { 0x4B, ETgPROP_KEY_NUMPAD_4, '\0' },
    { 0x4C, ETgPROP_KEY_NUMPAD_5, '\0' },
    { 0x4D, ETgPROP_KEY_NUMPAD_6, '\0' },
    { 0x47, ETgPROP_KEY_NUMPAD_7, '\0' },
    { 0x48, ETgPROP_KEY_NUMPAD_8, '\0' },
    { 0x49, ETgPROP_KEY_NUMPAD_9, '\0' },
    { 0x53, ETgPROP_KEY_NUMPAD_DECIMAL, '\0' },
    { 0x9C, ETgPROP_KEY_NUMPAD_ENTER, '\0' },
    { 0x4E, ETgPROP_KEY_NUMPAD_ADD, '\0' },
    { 0x4A, ETgPROP_KEY_NUMPAD_SUBTRACT, '\0' },
    { 0x37, ETgPROP_KEY_NUMPAD_MULTIPLY, '\0' },
    { 0xB5, ETgPROP_KEY_NUMPAD_DIVIDE, '\0' },
    { 0xD2, ETgPROP_KEY_INSERT, '\0' },
    { 0xC7, ETgPROP_KEY_HOME, '\0' },
    { 0xC9, ETgPROP_KEY_PAGE_UP, '\0' },
    { 0xD3, ETgPROP_KEY_DELETE, '\0' },
    { 0xCF, ETgPROP_KEY_END, '\0' },
    { 0xD1, ETgPROP_KEY_PAGE_DOWN, '\0' },
    { 0xC8, ETgPROP_KEY_UP, '\0' },
    { 0xD0, ETgPROP_KEY_DOWN, '\0' },
    { 0xCB, ETgPROP_KEY_LEFT, '\0' },
    { 0xCD, ETgPROP_KEY_RIGHT, '\0' },
    { 0x0E, ETgPROP_KEY_BACK, '\0' },
    { 0x0F, ETgPROP_KEY_TAB, '\0' },
    { 0x01, ETgPROP_KEY_ESCAPE, '\0' },
    { 0x1C, ETgPROP_KEY_ENTER, '\0' },
};

TgMSVC_WARN_DISABLE_POP()

static DIOBJECTDATAFORMAT s_asKeyboard_Layout[] = {
    { &MS_GUID_Key, 0, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 0 ), 0 },
    { &MS_GUID_Key, 1, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 1 ), 0 },
    { &MS_GUID_Key, 2, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 2 ), 0 },
    { &MS_GUID_Key, 3, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 3 ), 0 },
    { &MS_GUID_Key, 4, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 4 ), 0 },
    { &MS_GUID_Key, 5, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 5 ), 0 },
    { &MS_GUID_Key, 6, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 6 ), 0 },
    { &MS_GUID_Key, 7, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 7 ), 0 },
    { &MS_GUID_Key, 8, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 8 ), 0 },
    { &MS_GUID_Key, 9, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 9 ), 0 },
    { &MS_GUID_Key, 10, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 10 ), 0 },
    { &MS_GUID_Key, 11, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 11 ), 0 },
    { &MS_GUID_Key, 12, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 12 ), 0 },
    { &MS_GUID_Key, 13, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 13 ), 0 },
    { &MS_GUID_Key, 14, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 14 ), 0 },
    { &MS_GUID_Key, 15, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 15 ), 0 },
    { &MS_GUID_Key, 16, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 16 ), 0 },
    { &MS_GUID_Key, 17, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 17 ), 0 },
    { &MS_GUID_Key, 18, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 18 ), 0 },
    { &MS_GUID_Key, 19, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 19 ), 0 },
    { &MS_GUID_Key, 20, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 20 ), 0 },
    { &MS_GUID_Key, 21, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 21 ), 0 },
    { &MS_GUID_Key, 22, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 22 ), 0 },
    { &MS_GUID_Key, 23, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 23 ), 0 },
    { &MS_GUID_Key, 24, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 24 ), 0 },
    { &MS_GUID_Key, 25, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 25 ), 0 },
    { &MS_GUID_Key, 26, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 26 ), 0 },
    { &MS_GUID_Key, 27, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 27 ), 0 },
    { &MS_GUID_Key, 28, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 28 ), 0 },
    { &MS_GUID_Key, 29, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 29 ), 0 },
    { &MS_GUID_Key, 30, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 30 ), 0 },
    { &MS_GUID_Key, 31, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 31 ), 0 },
    { &MS_GUID_Key, 32, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 32 ), 0 },
    { &MS_GUID_Key, 33, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 33 ), 0 },
    { &MS_GUID_Key, 34, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 34 ), 0 },
    { &MS_GUID_Key, 35, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 35 ), 0 },
    { &MS_GUID_Key, 36, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 36 ), 0 },
    { &MS_GUID_Key, 37, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 37 ), 0 },
    { &MS_GUID_Key, 38, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 38 ), 0 },
    { &MS_GUID_Key, 39, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 39 ), 0 },
    { &MS_GUID_Key, 40, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 40 ), 0 },
    { &MS_GUID_Key, 41, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 41 ), 0 },
    { &MS_GUID_Key, 42, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 42 ), 0 },
    { &MS_GUID_Key, 43, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 43 ), 0 },
    { &MS_GUID_Key, 44, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 44 ), 0 },
    { &MS_GUID_Key, 45, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 45 ), 0 },
    { &MS_GUID_Key, 46, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 46 ), 0 },
    { &MS_GUID_Key, 47, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 47 ), 0 },
    { &MS_GUID_Key, 48, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 48 ), 0 },
    { &MS_GUID_Key, 49, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 49 ), 0 },
    { &MS_GUID_Key, 50, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 50 ), 0 },
    { &MS_GUID_Key, 51, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 51 ), 0 },
    { &MS_GUID_Key, 52, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 52 ), 0 },
    { &MS_GUID_Key, 53, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 53 ), 0 },
    { &MS_GUID_Key, 54, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 54 ), 0 },
    { &MS_GUID_Key, 55, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 55 ), 0 },
    { &MS_GUID_Key, 56, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 56 ), 0 },
    { &MS_GUID_Key, 57, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 57 ), 0 },
    { &MS_GUID_Key, 58, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 58 ), 0 },
    { &MS_GUID_Key, 59, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 59 ), 0 },
    { &MS_GUID_Key, 60, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 60 ), 0 },
    { &MS_GUID_Key, 61, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 61 ), 0 },
    { &MS_GUID_Key, 62, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 62 ), 0 },
    { &MS_GUID_Key, 63, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 63 ), 0 },
    { &MS_GUID_Key, 64, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 64 ), 0 },
    { &MS_GUID_Key, 65, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 65 ), 0 },
    { &MS_GUID_Key, 66, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 66 ), 0 },
    { &MS_GUID_Key, 67, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 67 ), 0 },
    { &MS_GUID_Key, 68, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 68 ), 0 },
    { &MS_GUID_Key, 69, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 69 ), 0 },
    { &MS_GUID_Key, 70, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 70 ), 0 },
    { &MS_GUID_Key, 71, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 71 ), 0 },
    { &MS_GUID_Key, 72, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 72 ), 0 },
    { &MS_GUID_Key, 73, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 73 ), 0 },
    { &MS_GUID_Key, 74, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 74 ), 0 },
    { &MS_GUID_Key, 75, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 75 ), 0 },
    { &MS_GUID_Key, 76, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 76 ), 0 },
    { &MS_GUID_Key, 77, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 77 ), 0 },
    { &MS_GUID_Key, 78, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 78 ), 0 },
    { &MS_GUID_Key, 79, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 79 ), 0 },
    { &MS_GUID_Key, 80, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 80 ), 0 },
    { &MS_GUID_Key, 81, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 81 ), 0 },
    { &MS_GUID_Key, 82, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 82 ), 0 },
    { &MS_GUID_Key, 83, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 83 ), 0 },
    { &MS_GUID_Key, 84, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 84 ), 0 },
    { &MS_GUID_Key, 85, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 85 ), 0 },
    { &MS_GUID_Key, 86, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 86 ), 0 },
    { &MS_GUID_Key, 87, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 87 ), 0 },
    { &MS_GUID_Key, 88, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 88 ), 0 },
    { &MS_GUID_Key, 89, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 89 ), 0 },
    { &MS_GUID_Key, 90, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 90 ), 0 },
    { &MS_GUID_Key, 91, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 91 ), 0 },
    { &MS_GUID_Key, 92, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 92 ), 0 },
    { &MS_GUID_Key, 93, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 93 ), 0 },
    { &MS_GUID_Key, 94, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 94 ), 0 },
    { &MS_GUID_Key, 95, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 95 ), 0 },
    { &MS_GUID_Key, 96, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 96 ), 0 },
    { &MS_GUID_Key, 97, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 97 ), 0 },
    { &MS_GUID_Key, 98, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 98 ), 0 },
    { &MS_GUID_Key, 99, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 99 ), 0 },
    { &MS_GUID_Key, 100, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 100 ), 0 },
    { &MS_GUID_Key, 101, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 101 ), 0 },
    { &MS_GUID_Key, 102, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 102 ), 0 },
    { &MS_GUID_Key, 103, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 103 ), 0 },
    { &MS_GUID_Key, 104, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 104 ), 0 },
    { &MS_GUID_Key, 105, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 105 ), 0 },
    { &MS_GUID_Key, 106, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 106 ), 0 },
    { &MS_GUID_Key, 107, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 107 ), 0 },
    { &MS_GUID_Key, 108, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 108 ), 0 },
    { &MS_GUID_Key, 109, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 109 ), 0 },
    { &MS_GUID_Key, 110, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 110 ), 0 },
    { &MS_GUID_Key, 111, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 111 ), 0 },
    { &MS_GUID_Key, 112, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 112 ), 0 },
    { &MS_GUID_Key, 113, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 113 ), 0 },
    { &MS_GUID_Key, 114, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 114 ), 0 },
    { &MS_GUID_Key, 115, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 115 ), 0 },
    { &MS_GUID_Key, 116, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 116 ), 0 },
    { &MS_GUID_Key, 117, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 117 ), 0 },
    { &MS_GUID_Key, 118, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 118 ), 0 },
    { &MS_GUID_Key, 119, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 119 ), 0 },
    { &MS_GUID_Key, 120, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 120 ), 0 },
    { &MS_GUID_Key, 121, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 121 ), 0 },
    { &MS_GUID_Key, 122, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 122 ), 0 },
    { &MS_GUID_Key, 123, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 123 ), 0 },
    { &MS_GUID_Key, 124, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 124 ), 0 },
    { &MS_GUID_Key, 125, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 125 ), 0 },
    { &MS_GUID_Key, 126, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 126 ), 0 },
    { &MS_GUID_Key, 127, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 127 ), 0 },
    { &MS_GUID_Key, 128, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 128 ), 0 },
    { &MS_GUID_Key, 129, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 129 ), 0 },
    { &MS_GUID_Key, 130, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 130 ), 0 },
    { &MS_GUID_Key, 131, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 131 ), 0 },
    { &MS_GUID_Key, 132, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 132 ), 0 },
    { &MS_GUID_Key, 133, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 133 ), 0 },
    { &MS_GUID_Key, 134, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 134 ), 0 },
    { &MS_GUID_Key, 135, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 135 ), 0 },
    { &MS_GUID_Key, 136, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 136 ), 0 },
    { &MS_GUID_Key, 137, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 137 ), 0 },
    { &MS_GUID_Key, 138, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 138 ), 0 },
    { &MS_GUID_Key, 139, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 139 ), 0 },
    { &MS_GUID_Key, 140, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 140 ), 0 },
    { &MS_GUID_Key, 141, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 141 ), 0 },
    { &MS_GUID_Key, 142, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 142 ), 0 },
    { &MS_GUID_Key, 143, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 143 ), 0 },
    { &MS_GUID_Key, 144, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 144 ), 0 },
    { &MS_GUID_Key, 145, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 145 ), 0 },
    { &MS_GUID_Key, 146, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 146 ), 0 },
    { &MS_GUID_Key, 147, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 147 ), 0 },
    { &MS_GUID_Key, 148, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 148 ), 0 },
    { &MS_GUID_Key, 149, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 149 ), 0 },
    { &MS_GUID_Key, 150, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 150 ), 0 },
    { &MS_GUID_Key, 151, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 151 ), 0 },
    { &MS_GUID_Key, 152, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 152 ), 0 },
    { &MS_GUID_Key, 153, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 153 ), 0 },
    { &MS_GUID_Key, 154, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 154 ), 0 },
    { &MS_GUID_Key, 155, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 155 ), 0 },
    { &MS_GUID_Key, 156, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 156 ), 0 },
    { &MS_GUID_Key, 157, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 157 ), 0 },
    { &MS_GUID_Key, 158, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 158 ), 0 },
    { &MS_GUID_Key, 159, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 159 ), 0 },
    { &MS_GUID_Key, 160, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 160 ), 0 },
    { &MS_GUID_Key, 161, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 161 ), 0 },
    { &MS_GUID_Key, 162, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 162 ), 0 },
    { &MS_GUID_Key, 163, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 163 ), 0 },
    { &MS_GUID_Key, 164, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 164 ), 0 },
    { &MS_GUID_Key, 165, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 165 ), 0 },
    { &MS_GUID_Key, 166, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 166 ), 0 },
    { &MS_GUID_Key, 167, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 167 ), 0 },
    { &MS_GUID_Key, 168, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 168 ), 0 },
    { &MS_GUID_Key, 169, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 169 ), 0 },
    { &MS_GUID_Key, 170, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 170 ), 0 },
    { &MS_GUID_Key, 171, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 171 ), 0 },
    { &MS_GUID_Key, 172, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 172 ), 0 },
    { &MS_GUID_Key, 173, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 173 ), 0 },
    { &MS_GUID_Key, 174, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 174 ), 0 },
    { &MS_GUID_Key, 175, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 175 ), 0 },
    { &MS_GUID_Key, 176, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 176 ), 0 },
    { &MS_GUID_Key, 177, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 177 ), 0 },
    { &MS_GUID_Key, 178, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 178 ), 0 },
    { &MS_GUID_Key, 179, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 179 ), 0 },
    { &MS_GUID_Key, 180, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 180 ), 0 },
    { &MS_GUID_Key, 181, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 181 ), 0 },
    { &MS_GUID_Key, 182, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 182 ), 0 },
    { &MS_GUID_Key, 183, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 183 ), 0 },
    { &MS_GUID_Key, 184, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 184 ), 0 },
    { &MS_GUID_Key, 185, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 185 ), 0 },
    { &MS_GUID_Key, 186, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 186 ), 0 },
    { &MS_GUID_Key, 187, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 187 ), 0 },
    { &MS_GUID_Key, 188, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 188 ), 0 },
    { &MS_GUID_Key, 189, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 189 ), 0 },
    { &MS_GUID_Key, 190, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 190 ), 0 },
    { &MS_GUID_Key, 191, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 191 ), 0 },
    { &MS_GUID_Key, 192, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 192 ), 0 },
    { &MS_GUID_Key, 193, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 193 ), 0 },
    { &MS_GUID_Key, 194, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 194 ), 0 },
    { &MS_GUID_Key, 195, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 195 ), 0 },
    { &MS_GUID_Key, 196, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 196 ), 0 },
    { &MS_GUID_Key, 197, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 197 ), 0 },
    { &MS_GUID_Key, 198, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 198 ), 0 },
    { &MS_GUID_Key, 199, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 199 ), 0 },
    { &MS_GUID_Key, 200, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 200 ), 0 },
    { &MS_GUID_Key, 201, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 201 ), 0 },
    { &MS_GUID_Key, 202, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 202 ), 0 },
    { &MS_GUID_Key, 203, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 203 ), 0 },
    { &MS_GUID_Key, 204, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 204 ), 0 },
    { &MS_GUID_Key, 205, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 205 ), 0 },
    { &MS_GUID_Key, 206, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 206 ), 0 },
    { &MS_GUID_Key, 207, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 207 ), 0 },
    { &MS_GUID_Key, 208, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 208 ), 0 },
    { &MS_GUID_Key, 209, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 209 ), 0 },
    { &MS_GUID_Key, 210, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 210 ), 0 },
    { &MS_GUID_Key, 211, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 211 ), 0 },
    { &MS_GUID_Key, 212, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 212 ), 0 },
    { &MS_GUID_Key, 213, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 213 ), 0 },
    { &MS_GUID_Key, 214, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 214 ), 0 },
    { &MS_GUID_Key, 215, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 215 ), 0 },
    { &MS_GUID_Key, 216, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 216 ), 0 },
    { &MS_GUID_Key, 217, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 217 ), 0 },
    { &MS_GUID_Key, 218, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 218 ), 0 },
    { &MS_GUID_Key, 219, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 219 ), 0 },
    { &MS_GUID_Key, 220, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 220 ), 0 },
    { &MS_GUID_Key, 221, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 221 ), 0 },
    { &MS_GUID_Key, 222, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 222 ), 0 },
    { &MS_GUID_Key, 223, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 223 ), 0 },
    { &MS_GUID_Key, 224, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 224 ), 0 },
    { &MS_GUID_Key, 225, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 225 ), 0 },
    { &MS_GUID_Key, 226, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 226 ), 0 },
    { &MS_GUID_Key, 227, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 227 ), 0 },
    { &MS_GUID_Key, 228, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 228 ), 0 },
    { &MS_GUID_Key, 229, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 229 ), 0 },
    { &MS_GUID_Key, 230, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 230 ), 0 },
    { &MS_GUID_Key, 231, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 231 ), 0 },
    { &MS_GUID_Key, 232, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 232 ), 0 },
    { &MS_GUID_Key, 233, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 233 ), 0 },
    { &MS_GUID_Key, 234, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 234 ), 0 },
    { &MS_GUID_Key, 235, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 235 ), 0 },
    { &MS_GUID_Key, 236, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 236 ), 0 },
    { &MS_GUID_Key, 237, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 237 ), 0 },
    { &MS_GUID_Key, 238, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 238 ), 0 },
    { &MS_GUID_Key, 239, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 239 ), 0 },
    { &MS_GUID_Key, 240, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 240 ), 0 },
    { &MS_GUID_Key, 241, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 241 ), 0 },
    { &MS_GUID_Key, 242, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 242 ), 0 },
    { &MS_GUID_Key, 243, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 243 ), 0 },
    { &MS_GUID_Key, 244, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 244 ), 0 },
    { &MS_GUID_Key, 245, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 245 ), 0 },
    { &MS_GUID_Key, 246, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 246 ), 0 },
    { &MS_GUID_Key, 247, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 247 ), 0 },
    { &MS_GUID_Key, 248, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 248 ), 0 },
    { &MS_GUID_Key, 249, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 249 ), 0 },
    { &MS_GUID_Key, 250, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 250 ), 0 },
    { &MS_GUID_Key, 251, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 251 ), 0 },
    { &MS_GUID_Key, 252, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 252 ), 0 },
    { &MS_GUID_Key, 253, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 253 ), 0 },
    { &MS_GUID_Key, 254, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 254 ), 0 },
    { &MS_GUID_Key, 255, DIDFT_BUTTON | 0x80000000 | DIDFT_MAKEINSTANCE( 255 ), 0 }
};

static const DIDATAFORMAT s_sKeyboard_Format =
{
    sizeof( DIDATAFORMAT ),                                           /* Size of this structure */
    sizeof( DIOBJECTDATAFORMAT ),                                     /* Size of object data format */
    DIDF_RELAXIS,                                                     /* Relative axis coordinates */
    256,                                                              /* Size of device data */
    sizeof( s_asKeyboard_Layout ) / sizeof( s_asKeyboard_Layout[0] ), /* Number of objects */
    s_asKeyboard_Layout,                                              /* And here they are */
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_IN_Keyboard,)
{
    TgUINT_E08                                  m_auiData[2][256];
    TgUINT_E32                                  m_uiBuffer;
    TgBOOL                                      m_bValid;
    TgUINT_E08                                  m_uiPad[3];
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static STg2_IN_Keyboard                     s_asKeyboard[KTgCONTROLLER_KEYBOARD_MAX];
static LPDIRECTINPUTDEVICE8                 s_pdxKeyboard = nullptr;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgIN_PM_Init_Keyboard ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Init_Keyboard( TgVOID )
{
    tgMM_Set_U08_0x00( s_asKeyboard, sizeof( s_asKeyboard ) );
    s_pdxKeyboard = nullptr;

    if(TgFAILED(g_pfnDIN8_CreateDevice( g_pdxDI, MS_REF GUID_SysKeyboard, (LPDIRECTINPUTDEVICE8*)&s_pdxKeyboard, nullptr )))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to create keyboard." );
        return (KTgE_FAIL);
    };

    if (TgFAILED( g_pfnDID8_SetDataFormat( s_pdxKeyboard, (LPCDIDATAFORMAT)&s_sKeyboard_Format ) ))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to setup keyboard." );
        g_pfnDID8_Release( s_pdxKeyboard );
        s_pdxKeyboard = nullptr;
        return (KTgE_FAIL);
    };

    //if (TgFAILED( g_pfnDID8_SetCooperativeLevel( s_pdxKeyboard, g_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE ) ))
    //{
    //    TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to setup keyboard." );
    //    g_pfnDID8_Release( s_pdxKeyboard );
    //    s_pdxKeyboard = nullptr;
    //    return (KTgE_FAIL);
    //};

    return (KTgS_OK);
}


/* ---- tgIN_PM_Boot_Keyboard ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Boot_Keyboard( TgVOID )
{
    if (TgFAILED( g_pfnDID8_Acquire( s_pdxKeyboard ) ))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to acquire keyboard." );
        return (KTgE_FAIL);
    };

    g_asController_Active[ETgCONTROLLER_KEYBOARD].m_pfnProduce = tgIN_PM_Update_Keyboard;
    g_asController_Active[ETgCONTROLLER_KEYBOARD].m_enController = ETgCONTROLLER_KEYBOARD;
    g_asController_Active[ETgCONTROLLER_KEYBOARD].m_psConsumer = nullptr;
    tgCM_UT_LF__LA_RB_SRSW__Init( &g_asController_Active[ETgCONTROLLER_KEYBOARD].m_sLA_RB_SRSW, KTgCONTROLLER_MAX_EVENT );

    return (KTgS_OK);
}


/* ---- tgIN_PM_Stop_Keyboard ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Stop_Keyboard( TgVOID )
{
    g_asController_Active[ETgCONTROLLER_KEYBOARD].m_pfnProduce = nullptr;
    g_asController_Active[ETgCONTROLLER_KEYBOARD].m_enController = ETgCONTROLLER__MAX;
    g_asController_Active[ETgCONTROLLER_KEYBOARD].m_psConsumer = nullptr;

    g_pfnDID8_Unacquire( s_pdxKeyboard );

    return (KTgS_OK);
}


/* ---- tgIN_PM_Free_Keyboard ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIN_PM_Free_Keyboard( TgVOID )
{
    if (nullptr != s_pdxKeyboard)
    {
        g_pfnDID8_Release( s_pdxKeyboard );
        s_pdxKeyboard = nullptr;
    };
    return (KTgS_OK);
}


/* ---- tgIN_PM_Update_Keyboard -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgIN_PM_Update_Keyboard( ETgCONTROLLER_C enController )
{
    TgUINT_E32_C    uiID = (TgUINT_E32)(enController - ETgCONTROLLER_KEYBOARD);
    TgUINT_E32_C    uiNext_Buffer = s_asKeyboard[uiID].m_uiBuffer ^ 1;
    TgUINT_E32                          uiIndex;
    TgUINT_E32                          uiEvent;
    TgUINT_E32                          uiState = ETgSTATE_KEYBOARD_VALID;

    TgERROR( uiID < KTgCONTROLLER_KEYBOARD_MAX );
    s_asKeyboard[uiID].m_uiBuffer = uiNext_Buffer; /* Advance the buffer id value (this is the device not the event buffer). */

    /* Read the keyboard state */
    if (TgFAILED( g_pfnDID8_GetDeviceState( s_pdxKeyboard, 256, (TgVOID_P)(s_asKeyboard[uiID].m_auiData[uiNext_Buffer]) ) ))
    {
        TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to get keyboard data." );
        s_asKeyboard[uiID].m_bValid = false;

        if (TgFAILED( g_pfnDID8_Acquire( s_pdxKeyboard ) ))
        {
            TgERROR_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to acquire keyboard." );
        };

        return;
    };

    if (!s_asKeyboard[uiID].m_bValid)
    {
        tgMM_Set_U08_0x00( &(s_asKeyboard[uiID].m_auiData[uiNext_Buffer ^ 1]), sizeof( s_asKeyboard[uiID].m_auiData[0] ) );
        s_asKeyboard[uiID].m_bValid = true;
    };

    if (nullptr == g_asController_Active[enController].m_psConsumer)
    {
        return;
    };

    uiState |= 0 != (0x80 & s_asKeyboard[uiID].m_auiData[uiNext_Buffer][0x2A]) ? ETgSTATE_KEYBOARD_LSHIFT : 0;
    uiState |= 0 != (0x80 & s_asKeyboard[uiID].m_auiData[uiNext_Buffer][0x36]) ? ETgSTATE_KEYBOARD_RSHIFT : 0;
    uiState |= 0 != (0x80 & s_asKeyboard[uiID].m_auiData[uiNext_Buffer][0x1D]) ? ETgSTATE_KEYBOARD_LCTRL : 0;
    uiState |= 0 != (0x80 & s_asKeyboard[uiID].m_auiData[uiNext_Buffer][0x9D]) ? ETgSTATE_KEYBOARD_RCTRL : 0;
    uiState |= 0 != (0x80 & s_asKeyboard[uiID].m_auiData[uiNext_Buffer][0x38]) ? ETgSTATE_KEYBOARD_LALT : 0;
    uiState |= 0 != (0x80 & s_asKeyboard[uiID].m_auiData[uiNext_Buffer][0xB8]) ? ETgSTATE_KEYBOARD_RALT : 0;
    uiState |= 0 != (0x80 & s_asKeyboard[uiID].m_auiData[uiNext_Buffer][0x3A]) ? ETgSTATE_KEYBOARD_CAPSLOCK : 0;
    uiState |= 0 != (0x80 & s_asKeyboard[uiID].m_auiData[uiNext_Buffer][0x45]) ? ETgSTATE_KEYBOARD_NUMLOCK : 0;

    for (uiIndex = 0; uiIndex < sizeof( s_auiKEY_DIK ) / sizeof( s_auiKEY_DIK[0] ); ++uiIndex)
    {
        TgUINT_E32_C    uiDIK = s_auiKEY_DIK[uiIndex].m_uiDIK;

        if (s_asKeyboard[uiID].m_auiData[0][uiDIK] == s_asKeyboard[uiID].m_auiData[1][uiDIK])
        {
            continue;
        };

        while (0 == tgCM_UT_LF__LA_RB_SRSW__Query_Free_Size( &g_asController_Active[enController].m_sLA_RB_SRSW ))
        {
            tgTR_Yield();
        };

        uiEvent = (TgUINT_E32)tgCM_UT_LF__LA_RB_SRSW__Push_Next_Index( &g_asController_Active[enController].m_sLA_RB_SRSW );

        g_asController_Active[enController].m_asEvent[uiEvent].m_enController = enController;
        g_asController_Active[enController].m_asEvent[uiEvent].m_uiState.Keyboard = uiState;
        g_asController_Active[enController].m_asEvent[uiEvent].m_enProp.Keyboard = s_auiKEY_DIK[uiIndex].m_enProp;
        g_asController_Active[enController].m_asEvent[uiEvent].m_uiUTF32 = (TgUINT_E32)s_auiKEY_DIK[uiIndex].m_uiChar;
        g_asController_Active[enController].m_asEvent[uiEvent].m_fValue = (s_asKeyboard[uiID].m_auiData[uiNext_Buffer][uiDIK] & 0x80) ? 1.0F : 0.0F;
        g_asController_Active[enController].m_asEvent[uiEvent].m_fDiff = (s_asKeyboard[uiID].m_auiData[uiNext_Buffer][uiDIK] & 0x80) ? 1.0F : -1.0F;

        tgCM_UT_LF__LA_RB_SRSW__Push_Commit( &g_asController_Active[enController].m_sLA_RB_SRSW );
    };
}


/* ---- tgIN_PM_Query_Fixed_Memory_Keyboard -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgIN_PM_Query_Fixed_Memory_Keyboard( TgVOID )
{
    return (0
            + sizeof( MS_GUID_Key )
            + sizeof( s_auiKEY_DIK )
            + sizeof( s_asKeyboard_Layout )
            + sizeof( s_sKeyboard_Format )
            + sizeof( s_asKeyboard )
            + sizeof( s_pdxKeyboard )
    );
}
