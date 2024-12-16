/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input - Constants.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_INPUT_CONSTANTS_H)
#define TGS_INPUT_CONSTANTS_H
#pragma once

#if !defined(TGS_INPUT_H)
#error This file should not be included directly - use the correct platform include wrapper
#endif


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_ENUM(ETgCONTROLLER, TgSINT_E32,

    ETgCONTROLLER__BEGIN,

    ETgCONTROLLER_GAMEPAD_0 = ETgCONTROLLER__BEGIN,                 ETgCONTROLLER_GAMEPAD_1,                                        ETgCONTROLLER_GAMEPAD_2,
    ETgCONTROLLER_GAMEPAD_3,                                        ETgCONTROLLER_KEYBOARD,                                         ETgCONTROLLER_GUI_KEYBOARD,
    ETgCONTROLLER_MOUSE,                                            ETgCONTROLLER_GUI_MOUSE,                                        ETgCONTROLLER_NET_0,
    ETgCONTROLLER_NET_1,                                            ETgCONTROLLER_NET_2,                                            ETgCONTROLLER_NET_3,

    ETgCONTROLLER__END,
    ETgCONTROLLER__MAX = ETgCONTROLLER__END,
    ETgCONTROLLER__COUNT = ETgCONTROLLER__END - ETgCONTROLLER__BEGIN,
);

TgTYPE_ENUM(ETgDEAD_ZONE, TgSINT_E32,
    ETgDEAD_ZONE_MOUSE_X,           ETgDEAD_ZONE_MOUSE_Y,           ETgDEAD_ZONE_MOUSE_Z,           ETgDEAD_ZONE_STICK_0_X,         ETgDEAD_ZONE_STICK_0_Y,
    ETgDEAD_ZONE_STICK_1_X,         ETgDEAD_ZONE_STICK_1_Y,         ETgDEAD_ZONE_MAX
);

/* Maximum number of events stored between successive update calls (size of input buffer).  This should be large enough to be able to send the current controller state */
/* when its connected.  This in the worse case could be an event for every controller property.  The keyboard is the exception in this case and client code has to be  */
/* prepared to deal with indeterminate input state with the keyboard controller. */
enum { KTgCONTROLLER_MAX_EVENT = 64 };

/* Maximum number of consumers in the system */
enum { KTgMAX_CONSUMER = 32 }; 

/* Maximum number of each input device type */
enum { KTgCONTROLLER_KEYBOARD_MAX = 1 };
enum { KTgCONTROLLER_GUI_KEYBOARD_MAX = 1 };
enum { KTgCONTROLLER_MOUSE_MAX = 1 };
enum { KTgCONTROLLER_GUI_MOUSE_MAX = 1 };
enum { KTgCONTROLLER_GAMEPAD_MAX = 4 };

/* ---- Controller Properties ---------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_ENUM(ETgPROP_GAMEPAD, TgSINT_E32,
    /* Digital Controls */
    ETgPROP_GAMEPAD__A,             ETgPROP_GAMEPAD__B,             ETgPROP_GAMEPAD__X,             ETgPROP_GAMEPAD__Y,             ETgPROP_GAMEPAD__DPAD_UP,
    ETgPROP_GAMEPAD__DPAD_DOWN,     ETgPROP_GAMEPAD__DPAD_LEFT,     ETgPROP_GAMEPAD__DPAD_RIGHT,    ETgPROP_GAMEPAD__LSHOULDER,     ETgPROP_GAMEPAD__RSHOULDER,
    ETgPROP_GAMEPAD__LTHUMB,        ETgPROP_GAMEPAD__RTHUMB,

    /* System Controls (Digital) */
    ETgPROP_GAMEPAD__START,         ETgPROP_GAMEPAD__BACK,

    /* Analog Controls */
    ETgPROP_GAMEPAD__LTRIGGER,      ETgPROP_GAMEPAD__RTRIGGER,      ETgPROP_GAMEPAD__LTHUMB_X,      ETgPROP_GAMEPAD__LTHUMB_Y,      ETgPROP_GAMEPAD__RTHUMB_X,
    ETgPROP_GAMEPAD__RTHUMB_Y,

    ETgPROP_GAMEPAD__VALID,         ETgPROP_GAMEPAD__MAX
);

TgTYPE_ENUM(ETgPROP_KEYBOARD, TgSINT_E32,
    /* Function Keys */
    ETgPROP_KEY_F1,                 ETgPROP_KEY_F2,                 ETgPROP_KEY_F3,                 ETgPROP_KEY_F4,                 ETgPROP_KEY_F5,
    ETgPROP_KEY_F6,                 ETgPROP_KEY_F7,                 ETgPROP_KEY_F8,                 ETgPROP_KEY_F9,                 ETgPROP_KEY_F10,
    ETgPROP_KEY_F11,                ETgPROP_KEY_F12,

    /* Numeric Pad */
    ETgPROP_KEY_NUMPAD_0,           ETgPROP_KEY_NUMPAD_1,           ETgPROP_KEY_NUMPAD_2,           ETgPROP_KEY_NUMPAD_3,           ETgPROP_KEY_NUMPAD_4,
    ETgPROP_KEY_NUMPAD_5,           ETgPROP_KEY_NUMPAD_6,           ETgPROP_KEY_NUMPAD_7,           ETgPROP_KEY_NUMPAD_8,           ETgPROP_KEY_NUMPAD_9,
    ETgPROP_KEY_NUMPAD_DECIMAL,     ETgPROP_KEY_NUMPAD_ENTER,       ETgPROP_KEY_NUMPAD_ADD,         ETgPROP_KEY_NUMPAD_SUBTRACT,    ETgPROP_KEY_NUMPAD_MULTIPLY,
    ETgPROP_KEY_NUMPAD_DIVIDE,

    /* Arrow Pad */
    ETgPROP_KEY_INSERT,             ETgPROP_KEY_HOME,               ETgPROP_KEY_PAGE_UP,            ETgPROP_KEY_DELETE,             ETgPROP_KEY_END,
    ETgPROP_KEY_PAGE_DOWN,          ETgPROP_KEY_UP,                 ETgPROP_KEY_DOWN,               ETgPROP_KEY_LEFT,               ETgPROP_KEY_RIGHT,

    /* Command Keys */
    ETgPROP_KEY_BACK,               ETgPROP_KEY_TAB,                ETgPROP_KEY_ESCAPE,             ETgPROP_KEY_ENTER,              ETgPROP_KEY_MAX
);

TgTYPE_ENUM(ETgPROP_GUI_KEYBOARD, TgSINT_E32,
    ETgPROP_GUI_KEY_MAX
);

TgTYPE_ENUM(ETgPROP_MOUSE, TgSINT_E32,
    /* Digital Controls */
    ETgPROP_MOUSE_BUTTON0,          ETgPROP_MOUSE_BUTTON1,          ETgPROP_MOUSE_BUTTON2,          ETgPROP_MOUSE_BUTTON3,          ETgPROP_MOUSE_BUTTON4,
    ETgPROP_MOUSE_BUTTON5,          ETgPROP_MOUSE_BUTTON6,          ETgPROP_MOUSE_BUTTON7,

    /* Analog Controls */
    ETgPROP_MOUSE_AXIX_DX,          ETgPROP_MOUSE_AXIX_DY,          ETgPROP_MOUSE_AXIX_DZ,          ETgPROP_MOUSE_MAX
);

TgTYPE_ENUM(ETgPROP_GUI_MOUSE, TgSINT_E32,
    /* Digital Controls */
    ETgPROP_GUI_MOUSE_BUTTON0,      ETgPROP_GUI_MOUSE_BUTTON1,      ETgPROP_GUI_MOUSE_BUTTON2,      ETgPROP_GUI_MOUSE_BUTTON3,      ETgPROP_GUI_MOUSE_BUTTON4,

    /* Analog Controls */
    ETgPROP_GUI_MOUSE_AXIX_DX,      ETgPROP_GUI_MOUSE_AXIX_DY,      ETgPROP_GUI_MOUSE_AXIX_DZ,      ETgPROP_GUI_MOUSE_MAX
);


/* ---- Controller State --------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_ENUM(ETgSTATE_GAMEPAD, TgSINT_E32,
    ETgSTATE_GAMEPAD_VALID                      = 1 << 0,
);

/* On systems that do not distinguish between left and right keys - the left key is the default. */
TgTYPE_ENUM(ETgSTATE_KEYBOARD, TgSINT_E32,
    ETgSTATE_KEYBOARD_VALID                     = 1 << 0,
    ETgSTATE_KEYBOARD_RCTRL                     = 1 << 1,
    ETgSTATE_KEYBOARD_LCTRL                     = 1 << 2,
    ETgSTATE_KEYBOARD_RSHIFT                    = 1 << 3,
    ETgSTATE_KEYBOARD_LSHIFT                    = 1 << 4,
    ETgSTATE_KEYBOARD_RALT                      = 1 << 5,
    ETgSTATE_KEYBOARD_LALT                      = 1 << 6,
    ETgSTATE_KEYBOARD_CAPSLOCK                  = 1 << 7,
    ETgSTATE_KEYBOARD_NUMLOCK                   = 1 << 8
);

TgTYPE_ENUM(ETgSTATE_GUI_KEYBOARD, TgSINT_E32,
    ETgSTATE_GUI_KEYBOARD_VALID                 = 1 << 0,
);

TgTYPE_ENUM(ETgSTATE_MOUSE, TgSINT_E32,
    ETgSTATE_MOUSE_VALID                        = 1 << 0,
);

TgTYPE_ENUM(ETgSTATE_GUI_MOUSE, TgSINT_E32,
    ETgSTATE_GUI_MOSUE_VALID                    = 1 << 0,
);


/* =============================================================================================================================================================================== */
#endif
