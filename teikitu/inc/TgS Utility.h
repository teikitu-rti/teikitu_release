/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Utility.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_UTILITY_H)
#define TGS_UTILITY_H
#pragma once

#define TGS_PLATFORM_UTILITY_H

#include "TgS UTILITY/TgS Utility - Constants.h"
#include "TgS UTILITY/TgS Utility - Type.h"
#include "TgS UTILITY/TgS Utility - Data.h"


/* == Attachment ================================================================================================================================================================= */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Attachment Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgVOID                               tgAttachment__Increment_Reference( TgATTACHMENT_ID_C ); /* #IMPLEMENT */
TgEXTN TgVOID                               tgAttachment__Decrement_Reference( TgATTACHMENT_ID_C ); /* #IMPLEMENT */
TgEXTN TgBOOL                               tgAttachment__Is_Valid( TgATTACHMENT_ID_C ); /* #IMPLEMENT */
TgEXTN TgRESULT                             tgAttachment__Query_Attachment_W( TgVEC_F32_04_1_P, TgVEC_F32_04_1_P, TgATTACHMENT_ID_C, TgFLOAT32_C ); /* #IMPLEMENT */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Blend Functions                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgBOOL                               tgInterpolate_F32( TgFLOAT32_PCU, ETgUT_INTERPOLATE_C, TgFLOAT32_C, TgFLOAT32_C, TgFLOAT32_C );
TgEXTN TgBOOL                               tgInterpolate_F32_04_1( TgVEC_F32_04_1_PCU, ETgUT_INTERPOLATE_C, TgVEC_F32_04_1_C, TgVEC_F32_04_1_C, TgVEC_F32_04_1_C );


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Debug Draw Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if TgS_DEBUG__EFFECT

TgEXTN TgVOID                               tgDBG_Draw_CO_Request_F32_04__Primitive( STg2_CO_Request_F32_04_CPCU ); /* #IMPLEMENT */

                                            /* 1: Request */
                                            /* 2: Draw Text: Text description of contact point on screen */
TgEXTN TgVOID                               tgDBG_Draw_CO_Request_F32_04__Contacts( STg2_CO_Request_F32_04_CPCU, TgBOOL_C ); /* #IMPLEMENT */

                                            /* 1: Origin */
                                            /* 2: Start Velocity */
                                            /* 3: Forcefield */
                                            /* 4: Duration */
TgEXTN TgVOID                               tgDBG_Draw_Projectile( TgVEC_F32_04_1_C, TgVEC_F32_04_1_C, TgVEC_F32_04_1_C, TgFLOAT32_C ); /* #IMPLEMENT */

/*# TgS_DEBUG__EFFECT */
#endif

/* =============================================================================================================================================================================== */
#endif
