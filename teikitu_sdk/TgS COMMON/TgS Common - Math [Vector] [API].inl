/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Vector] [API].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_VECTOR_API_INL)


#if !defined(TGS_COMMON_MATH_VECTOR_API_INL__ONCE)
#define TGS_COMMON_MATH_VECTOR_API_INL__ONCE

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Code Macros                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define VEC_02_1_ASSIGN_EQN                                                                                                                                                         \
    VEC_S_T(1)                          vResult;                                                                                                                                    \
    vResult.m_aData[ 0] = EQN( 0);                                                                                                                                                  \
    vResult.m_aData[ 1] = EQN( 1);                                                                                                                                                  \
    return (vResult);

#define VEC_03_1_ASSIGN_EQN                                                                                                                                                         \
    VEC_S_T(1)                          vResult;                                                                                                                                    \
    vResult.m_aData[ 0] = EQN( 0);                                                                                                                                                  \
    vResult.m_aData[ 1] = EQN( 1);                                                                                                                                                  \
    vResult.m_aData[ 2] = EQN( 2);                                                                                                                                                  \
    return (vResult);

#define VEC_04_1_ASSIGN_EQN                                                                                                                                                         \
    VEC_S_T(1)                          vResult;                                                                                                                                    \
    vResult.m_aData[ 0] = EQN( 0);                                                                                                                                                  \
    vResult.m_aData[ 1] = EQN( 1);                                                                                                                                                  \
    vResult.m_aData[ 2] = EQN( 2);                                                                                                                                                  \
    vResult.m_aData[ 3] = EQN( 3);                                                                                                                                                  \
    return (vResult);

#define VEC_08_1_ASSIGN_EQN                                                                                                                                                         \
    VEC_S_T(1)                          vResult;                                                                                                                                    \
    vResult.m_aData[ 0] = EQN( 0);                                                                                                                                                  \
    vResult.m_aData[ 1] = EQN( 1);                                                                                                                                                  \
    vResult.m_aData[ 2] = EQN( 2);                                                                                                                                                  \
    vResult.m_aData[ 3] = EQN( 3);                                                                                                                                                  \
    vResult.m_aData[ 4] = EQN( 4);                                                                                                                                                  \
    vResult.m_aData[ 5] = EQN( 5);                                                                                                                                                  \
    vResult.m_aData[ 6] = EQN( 6);                                                                                                                                                  \
    vResult.m_aData[ 7] = EQN( 7);                                                                                                                                                  \
    return (vResult);

#define VEC_16_1_ASSIGN_EQN                                                                                                                                                         \
    VEC_S_T(1)                          vResult;                                                                                                                                    \
    vResult.m_aData[ 0] = EQN( 0);                                                                                                                                                  \
    vResult.m_aData[ 1] = EQN( 1);                                                                                                                                                  \
    vResult.m_aData[ 2] = EQN( 2);                                                                                                                                                  \
    vResult.m_aData[ 3] = EQN( 3);                                                                                                                                                  \
    vResult.m_aData[ 4] = EQN( 4);                                                                                                                                                  \
    vResult.m_aData[ 5] = EQN( 5);                                                                                                                                                  \
    vResult.m_aData[ 6] = EQN( 6);                                                                                                                                                  \
    vResult.m_aData[ 7] = EQN( 7);                                                                                                                                                  \
    vResult.m_aData[ 8] = EQN( 8);                                                                                                                                                  \
    vResult.m_aData[ 9] = EQN( 9);                                                                                                                                                  \
    vResult.m_aData[10] = EQN(10);                                                                                                                                                  \
    vResult.m_aData[11] = EQN(11);                                                                                                                                                  \
    vResult.m_aData[12] = EQN(12);                                                                                                                                                  \
    vResult.m_aData[13] = EQN(13);                                                                                                                                                  \
    vResult.m_aData[14] = EQN(14);                                                                                                                                                  \
    vResult.m_aData[15] = EQN(15);                                                                                                                                                  \
    return (vResult);

/*# !defined(TGS_COMMON_MATH_VECTOR_API_INL__ONCE) */
#endif

#if defined(TEMPLATE_TYPE_EXPANSION__RELOAD)

/* == Common ===================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#include "TgS COMMON/TgS Common - Math [Vector] [S].inl"
#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || (!defined(TGS_COMMON_MATH_VECTOR_SPECIALIZATION) && VEC_IS_NATIVE) /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
    #include "TgS COMMON/TgS Common - Math [Vector].inl"
#endif

#if defined(TEMPLATE__ENABLE_INTEGER)
    #include "TgS COMMON/TgS Common - Math [Vector] [S] [I].inl"
    #if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || (!defined(TGS_COMMON_MATH_VECTOR_SPECIALIZATION) && VEC_IS_NATIVE) /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
        #include "TgS COMMON/TgS Common - Math [Vector] [I].inl"
    #endif

#else
    #include "TgS COMMON/TgS Common - Math [Vector] [S] [F].inl"
    #if (4 == TEMPLATE__VECTOR_DIM)
        #include "TgS COMMON/TgS Common - Math [Vector] [S] [FXX_04].inl"
    #endif
    #if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || (!defined(TGS_COMMON_MATH_VECTOR_SPECIALIZATION) && VEC_IS_NATIVE) /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
        #include "TgS COMMON/TgS Common - Math [Vector] [F].inl"
        #if (4 == TEMPLATE__VECTOR_DIM)
            #include "TgS COMMON/TgS Common - Math [Vector] [FXX_04].inl"
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

    #undef VEC_12_ASSIGN_EQN
    #undef VEC_13_ASSIGN_EQN
    #undef VEC_14_ASSIGN_EQN
    #undef VEC_08_ASSIGN_EQN
    #undef VEC_16_ASSIGN_EQN

/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COMMON_MATH_VECTOR_API_INL) */
#endif
