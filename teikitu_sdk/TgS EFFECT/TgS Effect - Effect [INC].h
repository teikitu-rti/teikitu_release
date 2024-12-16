/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Effect [INC].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined (ENABLE_RELOAD_GUARD_INC)

/** Effect Types
    Beam
    Billboard
    Decal
    Emitter
    Glass
    GIB
    Group
    Light
    Liquid
    Sound
    Trail */

#define ENABLE_RELOAD_GUARD_INC

/* Beam Effect */
#define T_NAME( A, ... ) A##Beam##__VA_ARGS__
#define T_TYPE( A, ... ) A##BEAM##__VA_ARGS__
#define T_TEXT( ... ) __VA_ARGS__ u8"Beam"
#include "TgS Effect - Effect [INC].h"

/* Billboard Effect */
#define T_NAME( A, ... ) A##Billboard##__VA_ARGS__
#define T_TYPE( A, ... ) A##BILLBOARD##__VA_ARGS__
#define T_TEXT( ... ) __VA_ARGS__ u8"Billboard"
#include "TgS Effect - Effect [INC].h"

/* Decal Effect */
#define T_NAME( A, ... ) A##Decal##__VA_ARGS__
#define T_TYPE( A, ... ) A##DECAL##__VA_ARGS__
#define T_TEXT( ... ) __VA_ARGS__ u8"Decal"
#define T_EFFECT_RENDER_PRIMITIVE_TYPE ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE
#include "TgS Effect - Effect [INC].h"

/* Emitter Effect */
#define T_NAME( A, ... ) A##Emitter##__VA_ARGS__
#define T_TYPE( A, ... ) A##EMITTER##__VA_ARGS__
#define T_TEXT( ... ) __VA_ARGS__ u8"Emitter"
#define T_EFFECT_TIME_DEFAULT 0
#define T_EFFECT_NOTIFY 1
#include "TgS Effect - Effect [INC].h"

/* Glass Effect */
#define T_NAME( A, ... ) A##Glass##__VA_ARGS__
#define T_TYPE( A, ... ) A##GLASS##__VA_ARGS__
#define T_TEXT( ... ) __VA_ARGS__ u8"Glass"
#define T_EFFECT_RENDER_PRIMITIVE_TYPE ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE
#include "TgS Effect - Effect [INC].h"

/* GIB Effect */
#define T_NAME( A, ... ) A##GIB##__VA_ARGS__
#define T_TYPE( A, ... ) A##GIB##__VA_ARGS__
#define T_TEXT( ... ) __VA_ARGS__ u8"GIB"
#define T_EFFECT_RENDER_PRIMITIVE_TYPE ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE
#include "TgS Effect - Effect [INC].h"

/* Group Effect */
#define T_NAME( A, ... ) A##Group##__VA_ARGS__
#define T_TYPE( A, ... ) A##GROUP##__VA_ARGS__
#define T_TEXT( ... ) __VA_ARGS__ u8"Group"
#define T_EFFECT_GROUP 1
#define T_EFFECT_TIME 0
#define T_EFFECT_SCENE 0
#define T_EFFECT_RENDER 0
#include "TgS Effect - Effect [INC].h"

/* Light Effect */
#define T_NAME( A, ... ) A##Light##__VA_ARGS__
#define T_TYPE( A, ... ) A##LIGHT##__VA_ARGS__
#define T_TEXT( ... ) __VA_ARGS__ u8"Light"
#define T_EFFECT_RENDER 0
#include "TgS Effect - Effect [INC].h"

/* Liquid Effect */
#define T_NAME( A, ... ) A##Liquid##__VA_ARGS__
#define T_TYPE( A, ... ) A##LIQUID##__VA_ARGS__
#define T_TEXT( ... ) __VA_ARGS__ u8"Liquid"
#define T_EFFECT_FRAME 0
#define T_EFFECT_RENDER_PRIMITIVE_TYPE ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE
#define T_EFFECT_PROCESS_COMMMAND 0
#include "TgS Effect - Effect [INC].h"

/* Post Effect */
#define T_NAME( A, ... ) A##Post##__VA_ARGS__
#define T_TYPE( A, ... ) A##POST##__VA_ARGS__
#define T_TEXT( ... ) __VA_ARGS__ u8"Post"
#define T_EFFECT_RENDER 0
#define T_EFFECT_FRAME 0
#define T_EFFECT_PROCESS_COMMMAND 0
#include "TgS Effect - Effect [INC].h"

/* Sound Effect */
#define T_NAME( A, ... ) A##Sound##__VA_ARGS__
#define T_TYPE( A, ... ) A##SOUND##__VA_ARGS__
#define T_TEXT( ... ) __VA_ARGS__ u8"Sound"
#define T_EFFECT_TIME 0
#define T_EFFECT_SCENE 0
#define T_EFFECT_RENDER 0
#include "TgS Effect - Effect [INC].h"

/* Trail Effect */
#define T_NAME( A, ... ) A##Trail##__VA_ARGS__
#define T_TYPE( A, ... ) A##TRAIL##__VA_ARGS__
#define T_TEXT( ... ) __VA_ARGS__ u8"Trail"
#define T_EFFECT_FRAME 0
#define T_EFFECT_TIME_DEFAULT 0
#define T_EFFECT_PROCESS_COMMMAND_DEFAULT 0
#include "TgS Effect - Effect [INC].h"

#undef ENABLE_RELOAD_GUARD_INC

#else

/** Error Checking */

#if !defined(__PARENT_FILE__)
#error Source Include file (template file) missing necessary definitions
/*# !defined(__PARENT_FILE__) */
#endif

#if !defined(T_NAME) || !defined(T_TYPE) || !defined(T_TEXT)
#error These should be defined in prior text of this file
/*# !defined(T_NAME) || !defined(T_TYPE) || !defined(T_TEXT) */
#endif

#if !defined(T_EFFECT_UPDATE)
#define T_EFFECT_UPDATE 1
/*# !defined(T_EFFECT_UPDATE) */
#endif

#if !defined(T_EFFECT_SCENE)
#define T_EFFECT_SCENE 1
/*# !defined(T_EFFECT_SCENE) */
#endif

#if !defined(T_EFFECT_RENDER)
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    #define T_EFFECT_RENDER 1
#else
    #define T_EFFECT_RENDER 0
#endif
/*# !defined(T_EFFECT_RENDER) */
#endif

#if !defined(T_EFFECT_RENDER_PRIMITIVE_TYPE)
#define T_EFFECT_RENDER_PRIMITIVE_TYPE ETgKN_GPU_EXT_TOPOLOGY_TYPE_TRIANGLE
/*# !defined(T_EFFECT_RENDER_PRIMITIVE_TYPE) */
#endif

#if !defined(T_EFFECT_RENDER_BATCH)
#define T_EFFECT_RENDER_BATCH 0
/*# !defined(T_EFFECT_RENDER_BATCH) */
#endif

#if !defined(T_EFFECT_GROUP)
#define T_EFFECT_GROUP 0
/*# !defined(T_EFFECT_GROUP) */
#endif

#if !defined(T_EFFECT_NOTIFY)
#define T_EFFECT_NOTIFY 0
/*# !defined(T_EFFECT_NOTIFY) */
#endif

#if !defined(T_EFFECT_TIME)
#define T_EFFECT_TIME (T_EFFECT_UPDATE && 1)
/*# !defined(T_EFFECT_TIME) */
#endif

#if !defined(T_EFFECT_TIME_DEFAULT)
#define T_EFFECT_TIME_DEFAULT (T_EFFECT_TIME && 1)
/*# !defined(T_EFFECT_TIME_DEFAULT) */
#endif

#if !defined(T_EFFECT_FRAME)
#define T_EFFECT_FRAME 1
/*# !defined(T_EFFECT_FRAME) */
#endif

#if !defined(T_EFFECT_PROCESS_COMMMAND)
#define T_EFFECT_PROCESS_COMMMAND 1
/*# !defined(T_EFFECT_PROCESS_COMMMAND) */
#endif

#if !defined(T_EFFECT_PROCESS_COMMMAND_DEFAULT)
#define T_EFFECT_PROCESS_COMMMAND_DEFAULT (T_EFFECT_PROCESS_COMMMAND && 1)
/*# !defined(T_EFFECT_PROCESS_COMMMAND_DEFAULT) */
#endif

#include __PARENT_FILE__

#undef T_EFFECT_PROCESS_COMMMAND_DEFAULT
#undef T_EFFECT_PROCESS_COMMMAND
#undef T_EFFECT_FRAME
#undef T_EFFECT_TIME_DEFAULT
#undef T_EFFECT_TIME
#undef T_EFFECT_NOTIFY
#undef T_EFFECT_GROUP
#undef T_EFFECT_RENDER_PRIMITIVE_TYPE
#undef T_EFFECT_RENDER
#undef T_EFFECT_SCENE
#undef T_EFFECT_UPDATE

#undef T_TEXT
#undef T_TYPE
#undef T_NAME

/*# !defined (ENABLE_RELOAD_GUARD) */
#endif
