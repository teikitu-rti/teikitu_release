/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Sound [Stub].h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_SOUND_H)
#define TGS_SOUND_H
#pragma once

#define TGS_PLATFORM_SOUND_H


/* == Sound ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_SN_DESC_Sound_Inst,)
{
    TgVEC_F32_04_1                              m_vPosition;
    TgVEC_F32_04_1                              m_vDirection;
    TgVEC_F32_04_1                              m_vVelocity;

    TgFLOAT32                                   m_fTime_To_Fail; /**< Time to wait for load completion before skipping the request */
    TgFLOAT32                                   m_fFade_In; /**< Time spent fading in the sound */
    TgUINT_E32                                  m_uiCategory; /**< A user category value used for sound grouping */
    TgBOOL                                      m_bMix;
    TgUINT_E08                                  m_uiPad[3];

    TgUINT_PTR                                  m_uiCall_Back_Param; /**< Extra parameter passed to the call back */
    TgVOID                                      (*m_pfnCall_Back)( TgUINT_PTR_C, TgSN_INST_ID_C );
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgINLINE TgRESULT
tgSN_Module_Init( TgVOID ) { return KTgS_OK; };

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgINLINE TgRESULT
tgSN_Module_Boot( TgVOID ) { return KTgS_OK; };

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgINLINE TgVOID
tgSN_Module_Stop( TgVOID ) {};

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgINLINE TgVOID
tgSN_Module_Free( TgVOID ) {};

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgINLINE TgRESULT
tgSN_Module_Update(
    TgFLOAT32_C UNUSED_PARAM ARG0 ) { return KTgS_OK; };


/** @brief Standard Module functions: Set the current configuration of the module. */
TgINLINE TgRESULT
tgSN_Load_Config( TgVOID ) { return KTgS_OK; };

/** @brief Standard Module function: Save the current configuration of the module. */
TgINLINE TgRESULT
tgSN_Save_Config( TgVOID ) { return KTgS_OK; };


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgINLINE TgBOOL
tgSN_Query_Init( TgVOID ) { return true; };

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgINLINE TgBOOL
tgSN_Query_Boot( TgVOID ) { return true; };

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgINLINE TgRSIZE
tgSN_Query_Fixed_Memory( TgVOID ) { return 0u; };




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Sound Functions                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgINLINE TgUINT_F32                           tgSN_Sound_Bank__Release( TgSN_BANK_ID_C UNUSED_PARAM ARG0 ) { return 0; };
TgINLINE TgUINT_F32                           tgSN_Sound__Release( TgSN_ID_C UNUSED_PARAM ARG0 ) { return 0u; };
TgINLINE TgSN_INST_ID                         tgSN_Sound_Inst__Init( TgSN_ID_C UNUSED_PARAM ARG0, STg2_SN_DESC_Sound_Inst_PCU UNUSED_PARAM ARG1 ) { return KTgSN_INST_ID__INVALID; };
TgINLINE TgVOID                               tgSN_Sound_Inst__Free( TgSN_INST_ID_C UNUSED_PARAM ARG0 ) {};
TgINLINE TgRESULT                             tgSN_Sound_Inst__Event_Stop( TgSN_INST_ID_C UNUSED_PARAM ARG0 ) { return KTgS_OK; };
TgINLINE TgBOOL                               tgSN_Sound_Inst__Is_Valid( TgSN_INST_ID_C UNUSED_PARAM ARG0 ) { return false; };
TgINLINE TgVOID                               tgSN_Sound_Inst__Set_Position( TgSN_INST_ID_C UNUSED_PARAM ARG0, TgVEC_F32_04_1_C UNUSED_PARAM ARG1 ) {};
TgINLINE TgVOID                               tgSN_Sound_Inst__Set_Direction( TgSN_INST_ID_C UNUSED_PARAM ARG0, TgVEC_F32_04_1_C UNUSED_PARAM ARG1 ) {};


/* =============================================================================================================================================================================== */
#endif
