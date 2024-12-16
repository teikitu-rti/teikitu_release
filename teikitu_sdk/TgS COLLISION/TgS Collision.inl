/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_INL)
#define TGS_COLLISION_INL
#pragma once

#include "TgS COMMON/TgS Common.inl"

#include "TgS COLLISION/TgS Collision - System.inl"

#include "TgS COLLISION/TgS Collision - Box AA-Box AA.inl"
#include "TgS COLLISION/TgS Collision - Box AA-Plane.inl"
#include "TgS COLLISION/TgS Collision - Box AA-Point.inl"
#include "TgS COLLISION/TgS Collision - Box AA-Sphere.inl"
#include "TgS COLLISION/TgS Collision - Box AA-Triangle.inl"

#include "TgS COLLISION/TgS Collision - Box [Util].inl"
#include "TgS COLLISION/TgS Collision - Box-Linear.inl"
#include "TgS COLLISION/TgS Collision - Box-Line.inl"
#include "TgS COLLISION/TgS Collision - Box-Plane.inl"
#include "TgS COLLISION/TgS Collision - Box-Point.inl"
#include "TgS COLLISION/TgS Collision - Box-Ray.inl"
#include "TgS COLLISION/TgS Collision - Box-Segment.inl"
#include "TgS COLLISION/TgS Collision - Box-Sphere.inl"
#include "TgS COLLISION/TgS Collision - Box-Triangle.inl"

#include "TgS COLLISION/TgS Collision - Capsule [Util].inl"
#include "TgS COLLISION/TgS Collision - Capsule-Capsule.inl"
#include "TgS COLLISION/TgS Collision - Capsule-Linear.inl"
#include "TgS COLLISION/TgS Collision - Capsule-Line.inl"
#include "TgS COLLISION/TgS Collision - Capsule-Plane.inl"
#include "TgS COLLISION/TgS Collision - Capsule-Point.inl"
#include "TgS COLLISION/TgS Collision - Capsule-Ray.inl"
#include "TgS COLLISION/TgS Collision - Capsule-Segment.inl"
#include "TgS COLLISION/TgS Collision - Capsule-Sphere.inl"
#include "TgS COLLISION/TgS Collision - Capsule-Triangle.inl"

#include "TgS COLLISION/TgS Collision - Circle-Circle.inl"
#include "TgS COLLISION/TgS Collision - Circle-Line.inl"
#include "TgS COLLISION/TgS Collision - Circle-Point.inl"
#include "TgS COLLISION/TgS Collision - Circle-Ray.inl"
#include "TgS COLLISION/TgS Collision - Circle-Segment.inl"

#include "TgS COLLISION/TgS Collision - Cylinder-Linear.inl"
#include "TgS COLLISION/TgS Collision - Cylinder-Line.inl"
#include "TgS COLLISION/TgS Collision - Cylinder-Plane.inl"
#include "TgS COLLISION/TgS Collision - Cylinder-Ray.inl"
#include "TgS COLLISION/TgS Collision - Cylinder-Segment.inl"

#include "TgS COLLISION/TgS Collision - Line.inl"
#include "TgS COLLISION/TgS Collision - Ray.inl"
#include "TgS COLLISION/TgS Collision - Segment.inl"

#include "TgS COLLISION/TgS Collision - Parallelogram-Linear.inl"
#include "TgS COLLISION/TgS Collision - Parallelogram-Line.inl"
#include "TgS COLLISION/TgS Collision - Parallelogram-Parallelogram.inl"
#include "TgS COLLISION/TgS Collision - Parallelogram-Point.inl"
#include "TgS COLLISION/TgS Collision - Parallelogram-Ray.inl"
#include "TgS COLLISION/TgS Collision - Parallelogram-Rectangle.inl"
#include "TgS COLLISION/TgS Collision - Parallelogram-Segment.inl"
#include "TgS COLLISION/TgS Collision - Parallelogram-Triangle.inl"

#include "TgS COLLISION/TgS Collision - Plane-Linear.inl"
#include "TgS COLLISION/TgS Collision - Plane-Line.inl"
#include "TgS COLLISION/TgS Collision - Plane-Point.inl"
#include "TgS COLLISION/TgS Collision - Plane-Ray.inl"
#include "TgS COLLISION/TgS Collision - Plane-Segment.inl"

#include "TgS COLLISION/TgS Collision - Rectangle-Linear.inl"
#include "TgS COLLISION/TgS Collision - Rectangle-Line.inl"
#include "TgS COLLISION/TgS Collision - Rectangle-Point.inl"
#include "TgS COLLISION/TgS Collision - Rectangle-Ray.inl"
#include "TgS COLLISION/TgS Collision - Rectangle-Rectangle.inl"
#include "TgS COLLISION/TgS Collision - Rectangle-Segment.inl"
#include "TgS COLLISION/TgS Collision - Rectangle-Triangle.inl"

#include "TgS COLLISION/TgS Collision - Sphere-Linear.inl"
#include "TgS COLLISION/TgS Collision - Sphere-Line.inl"
#include "TgS COLLISION/TgS Collision - Sphere-Plane.inl"
#include "TgS COLLISION/TgS Collision - Sphere-Point.inl"
#include "TgS COLLISION/TgS Collision - Sphere-Ray.inl"
#include "TgS COLLISION/TgS Collision - Sphere-Segment.inl"
#include "TgS COLLISION/TgS Collision - Sphere-Sphere.inl"
#include "TgS COLLISION/TgS Collision - Sphere-Triangle.inl"

#include "TgS COLLISION/TgS Collision - Triangle [Util].inl"
#include "TgS COLLISION/TgS Collision - Triangle-Line.inl"
#include "TgS COLLISION/TgS Collision - Triangle-Point.inl"
#include "TgS COLLISION/TgS Collision - Triangle-Ray.inl"
#include "TgS COLLISION/TgS Collision - Triangle-Segment.inl"
#include "TgS COLLISION/TgS Collision - Triangle-Triangle.inl"

#include "TgS COLLISION/TgS Collision - Tube-Linear.inl"
#include "TgS COLLISION/TgS Collision - Tube-Line.inl"
#include "TgS COLLISION/TgS Collision - Tube-Ray.inl"
#include "TgS COLLISION/TgS Collision - Tube-Segment.inl"


/* =============================================================================================================================================================================== */
#endif
