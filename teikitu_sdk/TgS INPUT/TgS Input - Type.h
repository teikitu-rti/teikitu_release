/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_INPUT_TYPE_H)
#define TGS_INPUT_TYPE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if !defined(TGS_INPUT_H)
#error This file should not be included directly - use the correct platform include wrapper
#endif

#include "TgS Ring 3 - Type.h"


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_IN_Event,)
{
    ETgCONTROLLER                               m_enController;

    union
    {
        TgUINT_E32                                  GamePad;
        TgUINT_E32                                  Keyboard;
        TgUINT_E32                                  GUI_Keyboard;
        TgUINT_E32                                  Mouse;
        TgUINT_E32                                  GUI_Mouse;
    }                                           m_uiState;

    union
    {
        ETgPROP_GAMEPAD                             GamePad;
        ETgPROP_KEYBOARD                            Keyboard;
        ETgPROP_GUI_KEYBOARD                        GUI_Keyboard;
        ETgPROP_MOUSE                               Mouse;
        ETgPROP_GUI_MOUSE                           GUI_Mouse;
    }                                           m_enProp;

    TgUINT_E32                                  m_uiUTF32;
    TgFLOAT32                                   m_fValue, m_fDiff;
};

typedef TgBOOL (*TgIN_FCN_CONSUMER)( TgUINT_PTR_C, TgFLOAT32_C, STg2_IN_Event_CPC );
typedef TgVOID (*TgIN_FCN_PRODUCER)( ETgCONTROLLER_C );
typedef TgRESULT (*TgIN_FCN_RUMBLE)( ETgCONTROLLER_C );


/* =============================================================================================================================================================================== */
#endif
