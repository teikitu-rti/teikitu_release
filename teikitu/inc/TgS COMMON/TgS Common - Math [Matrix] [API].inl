/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Matrix] [API].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_MATRIX_API_INL)


#if !defined(TGS_COMMON_MATH_MATRIX_API_INL__ONCE)
#define TGS_COMMON_MATH_MATRIX_API_INL__ONCE

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Code Macros                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define MAT_03_ASSIGN_EQN                                                                                                                                                           \
    pmOUT_0->m_avCol[0] = EQN( 0 );                                                                                                                                                 \
    pmOUT_0->m_avCol[1] = EQN( 1 );                                                                                                                                                 \
    pmOUT_0->m_avCol[2] = EQN( 2 );

#define MAT_04_ASSIGN_EQN                                                                                                                                                           \
    pmOUT_0->m_avCol[0] = EQN( 0 );                                                                                                                                                 \
    pmOUT_0->m_avCol[1] = EQN( 1 );                                                                                                                                                 \
    pmOUT_0->m_avCol[2] = EQN( 2 );                                                                                                                                                 \
    pmOUT_0->m_avCol[3] = EQN( 3 );

/*# !defined(TGS_COMMON_MATH_MATRIX_API_INL__ONCE) */
#endif

#if defined(TEMPLATE_TYPE_EXPANSION__RELOAD)

/* == Common ===================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#include "TgS COMMON/TgS Common - Math [Matrix] [S].inl"
#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || (!defined(TGS_COMMON_MATH_MATRIX_SPECIALIZATION) && VEC_IS_NATIVE) /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */
    #include "TgS COMMON/TgS Common - Math [Matrix].inl"
#endif

#if defined(TEMPLATE__ENABLE_INTEGER)
    #error Not supported

#else
    #include "TgS COMMON/TgS Common - Math [Matrix] [S] [F].inl"
    #if (4 == TEMPLATE__VECTOR_COL)
        #include "TgS COMMON/TgS Common - Math [Matrix] [S] [F] [44].inl"
    #elif (3 == TEMPLATE__VECTOR_COL)
        #include "TgS COMMON/TgS Common - Math [Matrix] [S] [F] [34].inl"
    #endif

    #if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || (!defined(TGS_COMMON_MATH_MATRIX_SPECIALIZATION) && VEC_IS_NATIVE) /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */
        #include "TgS COMMON/TgS Common - Math [Matrix] [F].inl"
        #if (4 == TEMPLATE__VECTOR_COL)
            #include "TgS COMMON/TgS Common - Math [Matrix] [F] [44].inl"
        #elif (3 == TEMPLATE__VECTOR_COL)
            #include "TgS COMMON/TgS Common - Math [Matrix] [F] [34].inl"
        #endif
    #endif

#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */


/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TEMPLATE__TEST_AND_UNLOAD_TEMPLATE_MACROS

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__VECTOR_COL 3
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__VECTOR_COL 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__VECTOR_COL 3
    #define TEMPLATE__TYPE_SIZE 64
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__VECTOR_COL 4
    #define TEMPLATE__TYPE_SIZE 64
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

    #undef MAT_04_ASSIGN_EQN
    #undef MAT_03_ASSIGN_EQN

/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COMMON_MATH_VECTOR_API_H) */
#endif
