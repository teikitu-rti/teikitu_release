/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Ring 3 - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_RING_3_TYPE_H)
#define TGS_RING_3_TYPE_H
#pragma once

#include "TgS Ring 2 - Type.h"


/* == Ring 3 ===================================================================================================================================================================== */

/* Reference Frames
   _N Root Reference Frame (no transformation).
   _I Inertial Reference Frame - Root Reference Frame that has been rotated (but not translated) to match the World Reference Frame.
   _B Body Reference Frame - Root reference frame that has been rotated and translated into a parent reference frame.
   _W World Reference Frame  - Root Reference Frame that has been translated and rotated into a world (or set).
   _V View Reference Frame - The reference frame based on a camera.
   _P Projected Reference Frame */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  System ID                                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Animation System */
TgKI_DECLARE( AM_FILE_ID ) /* #IMPLEMENT */
TgKI_DECLARE( AM_KEY_FRAME_ANIM_DATA_ID ) /* #IMPLEMENT */
TgKI_DECLARE( AM_KEY_FRAME_ANIM_INST_ID ) /* #IMPLEMENT */
TgKI_DECLARE( AM_MORPH_TARGET_DATA_ID ) /* #IMPLEMENT */
TgKI_DECLARE( AM_MORPH_TARGET_INST_ID ) /* #IMPLEMENT */
TgKI_DECLARE( AM_SKELETON_DATA_ID ) /* #IMPLEMENT */
TgKI_DECLARE( AM_SKELETON_INST_ID ) /* #IMPLEMENT */
TgKI_DECLARE( AM_SKELETON_ANIM_DATA_ID ) /* #IMPLEMENT */
TgKI_DECLARE( AM_SKELETON_ANIM_INST_ID ) /* #IMPLEMENT */
TgKI_DECLARE( AM_MACHINE_DATA_ID ) /* #IMPLEMENT */
TgKI_DECLARE( AM_MACHINE_INST_ID ) /* #IMPLEMENT */
TgKI_DECLARE( AM_MACHINE_VAR_ID ) /* #IMPLEMENT */
TgKI_DECLARE( AM_MACHINE_STATE_ID ) /* #IMPLEMENT */

/* Attachment System */
TgKI_DECLARE( ATTACHMENT_ID ) /* #IMPLEMENT */

/* Input System */
TgKI_DECLARE( IN_CONSUMER_ID )

/* Physics System */

/* Render System */
TgKI_DECLARE( RN_MAT_TYPE_ID ) /* #IMPLEMENT */
TgKI_DECLARE( RN_MATERIAL_ID ) /* #IMPLEMENT */
TgKI_DECLARE( RN_TEXTURE_ID ) /* #IMPLEMENT */
TgKI_DECLARE( RN_TARGET_ID ) /* #IMPLEMENT */
TgKI_DECLARE( RN_MESH_ID ) /* #IMPLEMENT */
TgKI_DECLARE( RN_MESH_SET_ID ) /* #IMPLEMENT */
TgKI_DECLARE( RN_CONTEXT_ID ) /* #IMPLEMENT */

/* Sound System */
TgKI_DECLARE( SN_BANK_ID ) /* #IMPLEMENT */
TgKI_DECLARE( SN_ID ) /* #IMPLEMENT */
TgKI_DECLARE( SN_INST_ID ) /* #IMPLEMENT */


/* =============================================================================================================================================================================== */
#endif
