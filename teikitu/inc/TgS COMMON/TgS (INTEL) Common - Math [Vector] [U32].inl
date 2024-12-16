/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (X86_64) Common - Math [Vector] [U32].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_API_VECTOR_U32_INL)
#define TGS_COMMON_MATH_API_VECTOR_U32_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgMH_SETU_U32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
CLANG_WARN_DISABLE_PUSH(cast-align)
TgINLINE TgVEC_U32_04_1 tgMH_SETU_U32_04_1( TgUINT_F32_CPCU puiVal )
{
    return (_mm_loadu_si128( (__m128i const *)puiVal ));
}
CLANG_WARN_DISABLE_POP()


/* ---- tgMH_SETA_U32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
CLANG_WARN_DISABLE_PUSH(cast-align)
TgINLINE TgVEC_U32_04_1 tgMH_SETA_U32_04_1( TgUINT_F32_CPCU puiVal )
{
    return (_mm_load_si128( (__m128i const *)puiVal ));
}
CLANG_WARN_DISABLE_POP()


/* ---- tgMH_SET1_U32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_SET1_U32_04_1( TgUINT_F32_C uiVal )
{
    return (_mm_set1_epi32( *(int32_t const *)&uiVal ));
}


/* ---- tgMH_SET4_U32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_SET4_U32_04_1( TgUINT_F32_C uiX, TgUINT_F32_C uiY, TgUINT_F32_C uiZ, TgUINT_F32_C uiW )
{
    return (_mm_set_epi32( (int)uiW,(int)uiZ, (int)uiY, (int)uiX ));
}


/* ---- tgMH_RAND_U32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_RAND_U32_04_1( TgVOID )
{
    TgUN_V128                           vResult;

    vResult.m_vS_U32_04_1 = tgMH_RAND_S_U32_04_1();
    return (vResult.m_vU32_04_1);
}


/* ---- tgMH_SEL_U32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_SEL_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight, TgVEC_U32_04_1_C tuvMask )
{
    return (_mm_or_si128( _mm_and_si128( vLeft, _mm_xor_si128( KTgFFFF_V128.m_vU32_04_1, tuvMask ) ), _mm_and_si128( vRight, tuvMask ) ));
}


/* ---- tgMH_AND_U32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_AND_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    return (_mm_and_si128( vLeft, vRight ));
}


/* ---- tgMH_OR_U32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_OR_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    return (_mm_or_si128( vLeft, vRight ));
}


/* ---- tgMH_XOR_U32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_XOR_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    return (_mm_xor_si128( vLeft, vRight ));
}


/* ---- tgMH_MAX_U32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_MAX_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    return (_mm_max_epu32( vLeft, vRight ));
}


/* ---- tgMH_MIN_U32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_MIN_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    return (_mm_min_epu32( vLeft, vRight ));
}


/* ---- tgMH_ABS_U32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_ABS_U32_04_1( TgVEC_U32_04_1_C v0 )
{
    return (_mm_sign_epi32( v0, v0 ));
}


/* ---- tgMH_SGN_U32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_SGN_U32_04_1( TgVEC_U32_04_1_C v0 )
{
    return (_mm_sign_epi32( _mm_set1_epi32(1), v0 ));
}


/* ---- tgMH_CMP_EQ_U32_04_1 --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_CMP_EQ_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    return (_mm_cmpeq_epi32( vLeft, vRight ));
}


/* ---- tgMH_CMP_NE_U32_04_1 --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_CMP_NE_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    return (_mm_xor_si128( KTgFFFF_V128.m_vU32_04_1, _mm_cmpeq_epi32( vLeft, vRight ) ));
}


/* ---- tgMH_CMP_GE_U32_04_1 --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_CMP_GE_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    return _mm_cmpeq_epi32(_mm_max_epu32(vLeft, vRight), vLeft);
}


/* ---- tgMH_CMP_GT_U32_04_1 --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_CMP_GT_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    return _mm_andnot_si128(_mm_cmpeq_epi32(_mm_min_epu32(vLeft, vRight), vLeft), _mm_set1_epi32(-1));
}


/* ---- tgMH_CMP_LE_U32_04_1 --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_CMP_LE_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    return _mm_cmpeq_epi32(_mm_min_epu32(vLeft, vRight), vLeft);
}


/* ---- tgMH_CMP_LT_U32_04_1 --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_CMP_LT_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    return (tgMH_CMP_GT_U32_04_1( vRight, vLeft ));
}


/* ---- tgMH_CMP_ALL_TO_BOOL_U32_04_1 ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgMH_CMP_ALL_TO_BOOL_U32_04_1( TgVEC_U32_04_1_C vARG )
{
    return (0 == _mm_test_all_ones( vARG ) ? false : true);
}


/* ---- tgMH_ADD_CLP_U32_04_1 ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_ADD_CLP_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    TgUN_V128                           vResult;

    vResult.m_vS_U32_04_1 = tgMH_ADD_CLP_S_U32_04_1( *(TgVEC_S_U32_04_1_CP)&vLeft, *(TgVEC_S_U32_04_1_CP)&vRight );
    return (vResult.m_vU32_04_1);
}


/* ---- tgMH_ADD_U32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_ADD_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    TgUN_V128                           vResult;

    vResult.m_vS_U32_04_1 = tgMH_ADD_S_U32_04_1( *(TgVEC_S_U32_04_1_CP)&vLeft, *(TgVEC_S_U32_04_1_CP)&vRight );
    return (vResult.m_vU32_04_1);
}


/* ---- tgMH_SUB_CLP_U32_04_1 ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_SUB_CLP_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    TgUN_V128                           vResult;

    vResult.m_vS_U32_04_1 = tgMH_SUB_CLP_S_U32_04_1( *(TgVEC_S_U32_04_1_CP)&vLeft, *(TgVEC_S_U32_04_1_CP)&vRight );
    return (vResult.m_vU32_04_1);
}


/* ---- tgMH_SUB_U32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_SUB_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    TgUN_V128                           vResult;

    vResult.m_vS_U32_04_1 = tgMH_SUB_S_U32_04_1( *(TgVEC_S_U32_04_1_CP)&vLeft, *(TgVEC_S_U32_04_1_CP)&vRight );
    return (vResult.m_vU32_04_1);
}


/* ---- tgMH_AVG_U32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_U32_04_1 tgMH_AVG_U32_04_1( TgVEC_U32_04_1_C vLeft, TgVEC_U32_04_1_C vRight )
{
    TgUN_V128                           vResult;

    vResult.m_vS_U32_04_1 = tgMH_AVG_S_U32_04_1( *(TgVEC_S_U32_04_1_CP)&vLeft, *(TgVEC_S_U32_04_1_CP)&vRight );
    return (vResult.m_vU32_04_1);
}


/* =============================================================================================================================================================================== */
#endif
