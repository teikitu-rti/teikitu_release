/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Set - Constants.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_SET_CONSTANTS_H)
#define TGS_SET_CONSTANTS_H
#pragma once


/* == Set ======================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

enum { KTgSE_MAX_LIGHT                      =    512 };
enum { KTgSE_MAX_INSTANCE                   =   8192 };
enum { KTgSE_MAX_OBJECT                     =    512 };

enum { KTgSE_MAX_CAMERA                     =     16 };
enum { KTgSE_MAX_VIEW                       =      8 };

enum { KTgSE_DRAW_MESH_INST__MAX            =  0xFFFF};


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_ENUM(ETgSE_DRAW_TYPE, TgSINT_E32,

    ETgSE_DRAW_TYPE__BEGIN,

    ETgSE_DRAW_TYPE__OPAQUE = ETgSE_DRAW_TYPE__BEGIN,
    ETgSE_DRAW_TYPE__TRANSPARENT,
    ETgSE_DRAW_TYPE__TARGET,

    ETgSE_DRAW_TYPE__END,
    ETgSE_DRAW_TYPE__MAX = ETgSE_DRAW_TYPE__END,
    ETgSE_DRAW_TYPE__COUNT = ETgSE_DRAW_TYPE__END - ETgSE_DRAW_TYPE__BEGIN,
);

TgTYPE_ENUM(ETgSE_CHANNEL, TgSINT_E32,

    ETgSE_CHANNEL__UNKNOWN,         ETgSE_CHANNEL__PICKING,         ETgSE_CHANNEL__SET,             ETgSE_CHANNEL__DEBRIS,          ETgSE_CHANNEL__EFFECT,
    ETgSE_CHANNEL__CHARACTER,       ETgSE_CHANNEL__RAG_DOLL,        ETgSE_CHANNEL__MAX,
);


/* =============================================================================================================================================================================== */
#endif
