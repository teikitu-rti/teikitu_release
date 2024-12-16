/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (NONE) Sound - System.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Sound ====================================================================================================================================================================== */

TgBOOL tgSN_Sound_Inst__Is_Valid( TgATTRIBUTE_UNUSED TgSN_INST_ID_C ARG0 ) { return false; } /* #IMPLEMENT */
TgSN_INST_ID tgSN_Sound_Inst__Init( TgATTRIBUTE_UNUSED TgSN_ID_C ARG0, TgATTRIBUTE_UNUSED STg2_SN_DESC_Sound_Inst_PCU ARG1 ) { return KTgSN_INST_ID__INVALID; } /* #IMPLEMENT */
TgVOID tgSN_Sound_Inst__Free( TgATTRIBUTE_UNUSED TgSN_INST_ID_C ARG0 ) {} /* #IMPLEMENT */
TgVOID tgSN_Sound_Inst__Set_Position( TgATTRIBUTE_UNUSED TgSN_INST_ID_C ARG0, TgATTRIBUTE_UNUSED TgVEC_F32_04_1_C ARG1 ) {} /* #IMPLEMENT */
TgVOID tgSN_Sound_Inst__Set_Direction( TgATTRIBUTE_UNUSED TgSN_INST_ID_C ARG0, TgATTRIBUTE_UNUSED TgVEC_F32_04_1_C ARG1 ) {} /* #IMPLEMENT */
TgRESULT tgSN_Sound_Inst__Event_Stop( TgATTRIBUTE_UNUSED TgSN_INST_ID_C ARG0 ) { return KTgE_FAIL; } /* #IMPLEMENT */
TgUINT_E32 tgSN_Sound__Release( TgATTRIBUTE_UNUSED TgSN_ID_C ARG0 ) { return 0; } /* #IMPLEMENT */
TgUINT_E32 tgSN_Sound_Bank__Release( TgATTRIBUTE_UNUSED TgSN_BANK_ID_C ARG0 ) { return 0; } /* #IMPLEMENT */
