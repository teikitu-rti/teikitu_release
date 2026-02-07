/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Object [INC].h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined (ENABLE_RELOAD_GUARD_INC)

/** Physic's Data Structures
    Material
    Form/Shape
    Body
    Constraint
    Motor
    Ragdoll
    Scene
    World
*/

#define ENABLE_RELOAD_GUARD_INC

#if defined(T_FCN) || defined(T_NAME) || defined(T_ID) || defined(T_GLOBAL) || defined(T_STATIC) || defined(T_NAME_VAR) || defined(T_NAME_DECLARE)
#error These should not be defined in prior text of this file
/*# defined(T_FCN) || defined(T_NAME) || defined(T_ID) || defined(T_GLOBAL) || defined(T_STATIC) || defined(T_NAME_VAR) || defined(T_NAME_DECLARE) */
#endif

/* Material */
#define MALLOC_COMMENT MATERIAL
#define T_FCN(A,B,C) A##Material##B##Material##C
#define T_NAME(A,B) A##Material##B
#define T_ID(A,B) A##MATERIAL##B
#define T_GLOBAL
#define T_NAME_VAR(A,B) g_##A##Material##B
#define T_NAME_DECLARE(A,B) g_##A##Material##B
#include "TgS Physics - Object [INC].h"

/* Form */
#define MALLOC_COMMENT FORM
#define T_FCN(A,B,C) A##Form##B##Form##C
#define T_NAME(A,B) A##Form##B
#define T_ID(A,B) A##FORM##B
#define T_NAME_VAR(A,B) g_a##A##Form##B[tiWorld.m_uiI]
#define T_NAME_DECLARE(A,B) g_a##A##Form##B[ETgPH_MAX_WORLD]
#include "TgS Physics - Object [INC].h"

/* Body */
#define MALLOC_COMMENT BODY
#define T_FCN(A,B,C) A##Body##B##Body##C
#define T_NAME(A,B) A##Body##B
#define T_ID(A,B) A##BODY##B
#define USE_DISABLE_TIMER 1
#define T_NAME_VAR(A,B) g_a##A##Body##B[tiWorld.m_uiI]
#define T_NAME_DECLARE(A,B) g_a##A##Body##B[ETgPH_MAX_WORLD]
#include "TgS Physics - Object [INC].h"

/* Constraint */
#define MALLOC_COMMENT CONSTRAINT
#define T_FCN(A,B,C) A##Constraint##B##Constraint##C
#define T_NAME(A,B) A##Constraint##B
#define T_ID(A,B) A##CONSTRAINT##B
#define T_NAME_VAR(A,B) g_a##A##Constraint##B[tiWorld.m_uiI]
#define T_NAME_DECLARE(A,B) g_a##A##Constraint##B[ETgPH_MAX_WORLD]
#include "TgS Physics - Object [INC].h"

/* Motor */
#define MALLOC_COMMENT MOTOR
#define T_FCN(A,B,C) A##Motor##B##Motor##C
#define T_NAME(A,B) A##Motor##B
#define T_ID(A,B) A##MOTOR##B
#define T_NAME_VAR(A,B) g_a##A##Motor##B[tiWorld.m_uiI]
#define T_NAME_DECLARE(A,B) g_a##A##Motor##B[ETgPH_MAX_WORLD]
#include "TgS Physics - Object [INC].h"

/* Ragdoll */
#define MALLOC_COMMENT RAGDOLL
#define T_FCN(A,B,C) A##Ragdoll##B##Ragdoll##C
#define T_NAME(A,B) A##Ragdoll##B
#define T_ID(A,B) A##RAGDOLL##B
#define T_NAME_VAR(A,B) g_a##A##Ragdoll##B[tiWorld.m_uiI]
#define T_NAME_DECLARE(A,B) g_a##A##Ragdoll##B[ETgPH_MAX_WORLD]
#include "TgS Physics - Object [INC].h"

/* Scene */
#define MALLOC_COMMENT SCENE
#define T_FCN(A,B,C) A##Scene##B##Scene##C
#define T_NAME(A,B) A##Scene##B
#define T_ID(A,B) A##SCENE##B
#define T_GLOBAL
#define T_NAME_VAR(A,B) g_##A##Scene##B
#define T_NAME_DECLARE(A,B) g_##A##Scene##B
#include "TgS Physics - Object [INC].h"

/* World */
#define MALLOC_COMMENT WORLD
#define T_FCN(A,B,C) A##World##B##World##C
#define T_NAME(A,B) A##World##B
#define T_ID(A,B) A##WORLD##B
#define T_GLOBAL
#define T_STATIC
#define T_NAME_VAR(A,B) g_##A##World##B
#define T_NAME_DECLARE(A,B) g_##A##World##B
#include "TgS Physics - Object [INC].h"

#undef ENABLE_RELOAD_GUARD_INC

#else

/** Error Checking */

#if !defined(__PARENT_FILE__)
#error Source Include file (template file) missing necessary definitions
/*# !defined(__PARENT_FILE__) */
#endif

#if !defined(T_FCN) || !defined(T_NAME) || !defined(T_ID) || !defined(T_NAME_VAR) || !defined(T_NAME_DECLARE)
#error These should be defined in prior text of this file
/*# !defined(T_FCN) || !defined(T_NAME) || !defined(T_ID) || !defined(T_NAME_VAR) || !defined(T_NAME_DECLARE) */
#endif


#include __PARENT_FILE__

#undef MALLOC_COMMENT
#undef T_ID
#undef T_NAME
#undef T_FCN
#undef T_GLOBAL
#undef T_STATIC
#undef T_NAME_VAR
#undef T_NAME_DECLARE

/*# !defined (ENABLE_RELOAD_GUARD) */
#endif
