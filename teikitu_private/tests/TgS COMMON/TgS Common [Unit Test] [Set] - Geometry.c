/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Set] - Geometry.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined (TGS_COMMON_GEOMETRY_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Common ===================================================================================================================================================================== */

TgVOID                                      FCN_V(UNIT_TEST__SETUP__EL)( VEC_OBJ_T(TgELLIPSE,PCU) );

#include "TgS Common [Unit Test] - Geometry - Type.c_inc"

#include "TgS Common [Unit Test] - Geometry 2D - Rectangle.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Box - Axis Aligned.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Box.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Capsule.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Circle.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Cylinder.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Line.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Mesh [Simple].c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Mesh [BA].c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Mesh [BVT].c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Parallelogram.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Particle.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Plane.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Ray.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Rectangle.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Segment.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Sphere.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Torus.c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Triangle [Point].c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Triangle [Edge].c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Triangle [Collision].c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Triangle [Space].c_inc"
#include "TgS Common [Unit Test] - Geometry 3D - Tube.c_inc"

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* =============================================================================================================================================================================== */

/*# defined (TGS_COMMON_GEOMETRY_H) */
#endif
