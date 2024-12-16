/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math API [Matrix] [S] [F] [34].h_inc
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

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store the transpose of the matrix ARG1
    @param [out] OUT0 Destination matrix
    @param [in] ARG1 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_TR_S)(
    VEC_S_T(4,PCU) NONULL OUT0, MAT_S_T(CPCU) NONULL ARG1 );




/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store a left-handed view matrix
    @param [out] OUT0 Destination matrix
    @param [in] ARG1 Vector, Eye Position
    @param [in] ARG2 Vector, Look at Position
    @param [in] ARG3 Vector, Camera Up Direction */
TgINLINE TgVOID
FCN_M(tgMH_LookLH_S)(
    MAT_S_T(PCU) NONULL OUT0, VEC_S_T(1,C) ARG1, VEC_S_T(1,C) ARG2, VEC_S_T(1,C) ARG3 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store a right-handed view matrix
    @param [out] OUT0 Destination matrix
    @param [in] ARG1 Vector, Eye Position
    @param [in] ARG2 Vector, Look at Position
    @param [in] ARG3 Vector, Camera Up Direction */
TgINLINE TgVOID
FCN_M(tgMH_LookRH_S)(
    MAT_S_T(PCU) NONULL OUT0, VEC_S_T(1,C) ARG1, VEC_S_T(1,C) ARG2, VEC_S_T(1,C) ARG3 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store a left-handed view matrix
    @param [out] OUT0 Destination matrix
    @param [in] ARG1 Vector, Eye Position
    @param [in] ARG2 Vector, Look at Position
    @param [in] ARG3 Vector, Camera Up Direction */
TgINLINE TgVOID
FCN_M(tgMH_Look_S)(
    MAT_S_T(PCU) NONULL OUT0, VEC_S_T(1,C) ARG1, VEC_S_T(1,C) ARG2, VEC_S_T(1,C) ARG3 );


/* =============================================================================================================================================================================== */
#endif
