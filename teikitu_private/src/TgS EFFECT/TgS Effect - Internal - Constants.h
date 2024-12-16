/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Internal - Constants.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_EFFECT_INTERNAL_CONSTANTS_H)
#define TGS_EFFECT_INTERNAL_CONSTANTS_H
#pragma once


/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Global Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

enum { ETgFX_COMMAND__CLIENT_TO_UPDATE__BYTE_MAX      = 512*1024 };
enum { ETgFX_COMMAND__SCENE_TO_RENDER__BYTE_MAX       = 256*1024 };
enum { ETgFX_COMMAND__TO_CLIENT__BYTE_MAX             = 128*1024 };
enum { ETgFX_MAX_HEADER_INDEX                         = 2 };
enum { ETgFX_DATA__EFFECT_MAX                         = 512 };
enum { ETgFX_DECAL__VERTEX_MAX                        = 256 };

TgTYPE_ENUM( ETgFX_EFFECT_STATE, TgSINT_E32,

/*  ETgFX_EFFECT_STATE__SHARED */
    ETgFX_EFFECT_STATE__SHARED__BEGIN,

    ETgFX_EFFECT_STATE__SHARED__UNKNOWN = ETgFX_EFFECT_STATE__SHARED__BEGIN,

    ETgFX_EFFECT_STATE__SHARED__END,
    ETgFX_EFFECT_STATE__SHARED__MAX = ETgFX_EFFECT_STATE__SHARED__END,
    ETgFX_EFFECT_STATE__SHARED__COUNT = ETgFX_EFFECT_STATE__SHARED__END - ETgFX_EFFECT_STATE__SHARED__BEGIN,

/*  ETgFX_EFFECT_STATE__CLIENT */
    ETgFX_EFFECT_STATE__CLIENT__BEGIN = ETgFX_EFFECT_STATE__SHARED__END,

    ETgFX_EFFECT_STATE__CLIENT__FREE = ETgFX_EFFECT_STATE__CLIENT__BEGIN,
    ETgFX_EFFECT_STATE__CLIENT__RESERVED,
    ETgFX_EFFECT_STATE__CLIENT__INIT,
    ETgFX_EFFECT_STATE__CLIENT__ACTIVE,
    ETgFX_EFFECT_STATE__CLIENT__ACTIVE_INFINITE,

    ETgFX_EFFECT_STATE__CLIENT__END,
    ETgFX_EFFECT_STATE__CLIENT__MAX = ETgFX_EFFECT_STATE__CLIENT__END,
    ETgFX_EFFECT_STATE__CLIENT__COUNT = ETgFX_EFFECT_STATE__CLIENT__END - ETgFX_EFFECT_STATE__CLIENT__BEGIN,

/*  ETgFX_EFFECT_STATE__UPDATE */
    ETgFX_EFFECT_STATE__UPDATE__BEGIN = ETgFX_EFFECT_STATE__CLIENT__END,

    ETgFX_EFFECT_STATE__UPDATE__ACTIVE = ETgFX_EFFECT_STATE__UPDATE__BEGIN,
    ETgFX_EFFECT_STATE__UPDATE__ACTIVE_INFINITE,
    ETgFX_EFFECT_STATE__UPDATE__ACTIVE_FIRST,
    ETgFX_EFFECT_STATE__UPDATE__ACTIVE_WAITING_TO_DIE,

    ETgFX_EFFECT_STATE__UPDATE__END,
    ETgFX_EFFECT_STATE__UPDATE__MAX = ETgFX_EFFECT_STATE__UPDATE__END,
    ETgFX_EFFECT_STATE__UPDATE__COUNT = ETgFX_EFFECT_STATE__UPDATE__END - ETgFX_EFFECT_STATE__UPDATE__BEGIN,
);

TgTYPE_ENUM( ETgFX_COMMAND, TgSINT_E32,

    /* ETgFX_COMMAND__CLIENT_TO_UPDATE */
    ETgFX_COMMAND__CLIENT_TO_UPDATE__BEGIN,
    ETgFX_COMMAND__CLIENT_TO_UPDATE__NOTIFY = ETgFX_COMMAND__CLIENT_TO_UPDATE__BEGIN,
    ETgFX_COMMAND__CLIENT_TO_UPDATE__CREATE,
    ETgFX_COMMAND__CLIENT_TO_UPDATE__KILL,
    ETgFX_COMMAND__CLIENT_TO_UPDATE__STOP,
    ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_SET,
    ETgFX_COMMAND__CLIENT_TO_UPDATE__POSITION_UPDATE_FROM_PARENT,
    ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_SET,
    ETgFX_COMMAND__CLIENT_TO_UPDATE__ROTATION_UPDATE_FROM_PARENT,
    ETgFX_COMMAND__CLIENT_TO_UPDATE__SPIN,
    ETgFX_COMMAND__CLIENT_TO_UPDATE__VISIBLE,
    ETgFX_COMMAND__CLIENT_TO_UPDATE__END = ETgFX_COMMAND__CLIENT_TO_UPDATE__VISIBLE,

    /* ETgFX_COMMAND__SCENE_TO_RENDER */
    ETgFX_COMMAND__SCENE_TO_RENDER__BEGIN,
    ETgFX_COMMAND__SCENE_TO_RENDER__PATCH_CONTEXT = ETgFX_COMMAND__SCENE_TO_RENDER__BEGIN,
    ETgFX_COMMAND__SCENE_TO_RENDER__END = ETgFX_COMMAND__SCENE_TO_RENDER__PATCH_CONTEXT,

    /* ETgFX_COMMAND__UPDATE_TO_CLIENT */
    ETgFX_COMMAND__UPDATE_TO_CLIENT__BEGIN,
    ETgFX_COMMAND__UPDATE_TO_CLIENT__CREATE = ETgFX_COMMAND__UPDATE_TO_CLIENT__BEGIN,
    ETgFX_COMMAND__UPDATE_TO_CLIENT__FREE,
    ETgFX_COMMAND__UPDATE_TO_CLIENT__NOTIFY,
    ETgFX_COMMAND__UPDATE_TO_CLIENT__END = ETgFX_COMMAND__UPDATE_TO_CLIENT__NOTIFY,

    ETgFX_COMMAND__MAX
);

TgTYPE_ENUM( ETgFX_COMMAND__CLIENT_TO_UPDATE, TgSINT_E32,

    ETgFX_COMMAND__CLIENT_TO_UPDATE__MAX = ETgFX_COMMAND__CLIENT_TO_UPDATE__END,
    ETgFX_COMMAND__CLIENT_TO_UPDATE__COUNT = ETgFX_COMMAND__CLIENT_TO_UPDATE__END - ETgFX_COMMAND__CLIENT_TO_UPDATE__BEGIN,
);

TgTYPE_ENUM( ETgFX_COMMAND__SCENE_TO_RENDER, TgSINT_E32,

    ETgFX_COMMAND__SCENE_TO_RENDER__MAX = ETgFX_COMMAND__SCENE_TO_RENDER__END,
    ETgFX_COMMAND__SCENE_TO_RENDER__COUNT = ETgFX_COMMAND__SCENE_TO_RENDER__END - ETgFX_COMMAND__SCENE_TO_RENDER__BEGIN,
);

TgTYPE_ENUM( ETgFX_COMMAND__UPDATE_TO_CLIENT, TgSINT_E32,

    ETgFX_COMMAND__UPDATE_TO_CLIENT__MAX = ETgFX_COMMAND__UPDATE_TO_CLIENT__END,
    ETgFX_COMMAND__UPDATE_TO_CLIENT__COUNT = ETgFX_COMMAND__UPDATE_TO_CLIENT__END - ETgFX_COMMAND__UPDATE_TO_CLIENT__BEGIN,
);

TgTYPE_ENUM( ETgFX_NOTIFY, TgSINT_E32,

    ETgFX_NOTIFY__BEGIN,

    ETgFX_NOTIFY__UNKNOWN = ETgFX_NOTIFY__BEGIN,

    ETgFX_NOTIFY__FRAME_COMPLETE,
    ETgFX_NOTIFY__EFFECT_DISABLE,

    ETgFX_NOTIFY__END,
    ETgFX_NOTIFY__MAX = ETgFX_NOTIFY__END,
    ETgFX_NOTIFY__COUNT = ETgFX_NOTIFY__END - ETgFX_NOTIFY__BEGIN,
);

TgTYPE_ENUM( ETgFX_NEXT, TgSINT_E32,

    ETgFX_NEXT__BEGIN,

    ETgFX_NEXT__UPDATE = ETgFX_NEXT__BEGIN,
    ETgFX_NEXT__SCENE,
    ETgFX_NEXT__RENDER,

    ETgFX_NEXT__END,
    ETgFX_NEXT__MAX = ETgFX_NEXT__END,
    ETgFX_NEXT__COUNT = ETgFX_NEXT__END - ETgFX_NEXT__BEGIN,
);


/* =============================================================================================================================================================================== */
#endif

