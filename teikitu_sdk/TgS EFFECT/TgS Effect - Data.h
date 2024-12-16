/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Data.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_EFFECT_DATA_H)
#if !defined (ENABLE_RELOAD_GUARD)


/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Profile Markers                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

PROFILE_EXTERN( FX_COMMANDS__CLIENT );
PROFILE_ARRAY_EXTERN( ETgFX_UPDATE__MAX + 1, FX_UPDATE__UPDATE );
PROFILE_EXTERN( FX_RENDER_PATCH_CONTEXT );
PROFILE_EXTERN( FX_RENDER_PROCESS_COMMANDS );
PROFILE_EXTERN( FX_RENDER_GENERATE );

#if TgS_DEBUG__EFFECT
TgEXTN TgCN_VAR_ID                          g_tiFX_Debug__Emitter__Draw_Debug_Colour;
/*# TgS_DEBUG__EFFECT */
#endif

#define __PARENT_FILE__ "TgS Effect - Data.h"
#define ENABLE_RELOAD_GUARD
#include "TgS Effect - Effect [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_EFFECT_DATA_H

/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Profile Markers and Console Variables                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

PROFILE_EXTERN( T_TYPE(FX_,_COMMANDS__UPDATE) );

#if T_EFFECT_UPDATE
PROFILE_EXTERN( T_TYPE(FX_,_UPDATE__DATA) );
PROFILE_EXTERN( T_TYPE(FX_,_UPDATE_EXTERNAL__DATA) );
PROFILE_ARRAY_EXTERN( ETgFX_UPDATE__MAX + 1, T_TYPE(FX_, _UPDATE__UPDATE) );
/*# T_EFFECT_UPDATE */
#endif

#if T_EFFECT_SCENE
PROFILE_ARRAY_EXTERN( ETgFX_UPDATE__MAX, T_TYPE(FX_,_SCENE__CULL) );
PROFILE_EXTERN( T_TYPE(FX_,_SCENE__CULL_TOTAL) );
PROFILE_ARRAY_EXTERN( ETgFX_UPDATE__MAX, T_TYPE(FX_,_SCENE__UPDATE_BA) );
PROFILE_EXTERN( T_TYPE(FX_,_SCENE__UPDATE_BA_TOTAL) );
PROFILE_EXTERN( T_TYPE(FX_,_SCENE__FINISH_TOTAL) );
/*# T_EFFECT_SCENE */
#endif

#if T_EFFECT_RENDER
PROFILE_ARRAY_EXTERN( ETgFX_UPDATE__MAX, T_TYPE(FX_,_RENDER__PROCESS_HEADERS) );
PROFILE_EXTERN( T_TYPE(FX_,_RENDER__PROCESS_HEADERS_TOTAL) );
PROFILE_EXTERN( T_TYPE(FX_,_RENDER_PATCH_CONTEXT) );
PROFILE_EXTERN( T_TYPE(FX_,_RENDER_UPDATE) );
PROFILE_EXTERN( T_TYPE(FX_,_RENDER__GENERATE) );
/*# T_EFFECT_RENDER */
#endif

#if TgS_DEBUG__EFFECT
TgEXTN TgCN_VAR_ID                          T_NAME(g_tiFX_Debug__,__Disable_Create);
TgEXTN TgCN_VAR_ID                          T_NAME(g_tiFX_Debug__,__Disable_Update);
TgEXTN TgCN_VAR_ID                          T_NAME(g_tiFX_Debug__,__Disable_Scene_Cull);
TgEXTN TgCN_VAR_ID                          T_NAME(g_tiFX_Debug__,__Disable_Render);
TgEXTN TgCN_VAR_ID                          T_NAME(g_tiFX_Debug__,__Draw_BA);
TgEXTN TgCN_VAR_ID                          T_NAME(g_tiFX_Debug__,__Draw_Debug);
/*# TgS_DEBUG__EFFECT */
#endif


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/*# !defined(TGS_EFFECT_DATA_H) */
#endif
