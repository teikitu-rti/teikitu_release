/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Scalar] [F].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_SCALAR_F_H)


#if !defined(TGS_COMMON_MATH_SCALAR_F_H__ONCE)
#define TGS_COMMON_MATH_SCALAR_F_H__ONCE

/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_MATH_SCALAR Scalar Functions
    @ingroup TGS_COMMON_MATH
*/

    /** @defgroup TGS_COMMON_MATH_SCALAR_ALG Algorithm
        @ingroup TGS_COMMON_MATH_SCALAR
    */

    /** @defgroup TGS_COMMON_MATH_SCALAR_ROOT Calculate Root of Polynomial
        @ingroup TGS_COMMON_MATH_SCALAR
    */


/*# !defined(TGS_COMMON_MATH_SCALAR_F_H__ONCE) */
#endif

#if defined(TEMPLATE_TYPE_EXPANSION__RELOAD)

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */


/** @addtogroup TGS_COMMON_MATH_SCALAR_ALG
    @brief Calculate the root of a first degree equation
    @param [in] ARG0 Pointer to an array to hold the root
    @param [in] ARG1 Parameter to be used with the function in ARG2
    @param [in] ARG2 Function pointer
    @param [in] ARG3 Parameter to use for the first evaluation of the function
    @param [in] ARG4 Parameter to use for the second evaluation of the function
    @return True if a root is found, and false otherwise */
TgEXTN TgBOOL
FCN_F(tgMH_BrentZ)(
    VAR_T(PCU) TgANALYSIS_NO_NULL ARG0, TgVOID_PCU ARG1, VAR_T()(*ARG2)( TgVOID_PCU, VAR_T(C) ), VAR_T() ARG3, VAR_T() ARG4 );

/** @addtogroup TGS_COMMON_MATH_SCALAR_ALG
    @brief Calculate the root of a first degree equation
    @param [in] ARG0 Pointer to an array to hold the root
    @param [in] ARG1 Pointer to hold a value of the first function at the root
    @param [in] ARG2 Parameter to be used with the functions in ARG3, ARG4
    @param [in] ARG3 Function pointer
    @param [in] ARG4 Function pointer
    @param [in] ARG5 Minimum of range
    @param [in] ARG6 Value inside of range
    @param [in] ARG7 Maximum of range
    @return True if a root is found, and false otherwise */
TgEXTN TgBOOL
FCN_F(tgMH_BrentD)(
    VAR_T(PCU) TgANALYSIS_NO_NULL ARG0, VAR_T(PCU) TgANALYSIS_NO_NULL ARG1, TgVOID_PCU ARG2, VAR_T()(*ARG3)( TgVOID_PCU, VAR_T(C) ), VAR_T()(*ARG4)( TgVOID_PCU, VAR_T(C) ), VAR_T() ARG5, VAR_T() ARG6,
    VAR_T() ARG7 );




/** @addtogroup TGS_COMMON_MATH_SCALAR_ROOT
    @brief Calculate the root of a first degree equation*/
/** @param [in] ARG0 Pointer to an array to hold the found roots (maximum of one)
    @param [in] ARG1 Pointer to an integer to hold the number of roots found
    @param [in] ARG2 Scalar value for the zero degree coefficient
    @param [in] ARG3 Scalar value for the first degree coefficient
    @return True if a root is found, and false otherwise */
TgEXTN TgBOOL
FCN_F(tgMH_Calc_Root_1)(
    VAR_T(PCU) TgANALYSIS_NO_NULL ARG0, TgSINT_E32_PCU ARG1, VAR_T() ARG2, VAR_T() ARG3 );

/** @addtogroup TGS_COMMON_MATH_SCALAR_ROOT
    @brief Calculate the root of a second degree equation*/
/** @param [in] ARG0 Pointer to an array to hold the found roots (maximum of second)
    @param [in] ARG1 Pointer to an integer to hold the number of roots found
    @param [in] ARG2 Scalar value for the zero degree coefficient
    @param [in] ARG3 Scalar value for the first degree coefficient
    @param [in] ARG4 Scalar value for the second degree coefficient
    @return True if a root is found, and false otherwise */
TgEXTN TgBOOL
FCN_F(tgMH_Calc_Root_2)(
    VAR_T(PCU) TgANALYSIS_NO_NULL ARG0, TgSINT_E32_PCU ARG1, VAR_T() ARG2, VAR_T() ARG3, VAR_T() ARG4 );

/** @addtogroup TGS_COMMON_MATH_SCALAR_ROOT
    @brief Calculate the root of a third degree equation*/
/** @param [in] ARG0 Pointer to an array to hold the found roots (maximum of three)
    @param [in] ARG1 Pointer to an integer to hold the number of roots found
    @param [in] ARG2 Scalar value for the zero degree coefficient
    @param [in] ARG3 Scalar value for the first degree coefficient
    @param [in] ARG4 Scalar value for the second degree coefficient
    @param [in] ARG5 Scalar value for the third degree coefficient
    @return True if a root is found, and false otherwise */
TgEXTN TgBOOL
FCN_F(tgMH_Calc_Root_3)(
    VAR_T(PCU) TgANALYSIS_NO_NULL ARG0, TgSINT_E32_PCU ARG1, VAR_T() ARG2, VAR_T() ARG3, VAR_T() ARG4, VAR_T() ARG5 );

/** @addtogroup TGS_COMMON_MATH_SCALAR_ROOT
    @brief Calculate the root of a fourth degree equation*/
/** @param [in] ARG0 Pointer to an array to hold the found roots (maximum of four)
    @param [in] ARG1 Pointer to an integer to hold the number of roots found
    @param [in] ARG2 Scalar value for the zero degree coefficient
    @param [in] ARG3 Scalar value for the first degree coefficient
    @param [in] ARG4 Scalar value for the second degree coefficient
    @param [in] ARG5 Scalar value for the third degree coefficient
    @param [in] ARG6 Scalar value for the fourth degree coefficient
    @return True if a root is found, and false otherwise */
TgEXTN TgBOOL
FCN_F(tgMH_Calc_Root_4)(
    VAR_T(PCU) TgANALYSIS_NO_NULL ARG0,TgSINT_E32_PCU ARG1,VAR_T() ARG2,VAR_T() ARG3,VAR_T() ARG4,VAR_T() ARG5,VAR_T() ARG6 );


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */

/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TEMPLATE__TYPE_SIZE 64
    #include __FILE__

    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COMMON_MATH_SCALAR_F_H) */
#endif
