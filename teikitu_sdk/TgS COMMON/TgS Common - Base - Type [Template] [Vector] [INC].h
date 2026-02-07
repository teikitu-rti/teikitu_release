/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Type [Template] [Vector].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if defined(TGS_COMMON_BASE_TYPE_VECTOR_HINC)
    #error This file should be included by TGS_COMMON_BASE_TYPE_VECTOR_H
#endif

#if defined(TEMPLATE__ENABLE_INTEGER)

    #if !defined (ENABLE_RELOAD_GUARD)
        #define ENABLE_RELOAD_GUARD
        #define TEMPLATE__ENABLE_UNSIGNED
        #include __FILE__
        #undef TEMPLATE__ENABLE_UNSIGNED
        #undef ENABLE_RELOAD_GUARD
    #endif

#else

    #if !defined (ENABLE_RELOAD_GUARD)
        #define ENABLE_RELOAD_GUARD
        #if !defined(TEMPLATE__TYPE_SIZE)
            #define TEMPLATE__TYPE_SIZE 32
            #include __FILE__
            #undef TEMPLATE__TYPE_SIZE
            #define TEMPLATE__TYPE_SIZE 64
        #endif
        #undef ENABLE_RELOAD_GUARD
    #endif

#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#undef TgMACRO_VECTOR_
#undef TgMACRO_NATIVE_VECTOR_

#if TEMPLATE__VECTOR_DIM < 10
    #define TgMACRO_VECTOR_(A,B,C,D,E) TgVEC_##A##B##_##C##_0##D
    #define TgMACRO_NATIVE_VECTOR_(A,B,C,D,E) TgVEC_##A##B##_##C##_0##D
#else
    #define TgMACRO_VECTOR_(A,B,C,D,E) TgVEC_##A##B##_##C##_##D
    #define TgMACRO_NATIVE_VECTOR_(A,B,C,D,E) TgVEC_##A##B##_##C##_##D
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || (!defined(TGS_COMMON_MATH_VECTOR_SPECIALIZATION) && VEC_IS_NATIVE) /* MACRO_COMPILE_NATIVE_VECTOR_GUARD */
TgCLANG_WARN_DISABLE_PUSH(padded)
#if VEC_IS_NATIVE
TgTYPE_UNION( VEC_T(1), )
{
    TgALIGN(16) VAR_T()                         m_aData[TEMPLATE__VECTOR_DIM];
};
#else
TgTYPE_UNION( VEC_T(1), )
{
    VAR_T()                                     m_aData[TEMPLATE__VECTOR_DIM];
};
#endif
TgCLANG_WARN_DISABLE_POP(padded)
/*# (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || (!defined(TGS_COMMON_MATH_VECTOR_SPECIALIZATION) && VEC_IS_NATIVE) */
#endif

TgTYPE_UNION( VEC_S_T(1), )
{
    VAR_T()                                     m_aData[TEMPLATE__VECTOR_DIM];
    #if 4 == TEMPLATE__VECTOR_DIM
    struct { VAR_T()                            x,y,z,w; };
    struct { VAR_T()                            r,g,b,a; };
    #elif 3 == TEMPLATE__VECTOR_DIM
    struct { VAR_T()                            x,y,z; };
    struct { VAR_T()                            r,g,b; };
    #elif 2 == TEMPLATE__VECTOR_DIM
    struct { VAR_T()                            x,y; };
    #endif
};

TgTYPE_UNION( VEC_DEC_T(TgVEC_UN,1), )
{
    VEC_T(1)                                    TgMACRO_CONCAT3( m_v, GENERATE__VEC_DESC, _1 );
    VEC_S_T(1)                                  TgMACRO_CONCAT3( m_vS_, GENERATE__VEC_DESC, _1 );
};
TgCOMPILER_ASSERT(sizeof(VAR_T())*TEMPLATE__VECTOR_DIM == sizeof(VEC_DEC_T(TgVEC_UN,1)),0 );

TgTYPE_UNION( VEC_DEC_T(TgVEC_UN_PTR,1), )
{
    VEC_T(1,P)                                  TgMACRO_CONCAT3( m_pv, GENERATE__VEC_DESC, _1 );
    VEC_S_T(1,P)                                TgMACRO_CONCAT3( m_pvS_, GENERATE__VEC_DESC, _1 );
};

TgTYPE_UNION( VEC_DEC_T(TgVEC_UN_CONST_PTR,1), )
{
    VEC_T(1,CP)                                 TgMACRO_CONCAT3( m_pv, GENERATE__VEC_DESC, _1 );
    VEC_S_T(1,CP)                               TgMACRO_CONCAT3( m_pvS_, GENERATE__VEC_DESC, _1 );
};




#if !defined(TEMPLATE__ENABLE_INTEGER) && (TEMPLATE__VECTOR_DIM > 2)

/** @union Non-native (scalar) vector with 3 rows (a DIMx3 matrix)
    @brief Matrix / Memory Layout - Column Major (currently used to match against apple SIMD implementation) */
TgTYPE_UNION( VEC_S_T(3), )
{
#if 4 == TEMPLATE__VECTOR_DIM
    struct { VAR_T()                            _11,_21,_31,_41,
                                                _12,_22,_32,_42,
                                                _13,_23,_33,_43; };
#endif
    struct { VEC_S_T(1)                         m_vC0,m_vC1,m_vC2; };
    VAR_T()                                     m_aElement[3*TEMPLATE__VECTOR_DIM];
    VAR_T()                                     m_aColRow[3][TEMPLATE__VECTOR_DIM];
    VEC_S_T(1)                                  m_avCol[3];
};


#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || (!defined(TGS_COMMON_MATH_MATRIX_SPECIALIZATION) && VEC_IS_NATIVE) /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */
/** @union Native vector */
TgTYPE_UNION( VEC_T(3), )
{
    struct { VEC_T(1)                           m_vC0,m_vC1,m_vC2; };
    VEC_T(1)                                    m_avCol[3];
};

/*# (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || (!defined(TGS_COMMON_MATH_MATRIX_SPECIALIZATION) && VEC_IS_NATIVE) */
#endif

TgTYPE_UNION( VEC_DEC_T(TgVEC_UN,3), )
{
    VEC_T(3)                                    TgMACRO_CONCAT3( m_m, GENERATE__VEC_DESC, _3 );
    VEC_S_T(3)                                  TgMACRO_CONCAT3( m_mS_, GENERATE__VEC_DESC, _3 );
};
TgCOMPILER_ASSERT(sizeof(VAR_T())*TEMPLATE__VECTOR_DIM*3 == sizeof(VEC_DEC_T(TgVEC_UN,3)),0 );

TgTYPE_UNION( VEC_DEC_T(TgVEC_UN_PTR,3), )
{
    VEC_T(3,P)                                  TgMACRO_CONCAT3( m_pm, GENERATE__VEC_DESC, _3 );
    VEC_S_T(3,P)                                TgMACRO_CONCAT3( m_pmS_, GENERATE__VEC_DESC, _3 );
};

TgTYPE_UNION( VEC_DEC_T(TgVEC_UN_CONST_PTR,3), )
{
    VEC_T(3,CP)                                 TgMACRO_CONCAT3( m_pm, GENERATE__VEC_DESC, _3 );
    VEC_S_T(3,CP)                               TgMACRO_CONCAT3( m_pmS_, GENERATE__VEC_DESC, _3 );
};

/*# !defined(TEMPLATE__ENABLE_INTEGER) && (TEMPLATE__VECTOR_DIM > 2) */
#endif





#if !defined(TEMPLATE__ENABLE_INTEGER) && (TEMPLATE__VECTOR_DIM > 3)

/** @union Non-native (scalar) vector with 4 rows (a DIMx4 matrix)
    @brief Memory Layout - Column Major (currently used to match against apple simd implementation)
           Matrix Layout - Row Major (Axis are stored across a row of the matrix), which with a column major memory layout allows for a 3x4 matrix size
           Multiplication Order - Pre Multiplication (e.g., P' = P * T * R * S [Row Vector x Matrix] due to row-major matrix format */
TgTYPE_UNION( VEC_S_T(4), )
{
#if 4 == TEMPLATE__VECTOR_DIM
    struct { VAR_T()                            _11,_21,_31,_41,
                                                _12,_22,_32,_42,
                                                _13,_23,_33,_43,
                                                _14,_24,_34,_44; };
#endif
    struct { VEC_S_T(1)                         m_vC0,m_vC1,m_vC2,m_vC3; };
    VAR_T()                                     m_aElement[4*TEMPLATE__VECTOR_DIM];
    VAR_T()                                     m_aColRow[4][TEMPLATE__VECTOR_DIM];
    VEC_S_T(1)                                  m_avCol[4];
};


#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || (!defined(TGS_COMMON_MATH_MATRIX_SPECIALIZATION) && VEC_IS_NATIVE) /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */
/** @union Native vector */
TgTYPE_UNION( VEC_T(4), )
{
    struct { VEC_T(1)                           m_vC0,m_vC1,m_vC2,m_vC3; };
    VEC_T(1)                                    m_avCol[4];
};

/*# (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || (!defined(TGS_COMMON_MATH_MATRIX_SPECIALIZATION) && VEC_IS_NATIVE) */
#endif

TgTYPE_UNION( VEC_DEC_T(TgVEC_UN,4), )
{
    VEC_T(4)                                    TgMACRO_CONCAT3( m_m, GENERATE__VEC_DESC, _4 );
    VEC_S_T(4)                                  TgMACRO_CONCAT3( m_mS_, GENERATE__VEC_DESC, _4 );
};
TgCOMPILER_ASSERT(sizeof(VAR_T())*TEMPLATE__VECTOR_DIM*4 == sizeof(VEC_DEC_T(TgVEC_UN,4)),0 );

TgTYPE_UNION( VEC_DEC_T(TgVEC_UN_PTR,4), )
{
    VEC_T(4,P)                                  TgMACRO_CONCAT3( m_pm, GENERATE__VEC_DESC, _4 );
    VEC_S_T(4,P)                                TgMACRO_CONCAT3( m_pmS_, GENERATE__VEC_DESC, _4 );
};

TgTYPE_UNION( VEC_DEC_T(TgVEC_UN_CONST_PTR,4), )
{
    VEC_T(4,CP)                                 TgMACRO_CONCAT3( m_pm, GENERATE__VEC_DESC, _4 );
    VEC_S_T(4,CP)                               TgMACRO_CONCAT3( m_pmS_, GENERATE__VEC_DESC, _4 );
};

/*# !defined(TEMPLATE__ENABLE_INTEGER) && (TEMPLATE__VECTOR_DIM > 3) */
#endif


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
