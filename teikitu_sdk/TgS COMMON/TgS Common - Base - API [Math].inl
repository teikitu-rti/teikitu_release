/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - API [Math].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_API_MATH_INL)


/* == Common ===================================================================================================================================================================== */

#if !defined(TGS_COMMON_BASE_API_MATH_INL__ONCE)
#define TGS_COMMON_BASE_API_MATH_INL__ONCE

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_RAND_F32 ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgFLOAT32 tgCM_RAND_F32( TgVOID )
{
    TgUINT_E32_C                            uiMantissa = tgCM_RAND_MT_U32(); /* 24 bits - 1 sign bit, and 23 bits for mantissa */
    TgUINT_E32_C                            uiExponent = tgCM_RAND_MT_U32(); /* 8 bits for the exponent */

    TgSINT_E32_C                            iMantissa_Numerator = *(TgSINT_E32_CP)&uiMantissa;
    TgFLOAT32_C                             fMantissa_Numerator = (TgFLOAT32)iMantissa_Numerator;
    TgUINT_E32_C                            uiMantissa_Denominator = (TgUINT_E32)KTgMAX_S32 + 1;
    TgFLOAT32_C                             fMantissa_Denominator = (TgFLOAT32)uiMantissa_Denominator;

    TgFLOAT32_C                             fMantissa = fMantissa_Numerator / fMantissa_Denominator;

    TgSINT_E32_C                            iExponent_Numerator = *(TgSINT_E32_CP)&uiExponent;
    TgFLOAT32_C                             fExponent_Numerator = (TgFLOAT32)iExponent_Numerator;
    TgUINT_E32_C                            uiExponent_Denominator = (KTgMAX_S32 >> 4) + 1;
    TgFLOAT32_C                             fExponent_Denominator = (TgFLOAT32)uiExponent_Denominator;

    TgFLOAT32_C                             fExponent = fExponent_Numerator / fExponent_Denominator;

    TgERROR((fMantissa >= -1.0F) && (fMantissa <= 1.0F));
    TgERROR((fExponent >= -32.0F) && (fExponent <= 32.0F));

    return (fMantissa * fExponent);
}


/* ---- tgCM_RAND_ONE_F32 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgFLOAT32 tgCM_RAND_ONE_F32( TgVOID )
{
    TgUINT_E32_C                            uiMantissa = tgCM_RAND_MT_U32(); /* 24 bits - 1 sign bit, and 23 bits for mantissa */

    TgSINT_E32_C                            iMantissa_Numerator = *(TgSINT_E32_CP)&uiMantissa;
    TgFLOAT32_C                             fMantissa_Numerator = (TgFLOAT32)iMantissa_Numerator;
    TgUINT_E32_C                            uiMantissa_Denominator = (TgUINT_E32)KTgMAX_S32 + 1;
    TgFLOAT32_C                             fMantissa_Denominator = (TgFLOAT32)uiMantissa_Denominator;

    TgFLOAT32_C                             fMantissa = fMantissa_Numerator / fMantissa_Denominator;

    TgERROR((fMantissa >= -1.0F) && (fMantissa <= 1.0F));

    return (fMantissa);
}


/* ---- tgCM_RAND_F64 ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgFLOAT64 tgCM_RAND_F64( TgVOID )
{
    TgUINT_E64_C                            uiMantissa_0 = tgCM_RAND_MT_U32();
    TgUINT_E64_C                            uiMantissa_1 = tgCM_RAND_MT_U32();
    TgUINT_E64_C                            uiMantissa = uiMantissa_0 + (uiMantissa_1 << 32); /* 53 bits - 1 sign bit, and 52 bits for mantissa */
    TgUINT_E64_C                            uiExponent = (TgUINT_E64)tgCM_RAND_MT_U32() << 32; /* 11 bits for the exponent, bit shift for sign bit */

    TgSINT_E64_C                            iMantissa_Numerator = *(TgSINT_E64_CP)&uiMantissa;
    TgFLOAT64_C                             fMantissa_Numerator = (TgFLOAT64)iMantissa_Numerator;
    TgUINT_E64_C                            uiMantissa_Denominator = (TgUINT_E64)KTgMAX_S64 + 1;
    TgFLOAT64_C                             fMantissa_Denominator = (TgFLOAT64)uiMantissa_Denominator;

    TgFLOAT64_C                             fMantissa = fMantissa_Numerator / fMantissa_Denominator;

    TgSINT_E64_C                            iExponent_Numerator = *(TgSINT_E64_CP)&uiExponent;
    TgFLOAT64_C                             fExponent_Numerator = (TgFLOAT64)iExponent_Numerator;
    TgUINT_E64_C                            uiExponent_Denominator = (KTgMAX_S64 >> 7) + 1;
    TgFLOAT64_C                             fExponent_Denominator = (TgFLOAT64)uiExponent_Denominator;

    TgFLOAT64_C                             fExponent = fExponent_Numerator / fExponent_Denominator;

    TgERROR((fMantissa >= -1.0) && (fMantissa <= 1.0));
    TgERROR((fExponent >= -256.0) && (fExponent <= 256.0));

    return (fMantissa * fExponent);
}


/* ---- tgCM_RAND_ONE_F64 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgFLOAT64 tgCM_RAND_ONE_F64( TgVOID )
{
    TgUINT_E64_C                            uiMantissa_0 = tgCM_RAND_MT_U32();
    TgUINT_E64_C                            uiMantissa_1 = tgCM_RAND_MT_U32();
    TgUINT_E64_C                            uiMantissa = uiMantissa_0 + (uiMantissa_1 << 32); /* 53 bits - 1 sign bit, and 52 bits for mantissa */

    TgSINT_E64_C                            iMantissa_Numerator = *(TgSINT_E64_CP)&uiMantissa;
    TgFLOAT64_C                             fMantissa_Numerator = (TgFLOAT64)iMantissa_Numerator;
    TgUINT_E64_C                            uiMantissa_Denominator = (TgUINT_E64)KTgMAX_S64 + 1;
    TgFLOAT64_C                             fMantissa_Denominator = (TgFLOAT64)uiMantissa_Denominator;

    TgFLOAT64_C                             fMantissa = fMantissa_Numerator / fMantissa_Denominator;

    TgERROR((fMantissa >= -1.0) && (fMantissa <= 1.0));

    return (fMantissa);
}

/*# !defined(TGS_COMMON_BASE_API_MATH_INL__ONCE) */
#endif


/* == Common ===================================================================================================================================================================== */

#if defined(TEMPLATE_TYPE_EXPANSION__RELOAD)

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#define FCM(A) TgMACRO_CONCAT5(tgCM_, A, _, GENERATE__TYPE_SYMBOL, GENERATE__TYPE_SIZE_TEXT)
#define FPM(A) TgMACRO_CONCAT5(tgPM_, A, _, GENERATE__TYPE_SYMBOL, GENERATE__TYPE_SIZE_TEXT)


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCM(SWP) ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCM(SWP)( VAR_T(PCU) OUT0, VAR_T(PCU) OUT1 )
{
    VAR_T() const uiTemp = *OUT0;
    *OUT0 = *OUT1;
    *OUT1 = uiTemp;
}


/* ---- FCM(SGN) ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(SGN)( VAR_T(C) ARG )
{
#if !defined(TEMPLATE__ENABLE_UNSIGNED)
    return ((ARG > TYPE_K(0)) ? TYPE_K(1) : ((ARG < TYPE_K(0)) ? -TYPE_K(1) : TYPE_K(0)));
#else
    if (ARG > TYPE_K(0))
    {
        return (TYPE_K(1));
    }
    else
    {
        return (TYPE_K(0));
    };
#endif
}


/* ---- FCM(MAX) ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(MAX)( VAR_T(C) ARG0, VAR_T(C) ARG1 )
{
    return (ARG0 >= ARG1 ? ARG0 : ARG1);

}


/* ---- FCM(MIN) ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(MIN)( VAR_T(C) ARG0, VAR_T(C) ARG1 )
{
    return (ARG1 >= ARG0 ? ARG0 : ARG1);
}


/* ---- FCM(CLP) ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(CLP)( VAR_T(C) ARG0, VAR_T(C) MIN, VAR_T(C) MAX )
{
    TgPARAM_CHECK(MIN <= MAX);
    return (ARG0 <= MIN ? MIN : (ARG0 >= MAX ? MAX : ARG0));
}

            
/* ---- FCM(CLP_MIN) ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(CLP_MIN)( VAR_T(C) ARG0, VAR_T(C) ARG1 )
{
    return (ARG0 <= ARG1 ? ARG1 : ARG0);
}

            
/* ---- FCM(CLP_MAX) ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(CLP_MAX)( VAR_T(C) ARG0, VAR_T(C) ARG1 )
{
    return (ARG0 >= ARG1 ? ARG1 : ARG0);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
#if defined(TEMPLATE__ENABLE_INTEGER)
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCM(FLR_ALGN_PW2) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(FLR_ALGN_PW2)( VAR_T(C) ARG0, VAR_T(C) ARG1 )
{
    TgPARAM_CHECK(ARG1 > 0 && FCM(IS_PW2)( ARG1 ));

#if !defined(TEMPLATE__ENABLE_UNSIGNED)
    {
        VAR_T()                             fVal;
        
        fVal = FPM(ABS)( ARG0 ) & ~(ARG1 - 1 );
        return (ARG0 > 0 ? fVal : -fVal);
    }
#else
    return ((ARG0)& ~(ARG1 - 1u));
/*# defined(TEMPLATE__ENABLE_UNSIGNED) */
#endif
}


/* ---- FCM(CEL_ALGN_PW2) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(CEL_ALGN_PW2)( VAR_T(C) ARG0, VAR_T(C) ARG1 )
{
    TgPARAM_CHECK(ARG1 > 0 && FCM(IS_PW2)( ARG1 ));

#if !defined(TEMPLATE__ENABLE_UNSIGNED)
    {
        VAR_T()                             fVal;

        fVal = (FPM(ABS)( ARG0 ) + ARG1 - 1) & ~(ARG1 - 1 );
        return (ARG0 > 0 ? fVal : -fVal);
    }
#else
    return ((ARG0 + ARG1 - 1u) & ~(ARG1 - 1u));
/*# defined(TEMPLATE__ENABLE_UNSIGNED) */
#endif
}


/* ---- FCM(PRV_PW2) ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(PRV_PW2)( VAR_T(C) ARG0 )
{
#if !defined(TEMPLATE__ENABLE_UNSIGNED)
    VAR_T()                             fABS_A;
    VAR_T()                             fSCAN;
    VAR_T()                             fPW2;

    fABS_A = FPM(ABS)( ARG0 );
    fSCAN = (ARG0 == 0) ? 0 : ( VAR_T() ) ( (UVAR_T())1 << UFCN_F(tgPM_BSR)( (UVAR_T())fABS_A ) );
    fPW2 = FCM(IS_PW2)( fABS_A ) ? fABS_A : fSCAN;

    return (ARG0 > 0 ? fPW2 : -fPW2);
#else
    return ((FCM(IS_PW2)( ARG0 )) ? ARG0 : (VAR_T())((ARG0 == 0) ? 0 : (1 << FPM(BSR)( ARG0 ))) );
/*# defined(TEMPLATE__ENABLE_UNSIGNED) */
#endif
}


/* ---- FCM(NXT_PW2) ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(NXT_PW2)( VAR_T(C) ARG0 )
{
#if !defined(TEMPLATE__ENABLE_UNSIGNED)
    VAR_T()                             fABS_A;
    VAR_T()                             fSCAN;
    VAR_T()                             fPW2;

    fABS_A = FPM(ABS)( ARG0 );
    fSCAN = (VAR_T())((ARG0 == 0) ? 1 : (2 << UFCN_F(tgPM_BSR)( (UVAR_T())fABS_A )));
    fPW2 = (FCM(IS_PW2)( fABS_A )) ? fABS_A : fSCAN;

    return (ARG0 > 0 ? fPW2 : -fPW2);
#else
    return ((FCM(IS_PW2)( ARG0 )) ? ARG0 : (VAR_T())((ARG0 == 0) ? 1 : (2 << FPM(BSR)( ARG0 ))) );
/*# defined(TEMPLATE__ENABLE_UNSIGNED) */
#endif
}


/* ---- FCM(IS_PW2) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCM(IS_PW2)( VAR_T(C) ARG0 )
{
#if !defined(TEMPLATE__ENABLE_UNSIGNED)
    UVAR_T()                    fABS_A;

    fABS_A = (UVAR_T())FPM(ABS)( ARG0 );
    return (fABS_A && ((fABS_A & (fABS_A - 1)) == 0));
#else
    return (ARG0 && ((ARG0 & (ARG0 - 1u)) == 0u));
/*# defined(TEMPLATE__ENABLE_UNSIGNED) */
#endif
}


/* ---- FCM(RAND) ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(RAND)( TgVOID )
{
#if defined(TEMPLATE__OVERRIDE_INT_TYPE)
    TgCOMPILER_ASSERT(sizeof(VAR_T()) == 8,);
    #if !defined(TEMPLATE__ENABLE_UNSIGNED)
        return ((VAR_T())( (tgCM_RAND_U64() & UVAR_K(KTgMAX)) - (UVAR_K(KTgMAX) >> 1)) );
    #else
        return (tgCM_RAND_U64() & VAR_K(KTgMAX));
    /*# defined(TEMPLATE__ENABLE_UNSIGNED) */
    #endif
    
#elif TEMPLATE__TYPE_SIZE < 16
    #if !defined(TEMPLATE__ENABLE_UNSIGNED)
        return ( (VAR_T())(tgCM_RAND_U16() & KTgMAX_U08) - (VAR_T())(KTgMAX_U08 >> 1) );
    #else
        return (VAR_T())(tgCM_RAND_U16() & KTgMAX_U08);
    /*# defined(TEMPLATE__ENABLE_UNSIGNED) */
    #endif
    
#else

#if 64 == TEMPLATE__TYPE_SIZE
    #if !defined(TEMPLATE__ENABLE_UNSIGNED)
        UVAR_T()                            RAND;
    #else
        VAR_T()                             RAND;
    /*# defined(TEMPLATE__ENABLE_UNSIGNED) */
    #endif
#endif

    #if defined(TgCOMPILE__HARDWARE__RAND)
        if (0 == TgMACRO_CONCAT3(tgPM__HARDWARE__RAND_, U, GENERATE__TYPE_SIZE_TEXT)( &RAND ))
    /*# defined((TgCOMPILE__HARDWARE__RAND)) */
    #endif
        {
        #if 64 == TEMPLATE__TYPE_SIZE
            RAND = (UVAR_T())tgCM_RAND_MT_U32() | ((UVAR_T())tgCM_RAND_MT_U32() << 32);
        #else
            #if !defined(TEMPLATE__ENABLE_UNSIGNED)
                return ((VAR_T())( (tgCM_RAND_MT_U32() & UVAR_K(KTgMAX)) - (UVAR_K(KTgMAX) >> 1)) );
            #else
                return (tgCM_RAND_MT_U32() & VAR_K(KTgMAX));
            /*# defined(TEMPLATE__ENABLE_UNSIGNED) */
            #endif
        #endif
        }

#if 64 == TEMPLATE__TYPE_SIZE
    #if !defined(TEMPLATE__ENABLE_UNSIGNED)
        return ((VAR_T())( (RAND & UVAR_K(KTgMAX)) - (UVAR_K(KTgMAX) >> 1)) );
    #else
        return (VAR_T())(RAND & VAR_K(KTgMAX));
    /*# defined(TEMPLATE__ENABLE_UNSIGNED) */
    #endif
#endif

/*# TEMPLATE__TYPE_SIZE < 16 */
#endif
}


#if defined(TEMPLATE__ENABLE_UNSIGNED)

/* ---- FPM(BSF) ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgSINT_E08 FPM(BSF)( VAR_T() ARG )
{
    if (0 == ARG)
    {
        return (-1);
    }

#if defined(TgCOMPILE__HARDWARE__BSF)
    #if 64 == TEMPLATE__TYPE_SIZE || defined(TEMPLATE__OVERRIDE_INT_TYPE)
        return ((TgSINT_E08)tgPM__HARDWARE__BSF_U64(ARG));
    #elif 32 >= TEMPLATE__TYPE_SIZE
        return ((TgSINT_E08)tgPM__HARDWARE__BSF_U32(ARG));
    #endif
#else
    for (TgSINT_E08 TRAILING_ZERO = 0; ARG != 0; ++TRAILING_ZERO, ARG >>= 1)
    {
        if (ARG & 1)
        {
            return (TRAILING_ZERO);
        };
    }
    return -1;
/*# defined(TgCOMPILE__HARDWARE__BSR) */
#endif
}


/* ---- FPM(BSR) ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgSINT_E08 FPM(BSR)( VAR_T() ARG )
{
    if (0 == ARG)
    {
        return (-1);
    }

#if defined(TgCOMPILE__HARDWARE__BSR)
    #if 64 == TEMPLATE__TYPE_SIZE || defined(TEMPLATE__OVERRIDE_INT_TYPE)
        return (63 - (TgSINT_E08)tgPM__HARDWARE__BSR_U64(ARG));
    #elif 32 >= TEMPLATE__TYPE_SIZE
        return (31 - (TgSINT_E08)tgPM__HARDWARE__BSR_U32(ARG));
    #endif
#else
    {
        UVAR_T()                            MASK;

        #if defined(TEMPLATE__ENABLE_UNSIGNED)
        MASK = (UVAR_T())(~(VAR_K(KTgMAX) >> 1));
        #else
        MASK = (UVAR_T())(~(UVAR_K(KTgMAX) >> 1));
        #endif
        for (TgRSIZE uiIndex = 0; ARG != 0; ++uiIndex, ARG <<= 1)
        {
            if (ARG & MASK)
            {
                return ((TgSINT_E08)(sizeof(VAR_T())*8 - 1 - uiIndex));
            };
        }
        return -1;
    }
/*# defined(TgCOMPILE__HARDWARE__BSR) */
#endif
}


/*# defined(TEMPLATE__ENABLE_UNSIGNED) */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*# defined(TEMPLATE__ENABLE_INTEGER) */
#else
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */


/* ---- FCM(NR0) ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCM(NR0)( VAR_T(C) ARG0 )
{
    return (FPM(ABS)( ARG0 ) <= VAR_K(KTgROOT_EPS));
}


/* ---- FCM(NR1) ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCM(NR1)( VAR_T(C) ARG0 )
{
    return (FPM(ABS)( FPM(ABS)( ARG0 ) - TYPE_K(1) ) <= VAR_K(KTgROOT_EPS));
}


/* ---- FCM(CLP_FRC) ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(CLP_FRC)( VAR_T(C) ARG0, VAR_T(C) ARG1 )
{
    return (FPM(FSEL)( ARG0, FPM(FSEL)(ARG0 - ARG1, TYPE_K(1), ARG0 / ARG1), TYPE_K(0)) );
}


/* ---- FCM(LRP) ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCM(LRP)( VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 )
{
    return (ARG0 + ARG2*(ARG1 - ARG0));
}


/* ---- FCM(EQ) ------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCM(EQ)( VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 )
{
    VAR_T(C)                        ARG0_ABS = FPM(ABS)( ARG0 );
    VAR_T(C)                        ARG1_ABS = FPM(ABS)( ARG1 );
    VAR_T(C)                        TOL = FCM(MAX)( ARG2, VAR_K(KTgEPS) );

    if (ARG1_ABS > VAR_K(KTgEPS))
    {
        return (FPM(ABS)( (ARG0_ABS / ARG1_ABS) - TYPE_K(1)) < TOL);
    }
    else if (ARG0_ABS > VAR_K(KTgEPS))
    {
        return (FPM(ABS)( (ARG1_ABS / ARG0_ABS) - TYPE_K(1)) < TOL);
    }
    else
    {
        return (true);
    };
}


/* ---- FPM(SINCOS) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FPM(SINCOS)( VAR_T(PCU) OUT0, VAR_T(PCU) OUT1, VAR_T(C) ARG0 )
{
    TgERROR(nullptr != OUT0 && nullptr != OUT1);
    *OUT0 = FPM(SIN)( ARG0 );
    *OUT1 = FPM(COS)( ARG0 );
}


/* ---- FPM(FSEL) ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FPM(FSEL)( VAR_T(C) ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2 )
{
    return ((ARG0 >= TYPE_K(0)) ? ARG1 : ARG2);
}

/*# defined(TEMPLATE__ENABLE_INTEGER) */
#endif


/* =============================================================================================================================================================================== */

/* MACROS defined in this file */
#undef FPM
#undef FCM

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

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

    #define TGS_COMMON_BASE_API_MATH_INL
    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COMMON_BASE_API_MATH_INL) */
#endif
