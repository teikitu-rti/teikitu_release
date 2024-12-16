/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Constants.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_EFFECT_CONSTANTS_H)
#define TGS_EFFECT_CONSTANTS_H
#pragma once


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Macros                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TgBUILD_FEATURE__GRAPHICS)
#define TgBUILD_FEATURE__GRAPHICS_VFX
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- Effects ------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

TgTYPE_ENUM_FLAG( ETgFX_ANIM_DATA, TgSINT_F32,

    ETgFX_ANIM_DATA__INVALID,
    ETgFX_ANIM_DATA__CONSTANT_F32_04,
    ETgFX_ANIM_DATA__KEY_FRAME_F32_01,
    ETgFX_ANIM_DATA__KEY_FRAME_F32_02,
    ETgFX_ANIM_DATA__KEY_FRAME_F32_03,
    ETgFX_ANIM_DATA__KEY_FRAME_F32_04,
    ETgFX_ANIM_DATA__SIN_F32,
    ETgFX_ANIM_DATA__SQUARE_F32,
    ETgFX_ANIM_DATA__SPLINE_F32,
    ETgFX_ANIM_DATA__FLICKER_F32,
    ETgFX_ANIM_DATA__CONSTANT_UXX,
    ETgFX_ANIM_DATA__MAX,
);

TgTYPE_ENUM_FLAG( ETgFX__EFFECT, TgSINT_F32,

    ETgFX__INVALID,

    /* No Rendering (Client / Update) */
    ETgFX__GROUP,
    ETgFX__LIGHT,
    ETgFX__SOUND,

    /* Render Effects (Client / Update / Render) */
    ETgFX__BEAM,
    ETgFX__BILLBOARD,
    ETgFX__DECAL,
    ETgFX__EMITTER,
    ETgFX__POST,
    ETgFX__TRAIL,

    /* Effect Systems (Client / Update / System / Render) */
    ETgFX__GIB, /**< GIBs - Independent simulating geometry chunks */
    ETgFX__GLASS, /**< Glass - Fracture simulation and render */
    ETgFX__LIQUID, /**< Liquid Pools (Blood, Oil, Acid ... ) */

    ETgFX__EFFECT_MAX,
);


/* ---- Configuration ------------------------------------------------------------------------------------------------------------------------------------------------------------ */


enum { 
       /* Effects that execute on the client thread */
       KTgFX_MAX_LIGHT                      =   128,
       KTgFX_MAX_SOUND                      =   128,
       KTgFX_MAX_GROUP                      =  1024,

        /* Effects that execute on the render thread */
       KTgFX_MAX_BEAM                       =   128,
       KTgFX_MAX_BILLBOARD                  =   128,
       KTgFX_MAX_DECAL                      =   128,
       KTgFX_MAX_EMITTER                    =   128,
       KTgFX_MAX_POST                       =   128,
       KTgFX_MAX_TRAIL                      =   128,

       KTgFX_MAX_GIB                        =   128,
       KTgFX_MAX_GLASS                      =    32,
       KTgFX_MAX_LIQUID                     =   128,

       /* Maximum number of effects that can be rendered in one frame. */
       KTgFX_MAX_RENDER_INSTANCE            = KTgFX_MAX_BEAM
                                            + KTgFX_MAX_BILLBOARD
                                            + KTgFX_MAX_DECAL
                                            + KTgFX_MAX_EMITTER
                                            + KTgFX_MAX_POST
                                            + KTgFX_MAX_TRAIL
                                            + KTgFX_MAX_GIB
                                            + KTgFX_MAX_GLASS
                                            + KTgFX_MAX_LIQUID,

       /* Maximum number of effect instances supported by the system */
       KTgFX_MAX_EFFECT_INSTANCE            = KTgFX_MAX_RENDER_INSTANCE
                                            + KTgFX_MAX_LIGHT
                                            + KTgFX_MAX_SOUND
                                            + KTgFX_MAX_GROUP
};

/* Number of sub-effects supported by a group */
enum { KTgFX_MAX_GROUP_SUB_EFFECTS          =     8 };
enum { KTgFX_MAX_PARTICLE_FOR_EMITTER       =  8192 };
enum { KTgFX_MAX_POINTS_IN_TRAIL            =   128 };


/* ---- Effect Descriptors ------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_ENUM( ETgFX_BILLBOARD_ORIENTATION, TgSINT_F32,

    ETgFX_BILLBOARD_ORIENTATION__CAMERA_FACE_SPHERE,
    ETgFX_BILLBOARD_ORIENTATION__CAMERA_FACE_PLANE,
    ETgFX_BILLBOARD_ORIENTATION__CAMERA_FACE_SPHERE__FIXED_Y,
    ETgFX_BILLBOARD_ORIENTATION__CAMERA_FACE_PLANE__FIXED_Y,
    ETgFX_BILLBOARD_ORIENTATION__NONE
);

TgTYPE_ENUM( ETgFX_BILLBOARD_FLAGS, TgSINT_F32,

    ETgFX_BILLBOARD_FLAGS__HAS_FADE_ANGLE = 1 << 0,
);

TgTYPE_ENUM( ETgFX_EMISSION_SHAPE, TgSINT_F32,
/*  Emission Shape Type                        Emission Shape Vector */
    ETgFX_EMISSION_SHAPE__POINT,           /**< [-,-,-,-] Unused */
    ETgFX_EMISSION_SHAPE__SPHERE,          /**< [r,r,r,r] Radius */
    ETgFX_EMISSION_SHAPE__BOX,             /**< [x,y,z,-] X/Y/Z Extents from Emitter centre */
    ETgFX_EMISSION_SHAPE__DISK,            /**< [r,r,r,r] Radius, Standard Basis Vectors in Model Space */
    ETgFX_EMISSION_SHAPE__CIRCLE,          /**< [r,r,r,r] Radius, Standard Basis Vectors in Model Space */
    ETgFX_EMISSION_SHAPE__VELOCITY,        /**< [d,d,d,d] Distance to spawn in direction of velocity */
);

TgTYPE_ENUM( ETgFX_EMISSION_FLAGS, TgSINT_F32,

    ETgFX_EMITTER_FLAGS__EMISSION__POSITION_CURRENT_RELATIVE = 1 << 0,       /**< Relative to the Emitter */
    ETgFX_EMITTER_FLAGS__EMISSION__ROTATION_CURRENT_RELATIVE = 1 << 1,       /**< Relative to the Emitter */
    ETgFX_EMITTER_FLAGS__EMISSION__ROTATION_START_RELATIVE = 1 << 2,         /**< Relative to the Emitter */
    ETgFX_EMITTER_FLAGS__EMISSION__EMITTER_ATTRACTOR = 1 << 3,               /**< Emitter exerts a force on the particles */
    ETgFX_EMITTER_FLAGS__EMISSION__MESH_SET = 1 << 4,                        /**< Emitter uses mesh sets instead of particles / quads */
    ETgFX_EMITTER_FLAGS__EMISSION__PARTICLE_COLLIDE_STATIC_CACHED = 1 << 5,  /**< Particles collide against a triangle cache from static geometry */
    ETgFX_EMITTER_FLAGS__EMISSION__PARTICLE_COLLIDE_STATIC = 1 << 6,         /**< Particles collide against static geometry */
    ETgFX_EMITTER_FLAGS__EMISSION__PARTICLE_COLLIDE_FULL = 1 << 7,           /**< Particles collide against the entire world scene */

    ETgFX_EMITTER_FLAGS__PARTICLE_REFERENCE_FRAME_RECALC = 1 << 8,           /**< Reference Frame is calculated per particle instead of per emitter */

    ETgFX_EMITTER_FLAGS__EMISSION__PARTICLE_COLLIDE_MASK = 1 << 5 | 1 << 6 | 1 << 7,
);

TgTYPE_ENUM( ETgFX_PARTICLE_ORIENTATION, TgSINT_F32,

    ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_SPHERE,
    ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_PLANE,
    ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_SPHERE__FIXED_Y,
    ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_PLANE__FIXED_Y,
    ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_SPHERE__FIXED_XZ,
    ETgFX_PARTICLE_ORIENTATION__CAMERA_FACE_PLANE__FIXED_XZ,
    ETgFX_PARTICLE_ORIENTATION__VELOCITY_TANGENT,
    ETgFX_PARTICLE_ORIENTATION__SCREEN_SPACE,
    ETgFX_PARTICLE_ORIENTATION__NONE,
);

TgTYPE_ENUM( ETgFX_TRAIL_TYPE, TgSINT_F32,

    ETgFX_TRAIL_TYPE__TEX_PER_POINT,
    ETgFX_TRAIL_TYPE__TEX_PER_METER,
    ETgFX_TRAIL_TYPE__TEX_FIXED,
);

TgTYPE_ENUM( ETgFX_UPDATE, TgSINT_F32,

    ETgFX_UPDATE__BEGIN,

    ETgFX_UPDATE__DEFAULT = ETgFX_UPDATE__BEGIN,
    ETgFX_UPDATE__EXTERNAL,
    ETgFX_UPDATE__NEW_CLIENT,

    ETgFX_UPDATE__END,
    ETgFX_UPDATE__MAX = ETgFX_UPDATE__END,
    ETgFX_UPDATE__COUNT = ETgFX_UPDATE__END - ETgFX_UPDATE__BEGIN,
);

/* =============================================================================================================================================================================== */
#endif
