/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Matrix] [F] [44].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_MATRIX_F_44_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store the concatenation (multiplication) of the two arguments (ARG1 x ARG2)
    @param [out] OUT0 Destination matrix
    @param [in] ARG1 Matrix
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_CAT_34_44)(
    VEC_T(4,PC) TgANALYSIS_NO_NULL OUT0, VEC_T(3,CPC) TgANALYSIS_NO_NULL ARG1, VEC_T(4,CPC) TgANALYSIS_NO_NULL ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store the concatenation (multiplication) of the two arguments (ARG1 x ARG2)
    @param [out] OUT0 Destination matrix
    @param [in] ARG1 Matrix
    @param [in] ARG2 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_CAT_44_34)(
    VEC_T(4,PC) TgANALYSIS_NO_NULL OUT0, VEC_T(4,CPC) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPC) TgANALYSIS_NO_NULL ARG2 );

/** @addtogroup TGS_COMMON_MATH_VECTOR_CALC
    @brief Store the transpose of the matrix ARG1
    @param [out] OUT0 Destination matrix
    @param [in] ARG1 Matrix */
TgINLINE TgVOID
FCN_M(tgMH_TR)(
    VEC_T(4,PC) TgANALYSIS_NO_NULL OUT0, VEC_T(4,CPC) TgANALYSIS_NO_NULL ARG1 );


/* =============================================================================================================================================================================== */
#endif
