/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Constants.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_CONSTANTS_H)
#define TGS_COLLISION_CONSTANTS_H
#pragma once


/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COLLISION Collision Module and Functions
*/

/** @defgroup TGS_COLLISION_BA Box, Axis-Aligned
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_BX Box
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_CP Capsule
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_CI Circle
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_CY Cylinder
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_EL Ellipse
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_LN Line
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_MA Mesh, BA
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_MB Mesh, BVT
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_MS Mesh, Simple
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_PE Parallelogram
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_PC Particle
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_PN Plane
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_RY Ray
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_RT Rectangle
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_SG Segment
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_SP Sphere
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_TS Torus
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_TRIANGLE Triangle
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_CT Triangle, Collision
    @ingroup TGS_COLLISION_TRIANGLE
*/

/** @defgroup TGS_COLLISION_ET Triangle, Edge
    @ingroup TGS_COLLISION_TRIANGLE
*/

/** @defgroup TGS_COLLISION_PT Triangle, Point
    @ingroup TGS_COLLISION_TRIANGLE
*/

/** @defgroup TGS_COLLISION_ST Triangle, Space
    @ingroup TGS_COLLISION_TRIANGLE
*/

/** @defgroup TGS_COLLISION_TB Tube
    @ingroup TGS_COLLISION
*/

/** @defgroup TGS_COLLISION_RT2D Rectangle, 2D
    @ingroup TGS_COLLISION
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Constants                                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

enum
{
    KTgCO_REQUEST__INTERNAL_RESULTS = 8
};

enum
{
    KTgCO_REQUEST__MAX_IGNORE = 32
};

TgTYPE_ENUM(ETgCO_PURPOSE, TgSINT_F32,

    ETgCO_PURPOSE__UNDEFINED,
    ETgCO_PURPOSE__LINE_OF_SIGHT,
    ETgCO_PURPOSE__DAMAGE,
    ETgCO_PURPOSE__SHADOW,
    ETgCO_PURPOSE__CAMERA_COLLISION,
    ETgCO_PURPOSE__BULLET,
    ETgCO_PURPOSE__DECAL,
    ETgCO_PURPOSE__MOUSE,
    ETgCO_PURPOSE__FLOORHEIGHT,
    ETgCO_PURPOSE__PHYSICS,
    ETgCO_PURPOSE__PATHFINDING,
    ETgCO_PURPOSE__RAY_CAST,

    ETgCO_PURPOSE__MAX
);

TgTYPE_ENUM(ETgCO_FILTER, TgSINT_F32,

    ETgCO_FILTER__NONE = 1 << 0,
    ETgCO_FILTER__ACTOR = 1 << 1,
    ETgCO_FILTER__STATIC_HIGH = 1 << 2,
    ETgCO_FILTER__STATIC_LOW = 1 << 3,
    ETgCO_FILTER__LIGHT = 1 << 4,
    ETgCO_FILTER__LIGHT_PROBE = 1 << 5,
    ETgCO_FILTER__PATH_POINT = 1 << 6,
    ETgCO_FILTER__PHYSICS = 1 << 7,
    ETgCO_FILTER__RAG_DOLL = 1 << 8,
    ETgCO_FILTER__WATER = 1 << 9,
    ETgCO_FILTER__RENDER = 1 << 10,

    ETgCO_FILTER__EDITOR__DRAFT = 1u << 30,
);

TgTYPE_ENUM(ETgCO_INTERFACE, TgSINT_F32,

    ETgCO_INTERFACE__FAIL,
    ETgCO_INTERFACE__INTERSECTION,
    ETgCO_INTERFACE__NONE,
    ETgCO_INTERFACE__CONTAINED,

    ETgCO_INTERFACE__MAX
);

TgTYPE_ENUM(ETgCO_TEST, TgSINT_F32,

    ETgCO_TEST__UNKNOWN,
    ETgCO_TEST__DIST,
    ETgCO_TEST__CLOSEST,
    ETgCO_TEST__BOOLEAN,
    ETgCO_TEST__BOOLEAN_SWEEP,
    ETgCO_TEST__INTERSECT,
    ETgCO_TEST__PENETRATE,
    ETgCO_TEST__SWEEP,
    ETgCO_TEST__SWEEP_PENETRATE,

    ETgCO_TEST__COLLECT, /* ETgCO_TEST__BOOLEAN */

    ETgCO_TEST__MAX
);

TgTYPE_ENUM(ETgCO_AXIS_CONTACT_DIRECTION, TgSINT_F32,

    ETgCO_AXIS_CONTACT_DIRECTION__UNKNOWN,
    ETgCO_AXIS_CONTACT_DIRECTION__POSITIVE,
    ETgCO_AXIS_CONTACT_DIRECTION__NEGATIVE,
    ETgCO_AXIS_CONTACT_DIRECTION__PENETRATED
);

/* Intersection tests results are kept in both the time and depth values.  This allows the user to select the ability to retain results that are closest to the origin or */
/* furthest from the origin. */

/* ETg_FLAGS_NOSORT is TRUE: */
/*   Result buffer is filled to capacity and then all further results are ignored. */

/* ETg_FLAGS_NOSORT is FALSE: */
/*   ETg_FLAGS_ORDER_PARAMETER is TRUE: Retain results that have the largest penetration depths. */
/*   ETg_FLAGS_ORDER_PARAMETER is FALSE: Retains results that are closest to a zero time result. */

TgTYPE_ENUM(ETgCO_REQUEST_CONFIG, TgSINT_F32,

    ETgCO_FLAGS_IGNORE_ALL = 1 << 0,
    ETgCO_FLAGS_OWNS_DATA = 1 << 1,
    ETgCO_FLAGS_NO_SORT = 1 << 2,
    ETgCO_FLAGS_ORDER_PARAMETER = 1 << 3, /**< Depth or Time sort parameter */
);

#define OK_PROC( A, B )
#define WARN_PROC( A, B )       ETgRET_CODE__##A,
#define ERROR_PROC( A, B )      ETgRET_CODE__##A,

typedef enum
{
    #include "TgS COLLISION/TgS Errors.TgS"
} ETgCOLLISION_RETURN_CODE__ERROR;
TgTYPE_MODIFIER_DEFAULT(ETgCOLLISION_RETURN_CODE__ERROR);

#define OK_PROC( A, B )         enum { KTgS_##A =  MAKE_TgRESULT( B, ETgRET_CODE__##A ) };
#define WARN_PROC( A, B )       enum { KTgW_##A = -MAKE_TgRESULT( B, ETgRET_CODE__##A ) };
#define ERROR_PROC( A, B )      enum { KTgE_##A = -MAKE_TgRESULT( B, ETgRET_CODE__##A ) };

#include "TgS COLLISION/TgS Errors.TgS"


/* =============================================================================================================================================================================== */
#endif

