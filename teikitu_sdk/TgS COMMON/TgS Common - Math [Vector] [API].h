/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Vector] [API].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_VECTOR_API_H)


#if !defined(TGS_COMMON_MATH_VECTOR_API_H__ONCE)
#define TGS_COMMON_MATH_VECTOR_API_H__ONCE

/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_MATH_VECTOR_API Vector SIMD Functions
    @ingroup TGS_COMMON_MATH
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_LOAD SIMD - Load | Set Operations
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_BOUNDS SIMD - Bounds
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_LOGICAL SIMD - Logical
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_PERM SIMD - Permute and Select
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_CMP SIMD - Comparison Operators
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_ART SIMD - Arithmetic Operations
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_API Vector Functions
    @ingroup TGS_COMMON_MATH
*/

/** @defgroup TGS_COMMON_MATH_QUAT Quaternion - Transformation
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_LOAD Load | Set Operations
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_BOUNDS Bounds
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_LOGICAL Logical
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_PERM Permute and Select
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_CMP Comparison Operators
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/

/** @defgroup TGS_COMMON_MATH_VECTOR_INT Arithmetic Operations
    @ingroup TGS_COMMON_MATH_VECTOR_API
*/


/*# !defined(TGS_COMMON_MATH_VECTOR_API_H__ONCE) */
#endif

#if defined(TEMPLATE_TYPE_EXPANSION__RELOAD)

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#include "TgS COMMON/TgS Common - Math [Vector] [S].h"
#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
    #include "TgS COMMON/TgS Common - Math [Vector].h"
#endif

#if defined(TEMPLATE__ENABLE_INTEGER)
    #include "TgS COMMON/TgS Common - Math [Vector] [S] [I].h"
    #if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
        #include "TgS COMMON/TgS Common - Math [Vector] [I].h"
    #endif

#else
    #include "TgS COMMON/TgS Common - Math [Vector] [S] [F].h"
    #if (4 == TEMPLATE__VECTOR_DIM)
        #include "TgS COMMON/TgS Common - Math [Vector] [S] [FXX_04].h"
    #endif
    #if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
        #include "TgS COMMON/TgS Common - Math [Vector] [F].h"
        #if (4 == TEMPLATE__VECTOR_DIM)
            #include "TgS COMMON/TgS Common - Math [Vector] [FXX_04].h"
        #endif
    #endif

#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */


/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TEMPLATE__TEST_AND_UNLOAD_TEMPLATE_MACROS

    #define TEMPLATE__ENABLE_INTEGER
    #define TEMPLATE__ENABLE_UNSIGNED

    #define TEMPLATE__TYPE_SIZE 8
    #define TEMPLATE__VECTOR_DIM 16
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 16
    #define TEMPLATE__VECTOR_DIM 8
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 32
    #define TEMPLATE__VECTOR_DIM 4
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 8
    #define TEMPLATE__VECTOR_DIM 4
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 16
    #define TEMPLATE__VECTOR_DIM 2
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 64
    #define TEMPLATE__VECTOR_DIM 4
    #include __FILE__

    #undef TEMPLATE__ENABLE_UNSIGNED

    #define TEMPLATE__TYPE_SIZE 8
    #define TEMPLATE__VECTOR_DIM 16
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 16
    #define TEMPLATE__VECTOR_DIM 8
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 32
    #define TEMPLATE__VECTOR_DIM 4
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 8
    #define TEMPLATE__VECTOR_DIM 4
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 16
    #define TEMPLATE__VECTOR_DIM 2
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 64
    #define TEMPLATE__VECTOR_DIM 4
    #include __FILE__

    #undef TEMPLATE__ENABLE_INTEGER

    #define TEMPLATE__VECTOR_DIM 2
    #define TEMPLATE__TYPE_SIZE 64
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 2
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 3
    #define TEMPLATE__TYPE_SIZE 64
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 3
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 64
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COMMON_MATH_VECTOR_API_H) */
#endif
