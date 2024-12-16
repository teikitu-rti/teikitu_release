/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common -- GEOMETRY.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_H)


/* == Common ===================================================================================================================================================================== */

#if !defined(TGS_COMMON_GEOMETRY_H__ONCE)
#define TGS_COMMON_GEOMETRY_H__ONCE

#if defined(TgCOMPILE_ASSERT__GEOM_PARAM_CHECK) && TgCOMPILE_ASSERT__GEOM_PARAM_CHECK
    #define TgGEOM_ASSERT_PARAM(...)            TgPARAM_CHECK(__VA_ARGS__)
#else
    #define TgGEOM_ASSERT_PARAM(...)
#endif

#include "TgS COMMON/TgS Common - Geometry - Constants.h"

TgTYPE_STRUCT(TgMESH_ITER,)
{
    TgRSIZE                                     m_uiIndex;
    TgRSIZE                                     m_nuiFace;
};

TgEXTN TgCHAR_U8_CP                         tgGM_Primitive_To_USZ( ETgPRIMITIVE_C );
TgEXTN TgCHAR_WC_CP                         tgGM_Primitive_To_WSZ( ETgPRIMITIVE_C );

/*# !defined(TGS_COMMON_GEOMETRY_H__ONCE) */
#endif


/* == Common ===================================================================================================================================================================== */

#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#include "TgS COMMON/TgS Common - Geometry - Type.h"

#include "TgS COMMON/TgS Common - Geometry 2D - Rectangle.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Box - Axis Aligned.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Box.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Capsule.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Circle.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Cylinder.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Ellipse.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Line.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Mesh [BA].h"
#include "TgS COMMON/TgS Common - Geometry 3D - Mesh [BVT].h"
#include "TgS COMMON/TgS Common - Geometry 3D - Mesh [Simple].h"
#include "TgS COMMON/TgS Common - Geometry 3D - Parallelogram.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Particle.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Plane.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Ray.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Rectangle.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Segment.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Sphere.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Torus.h"
#include "TgS COMMON/TgS Common - Geometry 3D - Triangle [Collision].h"
#include "TgS COMMON/TgS Common - Geometry 3D - Triangle [Edge].h"
#include "TgS COMMON/TgS Common - Geometry 3D - Triangle [Point].h"
#include "TgS COMMON/TgS Common - Geometry 3D - Triangle [Space].h"
#include "TgS COMMON/TgS Common - Geometry 3D - Tube.h"

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

    #define TGS_COMMON_GEOMETRY_H

#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COMMON_GEOMETRY_H) */
#endif
