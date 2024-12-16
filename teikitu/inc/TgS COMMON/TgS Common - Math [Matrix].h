/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math API [Matrix].h_inc
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_API_VECTOR_FXX_04_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOAD
    @brief Clear (set each element to zero) the destination
    @param [out] OUT Destination matrix */
TgINLINE TgVOID
FCN_M(tgMH_CLR)(
    MAT_T(PC) NONULL OUT );




/** @addtogroup TGS_COMMON_MATH_VECTOR_LOGICAL
    @brief Store a matrix where each element is the maximum of the corresponding elements in the argument matrices
    @param [out] OUT0 Destination Matrix
    @param [in] ARG1 Matrix
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_MAX)(
    MAT_T(PC) NONULL OUT0, MAT_T(CPC) NONULL ARG1, MAT_T(CPC) NONULL ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOGICAL
    @brief Store a matrix where each element is the minimum of the corresponding elements in the argument matrices
    @param [out] OUT0 Destination Matrix
    @param [in] ARG1 Matrix
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_MIN)(
    MAT_T(PC) NONULL OUT0, MAT_T(CPC) NONULL ARG1, MAT_T(CPC) NONULL ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOGICAL
    @brief Store the result of a bit-wise and between both arguments
    @param [out] OUT0 Destination Matrix
    @param [in] ARG1 Matrix
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_AND)(
    MAT_T(PC) NONULL OUT0, MAT_T(CPC) NONULL ARG1, MAT_T(CPC) NONULL ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOGICAL
    @brief Store the result of a bit-wise or between both arguments
    @param [out] OUT0 Destination Matrix
    @param [in] ARG1 Matrix
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_OR)(
    MAT_T(PC) NONULL OUT0, MAT_T(CPC) NONULL ARG1, MAT_T(CPC) NONULL ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_LOGICAL
    @brief Store the result of a bit-wise xor between both arguments
    @param [out] OUT0 Destination Matrix
    @param [in] ARG1 Matrix
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_XOR)(
    MAT_T(PC) NONULL OUT0, MAT_T(CPC) NONULL ARG1, MAT_T(CPC) NONULL ARG2 );


/* =============================================================================================================================================================================== */
#endif
