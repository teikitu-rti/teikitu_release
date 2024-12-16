/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input - Internal - Data.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_INPUT_INTERNAL_DATA_H)
#define TGS_INPUT_INTERNAL_DATA_H
#pragma once

#include "TgS Input - Internal - Type.h"


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN STg2_Input_Producer                  g_asController_Active[ETgCONTROLLER_MAX];
TgEXTN STg2_Input_Rumble                    g_asController_Rumble[ETgCONTROLLER_MAX];
TgEXTN STg2_Input_Consumer                  g_asConsumer[KTgMAX_CONSUMER];
TgEXTN TgBOOL                               g_abController_Paused[ETgCONTROLLER_MAX];
TgEXTN STg2_UT_LF__ST                       g_sConsumer_Insert;

TgEXTN TgFLOAT32                            g_fDefault_Mouse_X_Dead_Zone;
TgEXTN TgFLOAT32                            g_fDefault_Mouse_Y_Dead_Zone;
TgEXTN TgFLOAT32                            g_fDefault_Mouse_Z_Dead_Zone;

TgEXTN TgFLOAT32                            g_fDefault_GamePad_Stick_0_X_Dead_Zone;
TgEXTN TgFLOAT32                            g_fDefault_GamePad_Stick_0_Y_Dead_Zone;
TgEXTN TgFLOAT32                            g_fDefault_GamePad_Stick_1_X_Dead_Zone;
TgEXTN TgFLOAT32                            g_fDefault_GamePad_Stick_1_Y_Dead_Zone;

TgEXTN TgFLOAT32                            g_fGamePad_Stick_Dead_Zone[4][4];
TgEXTN TgFLOAT32                            g_fMouse_Dead_Zone[2][3];

#if TgS_STAT__INPUT
TgEXTN TgUINT_F32                           g_nuiStat_Insert[ETgCONTROLLER_MAX + 1], g_nuiStat_Remove[ETgCONTROLLER_MAX + 1];
#endif


/* =============================================================================================================================================================================== */
#endif
