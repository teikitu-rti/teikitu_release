/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (X86_64) Common - Math [Vector] [F32].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_API_VECTOR_F32_INL)
#define TGS_COMMON_MATH_API_VECTOR_F32_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgMH_SETU_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
CLANG_WARN_DISABLE_PUSH(cast-align)
TgINLINE TgVEC_F32_04_1 tgMH_SETU_F32_04_1( TgFLOAT32_CPCU puiVal )
{
    return (_mm_loadu_ps( puiVal ));
}
CLANG_WARN_DISABLE_POP()


/* ---- tgMH_SETA_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
CLANG_WARN_DISABLE_PUSH(cast-align)
TgINLINE TgVEC_F32_04_1 tgMH_SETA_F32_04_1( TgFLOAT32_CPCU puiVal )
{
    return (_mm_load_ps( puiVal ));
}
CLANG_WARN_DISABLE_POP()


/* ---- tgMH_SET1_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_SET1_F32_04_1( TgFLOAT32_C fVal )
{
    return (_mm_set1_ps( fVal ));
}


/* ---- tgMH_SET4_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_SET4_F32_04_1( TgFLOAT32_C fX, TgFLOAT32_C fY, TgFLOAT32_C fZ, TgFLOAT32_C fW )
{
    return (_mm_set_ps( fW, fZ, fY, fX ));
}


/* ---- tgMH_RAND_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_RAND_F32_04_1( TgVOID )
{
    TgUN_V128                           vResult;

    vResult.m_vS_F32_04_1 = tgMH_RAND_S_F32_04_1();
    return (vResult.m_vF32_04_1);
}


/* ---- tgMH_SEL_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_SEL_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight, TgVEC_F32_04_1_C tuvMask )
{
    return (_mm_or_ps( _mm_and_ps( vLeft, _mm_xor_ps( KTgFFFF_V128.m_vF32_04_1, tuvMask ) ), _mm_and_ps( vRight, tuvMask ) ));
}


/* ---- tgMH_AND_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_AND_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_and_ps( vLeft, vRight ));
}


/* ---- tgMH_OR_F32_04_1 --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_OR_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_or_ps( vLeft, vRight ));
}


/* ---- tgMH_XOR_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_XOR_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_xor_ps( vLeft, vRight ));
}


/* ---- tgMH_MAX_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_MAX_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_max_ps( vLeft, vRight ));
}


/* ---- tgMH_MIN_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_MIN_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_min_ps( vLeft, vRight ));
}


/* ---- tgMH_ABS_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_ABS_F32_04_1( TgVEC_F32_04_1_C vARG )
{
    return (_mm_mul_ps( vARG, tgMH_SGN_F32_04_1( vARG ) ));
}


/* ---- tgMH_SGN_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_SGN_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    const __m128                        vNegZero = _mm_set1_ps( -0.0f );
    const __m128                        vNonZero = _mm_cmpneq_ps( vLeft, _mm_setzero_ps() );
    const __m128                        vX_Signbit = _mm_and_ps( vLeft, vNegZero );
    const __m128                        vZeroOne = _mm_and_ps( vNonZero, _mm_set1_ps(1.0f) );

    return _mm_or_ps(vZeroOne, vX_Signbit);
}


/* ---- tgMH_CMP_EQ_F32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_CMP_EQ_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_cmpeq_ps( vLeft, vRight ));
}


/* ---- tgMH_CMP_NE_F32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_CMP_NE_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_cmpneq_ps( vLeft, vRight ));
}


/* ---- tgMH_CMP_GE_F32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_CMP_GE_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_cmpge_ps( vLeft, vRight ));
}


/* ---- tgMH_CMP_GT_F32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_CMP_GT_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_cmpgt_ps( vLeft, vRight ));
}


/* ---- tgMH_CMP_LE_F32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_CMP_LE_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_cmple_ps( vLeft, vRight ));
}


/* ---- tgMH_CMP_LT_F32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_CMP_LT_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_cmplt_ps( vLeft, vRight ));
}


/* ---- tgMH_CMP_ALL_TO_BOOL_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgMH_CMP_ALL_TO_BOOL_F32_04_1( TgVEC_F32_04_1_C vARG )
{
    return (0 == _mm_testz_ps( vARG, KTgFFFF_V128.m_vF32_04_1 ) ? false : true );
}


/* ---- tgMH_ADD_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_ADD_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_add_ps( vLeft, vRight ));
}


/* ---- tgMH_MAD_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_MAD_F32_04_1( TgVEC_F32_04_1_C vM0, TgVEC_F32_04_1_C vM1, TgVEC_F32_04_1_C vA0 )
{
    return (_mm_add_ps( _mm_mul_ps( vM0, vM1 ), vA0 ));
}


/* ---- tgMH_NMS_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_NMS_F32_04_1( TgVEC_F32_04_1_C vM0, TgVEC_F32_04_1_C vM1, TgVEC_F32_04_1_C vA0 )
{
    return (_mm_sub_ps( vA0, _mm_mul_ps( vM0, vM1 ) ));
}


/* ---- tgMH_DOT_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_DOT_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_dp_ps( vLeft, vRight, 0xFF ));
}


/* ---- tgMH_MUL_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_MUL_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_mul_ps( vLeft, vRight ));
}


/* ---- tgMH_DIV_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_DIV_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_div_ps( vLeft, vRight ));
}


/* ---- tgMH_SUB_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_SUB_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (_mm_sub_ps( vLeft, vRight ));
}


/* ---- tgMH_LRP_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_LRP_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight, TgVEC_F32_04_1_C vParametric )
{
    return (tgMH_ADD_F32_04_1( vRight, tgMH_MUL_F32_04_1( tgMH_SUB_F32_04_1( vRight, vLeft ), vParametric ) ));
}


/* ---- tgMH_LSQ_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_LSQ_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    return (tgMH_DOT_F32_04_1( vLeft, vLeft ));
}


/* ---- tgMH_LEN_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_LEN_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    const __m128                        vX1 = _mm_mul_ps( vLeft, vLeft );
    const __m128                        vX2 = _mm_shuffle_ps( vX1, vX1, _MM_SHUFFLE( 3, 2, 3, 2 ) );
    const __m128                        vX3 = _mm_add_ps( vX1, vX2 );
    const __m128                        vX4 = _mm_shuffle_ps( vX3, vX3, _MM_SHUFFLE( 1, 0, 0, 0 ) );
    const __m128                        vX5 = _mm_shuffle_ps( vX2, vX4, _MM_SHUFFLE( 3, 3, 0, 0 ) );
    const __m128                        vX6 = _mm_add_ps( vX4, vX5 );
    const __m128                        vX7 = _mm_shuffle_ps( vX6, vX6, _MM_SHUFFLE( 2, 2, 2, 2 ) );
    const __m128                        vx8 = _mm_sqrt_ps( vX7 );

    return (vx8);
}


/* ---- tgMH_NEG_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_NEG_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    return (_mm_xor_ps( KTgSgnM_V128.m_vF32_04_1, vLeft ));
}


/* ---- tgMH_SQRT_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_SQRT_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    return (_mm_sqrt_ps( vLeft ));
}


/* ---- tgMH_RSQRT_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_RSQRT_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    const __m128                        vX1 = _mm_sqrt_ps( vLeft );
    const __m128                        vX2 = _mm_set1_ps( 1.0F );
    const __m128                        vX3 = _mm_div_ps( vX2, vX1 );

    return (vX3);
}


/* ---- tgMH_NORM_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_NORM_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    const __m128                        vX1 = _mm_mul_ps( vLeft, vLeft );
    const __m128                        vX2 = _mm_shuffle_ps( vX1, vX1, _MM_SHUFFLE( 3, 2, 3, 2 ) );
    const __m128                        vX3 = _mm_add_ps( vX1, vX2 );
    const __m128                        vX4 = _mm_shuffle_ps( vX3, vX3, _MM_SHUFFLE( 1, 0, 0, 0 ) );
    const __m128                        vX5 = _mm_shuffle_ps( vX2, vX4, _MM_SHUFFLE( 3, 3, 0, 0 ) );
    const __m128                        vX6 = _mm_add_ps( vX4, vX5 );
    const __m128                        vX7 = _mm_shuffle_ps( vX6, vX6, _MM_SHUFFLE( 2, 2, 2, 2 ) );
    const __m128                        vx8 = _mm_sqrt_ps( vX7 );
    const __m128                        vX9 = _mm_cmpneq_ps( vX7, KTgINF_V128.m_vF32_04_1 );
    const __m128                        vXA = _mm_div_ps( vLeft, vx8 );
    const __m128                        vXB = _mm_and_ps( vXA, vX9 );

    return (vXB);
}


/* ---- tgMH_NORM_LEN_F32_04_1 --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_NORM_LEN_F32_04_1( TgVEC_F32_04_1_PCU ptvRet_Length, TgVEC_F32_04_1_C vLeft )
{
    const __m128                        vX1 = _mm_mul_ps( vLeft, vLeft );
    const __m128                        vX2 = _mm_shuffle_ps( vX1, vX1, _MM_SHUFFLE( 3, 2, 3, 2 ) );
    const __m128                        vX3 = _mm_add_ps( vX1, vX2 );
    const __m128                        vX4 = _mm_shuffle_ps( vX3, vX3, _MM_SHUFFLE( 1, 0, 0, 0 ) );
    const __m128                        vX5 = _mm_shuffle_ps( vX2, vX4, _MM_SHUFFLE( 3, 3, 0, 0 ) );
    const __m128                        vX6 = _mm_add_ps( vX4, vX5 );
    const __m128                        vX7 = _mm_shuffle_ps( vX6, vX6, _MM_SHUFFLE( 2, 2, 2, 2 ) );
    const __m128                        vx8 = _mm_sqrt_ps( vX7 );
    const __m128                        vX9 = _mm_cmpneq_ps( vX7, KTgINF_V128.m_vF32_04_1 );
    const __m128                        vXA = _mm_div_ps( vLeft, vx8 );
    const __m128                        vXB = _mm_and_ps( vXA, vX9 );

    *ptvRet_Length = vx8;

    return (vXB);
}


/* ---- tgMH_FLR_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_FLR_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    __m128                              vX1;

    vX1[0] = tgPM_FLOOR_F32( vLeft[0] );
    vX1[1] = tgPM_FLOOR_F32( vLeft[1] );
    vX1[2] = tgPM_FLOOR_F32( vLeft[2] );
    vX1[3] = tgPM_FLOOR_F32( vLeft[3] );

    return (vX1);
}


/* ---- tgMH_CEL_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_CEL_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    __m128                              vX1;

    vX1[0] = tgPM_CEIL_F32( vLeft[0] );
    vX1[1] = tgPM_CEIL_F32( vLeft[1] );
    vX1[2] = tgPM_CEIL_F32( vLeft[2] );
    vX1[3] = tgPM_CEIL_F32( vLeft[3] );

    return (vX1);
}


/* ---- tgMH_CLP_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_CLP_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vMin, TgVEC_F32_04_1_C vMax )
{
    return (_mm_max_ps( vMin, _mm_min_ps( vMax, vLeft ) ));
}


/* ---- tgMH_SAT_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_SAT_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    return (tgMH_CLP_F32_04_1( vLeft, KTgZERO_V128.m_vF32_04_1, KTgONE_V128.m_vF32_04_1 ));
}


/* ---- tgMH_NAN_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_NAN_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    return (tgMH_CMP_EQ_F32_04_1( tgMH_AND_F32_04_1( vLeft, KTgNAN_V128.m_vF32_04_1 ), KTgNAN_V128.m_vF32_04_1 ));
}


/* ---- tgMH_BND_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_BND_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vBound )
{
    const __m128                        vX1 = _mm_sub_ps( KTgZERO_V128.m_vF32_04_1, vBound );
    const __m128                        vX2 = _mm_cmpgt_ps( vLeft, vBound );
    const __m128                        vX3 = _mm_cmplt_ps( vLeft, vX1 );

    return (tgMH_XOR_F32_04_1( (_mm_or_ps( vX2, vX3 )), KTgFFFF_V128.m_vF32_04_1 ));
}


/* =============================================================================================================================================================================== */
#endif
