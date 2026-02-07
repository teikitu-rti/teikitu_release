/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (MAC) Input - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined(TGS_MAC_INPUT_INTERNAL_H)
#define TGS_MAC_INPUT_INTERNAL_H

#include "TgS Input - Internal.h"

#if !defined(TgBUILD_OS__MAC)
#error This file should only be included for MAC platforms
#endif

#include "TgS COMMON/TgS (MAC) Common - Base - Include.h"
#include "TgS COMMON/TgS (MAC) Common - Global.h"
#include "TgS KERNEL/TgS (MAC) Kernel - Constants.h"
#include "TgS KERNEL/TgS (MAC) Kernel.h"

#include "TgS (MAC) Input - Internal - Data.h"

#include "TgS COMMON/TgS Common.inl"


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgRESULT
tgIN_PM_Init_Function_Table( TgVOID );


TgEXTN TgRESULT
tgIN_PM_Init_GamePad( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Boot_GamePad( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Stop_GamePad( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Free_GamePad( TgVOID );

TgEXTN TgVOID
tgIN_PM_Update_GamePad(
    ETgCONTROLLER_C );

TgEXTN TgRSIZE
tgIN_PM_Query_Fixed_Memory_GamePad( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Set_GamePad_Rumble(
    ETgCONTROLLER_C, TgFLOAT32_C, TgFLOAT32_C );


TgEXTN TgRESULT
tgIN_PM_Init_GUI_Keyboard( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Boot_GUI_Keyboard( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Stop_GUI_Keyboard( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Free_GUI_Keyboard( TgVOID );

TgEXTN TgVOID
tgIN_PM_Update_GUI_Keyboard(
    ETgCONTROLLER_C );

TgEXTN TgRSIZE
tgIN_PM_Query_Fixed_Memory_GUI_Keyboard( TgVOID );


TgEXTN TgRESULT
tgIN_PM_Init_GUI_Mouse( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Boot_GUI_Mouse( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Stop_GUI_Mouse( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Free_GUI_Mouse( TgVOID );

TgEXTN TgVOID
tgIN_PM_Update_GUI_Mouse(
    ETgCONTROLLER_C );

TgEXTN TgRSIZE
tgIN_PM_Query_Fixed_Memory_GUI_Mouse( TgVOID );


TgEXTN TgRESULT
tgIN_PM_Init_Mouse( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Boot_Mouse( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Stop_Mouse( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Free_Mouse( TgVOID );

TgEXTN TgVOID
tgIN_PM_Update_Mouse(
    ETgCONTROLLER_C );

TgEXTN TgRSIZE
tgIN_PM_Query_Fixed_Memory_Mouse( TgVOID );


TgEXTN TgRESULT
tgIN_PM_Init_Keyboard( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Boot_Keyboard( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Stop_Keyboard( TgVOID );

TgEXTN TgRESULT
tgIN_PM_Free_Keyboard( TgVOID );

TgEXTN TgVOID
tgIN_PM_Update_Keyboard(
    ETgCONTROLLER_C );

TgEXTN TgRSIZE
tgIN_PM_Query_Fixed_Memory_Keyboard( TgVOID );


/* =============================================================================================================================================================================== */
#endif
