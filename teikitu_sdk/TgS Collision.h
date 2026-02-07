/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* DEFINITION: PENETRATION TEST
    Returns the first point of contact, the normal of separation and the depth of the contact.
        Point of Contact - A point on the surface of object 1 that is suspected of being first point of contact.
        Normal of Separation - The minimal direction which will separate the two bodies.
        Depth - The minimal distance that will separate the two bodies.
        Concept: The values are such that if the point of contact is moved along the normal by the depth it will cause object 1 to be completely separated from object 0.
                 The resultant axis of separation would be the normal of penetration.  The object being moved to separate the two bodies is object 1.

   F_Sweep == First point and time of contact
   F_Intersect == All possible points of contact/interface (ie non-volume interactions)
   F_Penetrate == All possible points of contact with normal and depths ( ie. dual volume interactions )                                                                           */


/* TODO Implement tgCO_Sweep_LR11_CP */
/* TODO Implement tgCO_Sweep_VT_CP */
/* TODO Implement tgCO_Sweep_ET_CP */
/* TODO Implement tgCO_Test_BA_PT */
/* TODO Implement tgCO_Penetrate_BX_BX */
/* TODO Implement tgCO_Penetrate_BX_BX */
/* TODO Implement tgCO_Module_Init */
/* TODO Implement tgCO_Module_Boot */
/* TODO Implement tgCO_Module_Stop */
/* TODO Implement tgCO_Module_Free */
/* TODO Implement tgCO_Module_Update */
/* TODO Implement tgCO_Load_Config - Note no parameter for configuration file or similar mechanism */
/* TODO Implement tgCO_Save_Config - Note no parameter for configuration file or similar mechanism */
/* TODO Implement tgCO_Query_Init */
/* TODO Implement tgCO_Query_Boot */
/* TODO Implement tgCO_Query_Fixed_Memory */
/* TODO Implement Triangle collision queries to respect feature flags */


#if !defined(TGS_COLLISION_H)
#define TGS_COLLISION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "TgS Common.h"

#include "TgS COLLISION/TgS Collision - Constants.h"
#include "TgS COLLISION/TgS Collision - Type.h"


/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgCO_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgCO_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgCO_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgCO_Module_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgCO_Module_Update(
    TgFLOAT32_C ARG0 );


/** @brief Standard Module functions: Set the current configuration of the module. */
TgEXTN TgVOID
tgCO_Load_Config( TgVOID );

/** @brief Standard Module function: Save the current configuration of the module. */
TgEXTN TgVOID
tgCO_Save_Config( TgVOID );


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgCO_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgCO_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgCO_Query_Fixed_Memory( TgVOID );


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Collision Functions                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#include "TgS COLLISION/TgS Collision - Request.h"


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Collision - Pair Functions                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#include "TgS COLLISION/TgS Collision - Box AA.h"
#include "TgS COLLISION/TgS Collision - Box.h"
#include "TgS COLLISION/TgS Collision - Capsule.h"
#include "TgS COLLISION/TgS Collision - Circle.h"
#include "TgS COLLISION/TgS Collision - Cylinder.h"
#include "TgS COLLISION/TgS Collision - Ellipse.h"
#include "TgS COLLISION/TgS Collision - Line.h"
#include "TgS COLLISION/TgS Collision - Mesh.h"
#include "TgS COLLISION/TgS Collision - Parallelogram.h"
#include "TgS COLLISION/TgS Collision - Plane.h"
#include "TgS COLLISION/TgS Collision - Ray.h"
#include "TgS COLLISION/TgS Collision - Rectangle.h"
#include "TgS COLLISION/TgS Collision - Segment.h"
#include "TgS COLLISION/TgS Collision - Sphere.h"
#include "TgS COLLISION/TgS Collision - Torus.h"
#include "TgS COLLISION/TgS Collision - Triangle.h"
#include "TgS COLLISION/TgS Collision - Tube.h"


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Collision - Generic Pair Functions                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#include "TgS COLLISION/TgS Collision - Primitive.h"


/* =============================================================================================================================================================================== */
#endif


