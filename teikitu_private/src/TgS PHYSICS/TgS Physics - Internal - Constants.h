/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Internal - Constants.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_INTERNAL_CONSTANTS_H)
#define TGS_PHYSICS_INTERNAL_CONSTANTS_H
#pragma once


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

enum { ETgPH_COMMAND__CLIENT_TO_UPDATE__BYTE_MAX      = 512*1024 };
enum { ETgPH_COMMAND__TO_CLIENT__BYTE_MAX             = 128*1024 };
enum {
       /* PA GRAPH requires last two bits, 0-47 are intersection test (0 != CategeoryA & CollideB && 0 != CategeoryB & CollideA),
          48-61 are union tests (0 != CategeoryA & CollideB || 0 != CategeoryB & CollideA) */

       KTgPH_CATEGORY_BIT__FORM_IS_UPDATING_GRAPH   = KTgPA_CATEGORY_BIT__RESERVED__USER_0,
       KTgPH_CATEGORY_BIT__FORM_IS_UPDATING         = KTgPA_CATEGORY_BIT__LAST_OR_BIT,
       KTgPH_CATEGORY_BIT__ENABLE_COLLSION          = 0,

       KTgPH_CACHE_BIT__FORM_IS_UPDATING_GRAPH      = 0,
       KTgPH_CACHE_BIT__FORM_IS_UPDATING            = 1,
       KTgPH_CACHE_BIT__ENABLE_COLLSION             = 2,
       KTgPH_CACHE_BIT__VALID_PA_ID                 = 3,
       KTgPH_CACHE_BIT__TOTAL_REQUIRED              = 4,
       KTgPH_CACHE_BIT__TOTAL_RESERVED              = 4,
};



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Constants                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

typedef enum TgCLANG_ATTRIBUTE(enum_extensibility(closed))
{
    ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_LINEAR_BODY_0 = 0,
    ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_ANGULAR_BODY_0,
    ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_LINEAR_BODY_1,
    ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_ANGULAR_BODY_1,
    ETgPH_PROBLEM_COEFFICIENT_INDEX__MIN_MAX_CFM_RHS,
    ETgPH_PROBLEM_COEFFICIENT_INDEX__RECIPROCAL_A_DIAGONAL, /**< RE: See Notes for Reference. A is the matrix J*(M⁻¹)*(Jᵀ) */
    ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_RESULT_FACTOR_LINEAR_BODY_0,
    ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_RESULT_FACTOR_ANGULAR_BODY_0,
    ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_RESULT_FACTOR_LINEAR_BODY_1,
    ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_RESULT_FACTOR_ANGULAR_BODY_1,
    ETgPH_PROBLEM_COEFFICIENT_INDEX__VECTORS_PER_DOF,

    ETgPH_PCI__JACOBIAN_LIN_BY_0 = ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_LINEAR_BODY_0,
    ETgPH_PCI__JACOBIAN_ANG_BY_0 = ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_ANGULAR_BODY_0,
    ETgPH_PCI__JACOBIAN_LIN_BY_1 = ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_LINEAR_BODY_1,
    ETgPH_PCI__JACOBIAN_ANG_BY_1 = ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_ANGULAR_BODY_1,
    ETgPH_PCI__MIN_MAX_CFM_RHS = ETgPH_PROBLEM_COEFFICIENT_INDEX__MIN_MAX_CFM_RHS,
#if defined(TgBUILD_FEATURE__PHYSICS__CFM)
    ETgPH_PCI__RCP_A_DIAG = ETgPH_PROBLEM_COEFFICIENT_INDEX__RECIPROCAL_A_DIAGONAL,
#endif
    ETgPH_PCI__J_LIN_RESULT_MULT_BY_0 = ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_RESULT_FACTOR_LINEAR_BODY_0,
    ETgPH_PCI__J_ANG_RESULT_MULT_BY_0 = ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_RESULT_FACTOR_ANGULAR_BODY_0,
    ETgPH_PCI__J_LIN_RESULT_MULT_BY_1 = ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_RESULT_FACTOR_LINEAR_BODY_1,
    ETgPH_PCI__J_ANG_RESULT_MULT_BY_1 = ETgPH_PROBLEM_COEFFICIENT_INDEX__JACOBIAN_RESULT_FACTOR_ANGULAR_BODY_1,
    ETgPH_PCI__VEC_PER_DOF = ETgPH_PROBLEM_COEFFICIENT_INDEX__VECTORS_PER_DOF

} ETgPH_PROBLEM_COEFFICIENT_INDEX_ENUM;
TgTYPE_DECLARE( TgSINT_E32, ETgPH_PROBLEM_COEFFICIENT_INDEX );

TgEXTN TgVEC_F32_04_1_C                    KTgPH_MAX_LIN_SPEED;
TgEXTN TgVEC_F32_04_1_C                    KTgPH_MAX_ANG_SPEED;




/* =============================================================================================================================================================================== */
#endif
