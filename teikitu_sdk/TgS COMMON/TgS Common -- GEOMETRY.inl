/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common -- GEOMETRY.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON____GEOMETRY_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


/* == Common ===================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#include "TgS COMMON/TgS Common - Geometry - Type.inl"

#include "TgS COMMON/TgS Common - Geometry 2D - Rectangle.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Box - Axis Aligned.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Box.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Capsule.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Circle.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Cylinder.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Ellipse.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Line.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Mesh [BA].inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Mesh [BVT].inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Mesh [Simple].inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Mesh [Utility].inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Parallelogram.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Particle.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Plane.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Ray.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Rectangle.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Segment.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Sphere.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Torus.inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Triangle [Collision].inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Triangle [Edge].inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Triangle [Point].inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Triangle [Space].inl"
#include "TgS COMMON/TgS Common - Geometry 3D - Tube.inl"

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* =============================================================================================================================================================================== */

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TGS_COMMON____GEOMETRY_INL

#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COMMON_GEOMETRY_INL) */
#endif
