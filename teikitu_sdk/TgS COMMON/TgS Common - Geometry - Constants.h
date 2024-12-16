/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry - Constants.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_CONSTANTS_H)
#define TGS_COMMON_GEOMETRY_CONSTANTS_H
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_GEOMETRY Geometry Functions
    @ingroup TGS_COMMON
*/

/** @defgroup TGS_COMMON_GEOMETRY_BA Box, Axis-Aligned
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_BX Box
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_CP Capsule
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_CI Circle
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_CY Cylinder
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_EL Ellipse
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_LN Line
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_MA Mesh, BA
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_MB Mesh, BVT
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_MS Mesh, Simple
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_PE Parallelogram
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_PC Particle
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_PN Plane
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_RY Ray
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_RT Rectangle
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_SG Segment
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_SP Sphere
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_TS Torus
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_CT Triangle, Collision
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_ET Triangle, Edge
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_PT Triangle, Point
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_ST Triangle, Space
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_TB Tube
    @ingroup TGS_COMMON_GEOMETRY
*/

/** @defgroup TGS_COMMON_GEOMETRY_RT2D Rectangle, 2D
    @ingroup TGS_COMMON_GEOMETRY
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Enumerations ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_ENUM( ETgPRIMITIVE, TgSINT_E32,

    ETgPRIMITIVE_UNKNOWN = 0,

    /* 0D Objects in 3D, Points   */
    ETgPOINT,               /* VT */
    ETgPARTICLE,            /* PC */

    /* 1D Objects in 3D, Lines    */
    ETgLINE,                /* LN */
    ETgRAY,                 /* RY */
    ETgSEGMENT,             /* SG */

    /* 2D Objects in 2D, Surfaces */
    ETgRECTANGLE2D,         /* RT */
    ETgELLIPSE2D ,          /* EL */

    /* 2D Objects in 3D, Surfaces */
    ETgCIRCLE,              /* CI */
    ETgDISK,                /* DK */
    ETgELLIPSE,             /* EL */
    ETgPARALLELOGRAM,       /* PE */
    ETgPLANE,               /* PN */
    ETgRECTANGLE,           /* RT */
    ETgPTRI,                /* PT */
    ETgETRI,                /* ET */
    ETgCTRI,                /* CT */
    ETgSTRI,                /* ST */

    /* 3D Objects, Volumes        */
    ETgBOXAA,               /* BA */
    ETgBOX,                 /* BX */
    ETgCAPSULE,             /* CP */
    ETgCONE,                /* CE */
    ETgCYLINDER,            /* CY */
    ETgFRUSTRUM,            /* FT */
    ETgMESH_SIMPLE,         /* MS */
    ETgMESH_BVT,            /* MB */
    ETgMESH_BA,             /* MA */
    ETgSPHERE,              /* SP */
    ETgTETRAHEDRON,         /* TN */
    ETgTORUS,               /* TS */
    ETgTUBE,                /* TB */

    ETgPRIMITIVE_MAX
);


TgTYPE_ENUM( ETgPM_SHORT, TgSINT_E32,

    ETgPM_UNKNOWN = 0,

    /* 0D Objects in 3D, Points   */
    ETgPM_VT,
    ETgPM_PC,

    /* 1D Objects in 3D, Lines    */
    ETgPM_LN,
    ETgPM_RY,
    ETgPM_SG,

    /* 2D Objects in 2D, Surfaces */
    ETgPM_RT2D,
    ETgPM_EL2D,

    /* 2D Objects in 3D, Surfaces */
    ETgPM_CI,
    ETgPM_DK,
    ETgPM_EL,
    ETgPM_PE,
    ETgPM_PN,
    ETgPM_RT,
    ETgPM_PT,
    ETgPM_ET,
    ETgPM_CT,
    ETgPM_ST,

    /* 3D Objects, Volumes        */
    ETgPM_BA,
    ETgPM_BX,
    ETgPM_CP,
    ETgPM_CE,
    ETgPM_CY,
    ETgPM_FT,
    ETgPM_MS,
    ETgPM_MB,
    ETgPM_MA,
    ETgPM_SP,
    ETgPM_TN,
    ETgPM_TS,
    ETgPM_TB,

    ETgPM_MAX
);


TgTYPE_ENUM( ETgSWEEP_TYPE, TgSINT_E32,
    ETgSWEEP_STATIC,                ETgSWEEP_LINEAR,                ETgSWEEP_ROTATIONAL
);

TgTYPE_ENUM( ETgFRUSTUM_PLANE, TgSINT_E32,
    ETgFRUSTUM_PLANE__NEAR,         ETgFRUSTUM_PLANE__FAR,          ETgFRUSTUM_PLANE__LEFT,         ETgFRUSTUM_PLANE__RIGHT,        ETgFRUSTUM_PLANE__TOP,
    ETgFRUSTUM_PLANE__BOTTOM,       ETgFRUSTUM_PLANE__MAX
);


/* ---- Constants ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgUINT_E16_C                         KTgGM_CUBE_P_INDEX[36];
TgEXTN TgVEC_UN_F32_04_1_C                  KTgGM_CUBE_P_INDEX_VERTEX[8];
TgEXTN TgVEC_UN_F32_04_1_C                  KTgGM_CUBE_PN_TRI_LIST_VERTEX[72];

TgEXTN TgUINT_E16_C                         KTgGM_TETRAHEDRON_P_INDEX[12];
TgEXTN TgVEC_UN_F32_04_1_C                  KTgGM_TETRAHEDRON_P_VERTEX[4];

TgEXTN TgUINT_E16_C                         KTgGM_OCTOGON_P_INDEX[24];
TgEXTN TgVEC_UN_F32_04_1_C                  KTgGM_OCTOGON_P_INDEX_VERTEX[6];

TgEXTN TgUINT_E16_C                         KTgGM_ICOSAHEDRON_PN_INDEX[60];
TgEXTN TgVEC_UN_F32_04_1_C                  KTgGM_ICOSAHEDRON_PN_INDEX_VERTEX[24];

TgEXTN TgUINT_E16_C                         KTgGM_ICOSAHEDRON_CAPSULE_FULL_PN_INDEX[12*3*3];
TgEXTN TgVEC_UN_F32_04_1_C                  KTgGM_ICOSAHEDRON_CAPSULE_PN_INDEX_VERTEX[40];


/* =============================================================================================================================================================================== */
#endif
