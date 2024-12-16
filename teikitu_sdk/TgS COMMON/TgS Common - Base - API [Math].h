/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - API [Math].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_API_MATH_H)
#if defined(TEMPLATE_TYPE_EXPANSION__RELOAD)

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#define FCM(A) TgMACRO_CONCAT5(tgCM_, A, _, GENERATE__TYPE_SYMBOL, GENERATE__TYPE_SIZE_TEXT)
#define FPM(A) TgMACRO_CONCAT5(tgPM_, A, _, GENERATE__TYPE_SYMBOL, GENERATE__TYPE_SIZE_TEXT)


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/** @addtogroup TGS_COMMON_MATH */
/** @{ */

/** @brief Swap the values of the two parameters
    @param [in,out] OUT0 Pointer to a value of the function type
    @param [in,out] OUT1 Pointer to a value of the function type */
TgINLINE TgVOID
FCM(SWP)(
    VAR_T(PCU) TgANALYSIS_NO_NULL OUT0, VAR_T(PCU) TgANALYSIS_NO_NULL OUT1 );

/** @return The sign of the value in ARG [-1 for negative, 1 for positive and 0 otherwise]
    @param [in] ARG A value of the function type */
TgINLINE VAR_T()
FCM(SGN)(
    VAR_T(C) ARG );

/** @return Max value of the two parameters
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 A value of the function type */
TgINLINE VAR_T()
FCM(MAX)(
    VAR_T(C) ARG0, VAR_T(C) ARG1 );

/** @return Min value of the two parameters
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 A value of the function type */
TgINLINE VAR_T()
FCM(MIN)(
    VAR_T(C) ARG0, VAR_T(C) ARG1 );

/** @return The closest value to ARG0 limited to the range of [ARG1, ARG2]
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 Minimum value of the clamped region
    @param [in] ARG2 Maximum value of the clamped region */
TgINLINE VAR_T()
FCM(CLP)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 );

/** @return The maximum of the two parameters, a clamp to the region of [ARG1, ∞)
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 Minimum value of the clamped region */
TgINLINE VAR_T()
FCM(CLP_MIN)(
    VAR_T(C) ARG0, VAR_T(C) ARG1 );

/** @return The minimum of the two parameters, a clamp to the region of (∞, ARG1]
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 Maximum value of the clamped region */
TgINLINE VAR_T()
FCM(CLP_MAX)(
    VAR_T(C) ARG0, VAR_T(C) ARG1 );

/** @return The absolute value of the parameter value in ARG
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(ABS)(
    VAR_T(C) ARG );

/** @return A random number ranging from [MIN,MAX] */
TgINLINE VAR_T()
FCM(RAND)( TgVOID );

#if defined(TEMPLATE__ENABLE_INTEGER)
/** @return The closest multiple of ARG1 (a power of two value) that is less than or equal to the parameter in ARG0
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 Alignment value that is a power of two */
TgINLINE VAR_T()
FCM(FLR_ALGN_PW2)(
    VAR_T(C) ARG0, VAR_T(C) ARG1 );

/** @return The closest multiple of ARG1 (a power of two value) that is greater than or equal to the parameter in ARG0
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 Alignment value that is a power of two */
TgINLINE VAR_T()
FCM(CEL_ALGN_PW2)(
    VAR_T(C) ARG0, VAR_T(C) ARG1 );

/** @return The nearest power of two that is less than or equal to parameter in ARG0
    @param [in] ARG A value of the function type */
TgINLINE VAR_T()
FCM(PRV_PW2)(
    VAR_T(C) ARG );

/** @return The nearest power of two that is greater than or equal to parameter in ARG0
    @param [in] ARG A value of the function type */
TgINLINE VAR_T()
FCM(NXT_PW2)(
    VAR_T(C) ARG );

/** @return Boolean test to determine if parameter in ARG is a power of two
    @param [in] ARG A value of the function type */
TgINLINE TgBOOL
FCM(IS_PW2)(
    VAR_T(C) ARG );

#if defined(TEMPLATE__ENABLE_UNSIGNED)
/** @return Return the number of bits after the first set bit scanning from lowest to highest significance in ARG*/
/** @param [in] ARG A value of the function type */
TgINLINE TgSINT_E08
FPM(BSF)(
    VAR_T() ARG );

/** @return Return the number of bits after the first set bit scanning from highest to lowest significance in ARG
    @param [in] ARG A value of the function type */
TgINLINE TgSINT_E08
FPM(BSR)(
    VAR_T() ARG );
#endif



/*# defined(TEMPLATE__ENABLE_INTEGER) */
#else



/** @return True if the value is "near" [within EPSILON] zero and false otherwise
    @param [in] ARG A value of the function type */
TgINLINE TgBOOL
FCM(NR0)(
    VAR_T(C) ARG );

/** @return True if the value is "near" [within EPSILON] one and false otherwise
    @param [in] ARG A value of the function type */
TgINLINE TgBOOL
FCM(NR1)(
    VAR_T(C) ARG );

/** @return ARG0 / ARG1 clamped to the region of [0.1]
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 A value of the function type */
TgINLINE VAR_T()
FCM(CLP_FRC)(
    VAR_T(C) ARG0, VAR_T(C) ARG1 );

/** @return Linear interpolation / extrapolation [ARG0 + ARG2*(ARG1 - ARG0)]*/
/** @param [in] ARG0 A value of the function type
    @param [in] ARG1 A value of the function type
    @param [in] ARG2 Interpolant / extrapolant */
TgINLINE VAR_T()
FCM(LRP)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 );

/** @return True if ARG0 and ARG1 are within tolerance equal to each other (determined by (ARG0/ARG1)-1 < ARG2)
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 A value of the function type
    @param [in] ARG1 Tolerance */
TgINLINE TgBOOL
FCM(EQ)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 );


/** @return True if parameter in ARG is a valid and finite number and false otherwise
    @param [in] ARG A value of the function type */
TgEXTN TgBOOL
FPM(NAN)(
    VAR_T(C) ARG );

/** @return The closest integer value equal to or greater than the parameter in ARG
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(CEIL)(
    VAR_T(C) ARG );

/** @return The closest integer value equal to or less than the parameter in ARG
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(FLOOR)(
    VAR_T(C) ARG );

/** @return The sine of the parameter in ARG
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(SIN)(
    VAR_T(C) ARG );

/** @return The cosine of the parameter in ARG
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(COS)(
    VAR_T(C) ARG );

/** @brief Return the sine of parameter in ARG2 in ARG0 and the cosine in ARG1
    @param [out] OUT0 Pointer to an output value
    @param [out] OUT1 Pointer to an output value
    @param [in] ARG2 A value of the function type */
TgINLINE TgVOID
FPM(SINCOS)(
    VAR_T(PCU) TgANALYSIS_NO_NULL OUT0, VAR_T(PCU) TgANALYSIS_NO_NULL OUT1, VAR_T(C) ARG2 );

/** @return Tangent of the parameter in ARG
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(TAN)(
    VAR_T(C) ARG );

/** @return Arc sine of the parameter in ARG
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(ASIN)(
    VAR_T(C) ARG );

/** @return Arc cosine of the parameter in ARG
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(ACOS)(
    VAR_T(C) ARG );

/** @return Arc tangent of the parameter in ARG
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(ATAN)(
    VAR_T(C) ARG );

/** @return Arc tan2 of the parameter in ARG
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 A value of the function type */
TgEXTN VAR_T()
FPM(ATAN2)(
    VAR_T(C) ARG0, VAR_T(C) ARG1 );

/** @return The result of base (ARG0) to the power of exponent (ARG1)
    @param [in] ARG0 Value representing the base of the power function
    @param [in] ARG1 Value representing the exponent of the power function */
TgEXTN VAR_T()
FPM(POW)(
    VAR_T(C) ARG0, VAR_T(C) ARG1 );

/** @return The square-root of the parameter in ARG
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(SQRT)(
    VAR_T(C) ARG );

/** @return The result of natural exponential function where parameter in ARG is the exponent
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(EXP)(
    VAR_T(C) ARG );

/** @return Natural logarithm of the parameter in ARG
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(LN)(
    VAR_T(C) ARG );

/** @return Logarithm of the parameter in ARG
    @param [in] ARG A value of the function type */
TgEXTN VAR_T()
FPM(LOG)(
    VAR_T(C) ARG );

/** @return Result of ARG0 modulo ARG1
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 A value of the function type */
TgEXTN VAR_T()
FPM(FMOD)(
    VAR_T(C) ARG0, VAR_T(C) ARG1 );

/** @return Fused multiple-add at full precision of the floating point unit [(ARG0*ARG1) + ARG2]
    @param [in] ARG0 Multiplican
    @param [in] ARG1 Multiplican
    @param [in] ARG2 Addition term */
TgINLINE VAR_T()
FPM(FMA)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 );

/** @return A value with magnitude of ARG0 and the sign of ARG1
    @param [in] ARG0 A value of the function type
    @param [in] ARG1 A value of the function type */
TgEXTN VAR_T()
FPM(COPY_SIGN)(
    VAR_T(C) ARG0, VAR_T(C) ARG1 );

/** @return ARG1 when ARG0 is greater than zero, and ARG2 otherwise [ARG0 >= TYPE_K(0)) ? ARG1 : ARG2]
    @param [in] ARG0 Float value to be compared with zero.
    @param [in] ARG1 Float value to be used if ARG0 is greater than or equal to zero.
    @param [in] ARG2 Float value to be used if ARG0 is less than zero or is a NaN. */
TgINLINE VAR_T()
FPM(FSEL)(
    VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 );

/*# defined(TEMPLATE__ENABLE_INTEGER) */
#endif

/** @} */


/* =============================================================================================================================================================================== */

/* MACROS defined in this file */
#undef FPM
#undef FCM

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

TgINLINE TgFLOAT32
tgCM_RAND_ONE_F32( TgVOID );

TgINLINE TgFLOAT64
tgCM_RAND_ONE_F64( TgVOID );

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TEMPLATE__ENABLE_INTEGER
    #define TEMPLATE__ENABLE_UNSIGNED

    #define TEMPLATE__TYPE_SIZE 8
    #include __FILE__
    #define TEMPLATE__TYPE_SIZE 16
    #include __FILE__
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__
    #define TEMPLATE__TYPE_SIZE 64
    #include __FILE__
    #define TEMPLATE__OVERRIDE_INT_TYPE PTR
    #include __FILE__
    #define TEMPLATE__OVERRIDE_INT_TYPE MAX
    #include __FILE__

    #undef TEMPLATE__ENABLE_UNSIGNED

    #define TEMPLATE__TYPE_SIZE 8
    #include __FILE__
    #define TEMPLATE__TYPE_SIZE 16
    #include __FILE__
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__
    #define TEMPLATE__TYPE_SIZE 64
    #include __FILE__
    #define TEMPLATE__OVERRIDE_INT_TYPE PTR
    #include __FILE__
    #define TEMPLATE__OVERRIDE_INT_TYPE MAX
    #include __FILE__

    #undef TEMPLATE__ENABLE_INTEGER

    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__
    #define TEMPLATE__TYPE_SIZE 64
    #include __FILE__

    #define TGS_COMMON_BASE_API_MATH_H
    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COMMON_BASE_API_MATH_H) */
#endif
