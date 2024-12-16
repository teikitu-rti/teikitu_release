/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Scalar] [F].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD)
    #define ENABLE_RELOAD_GUARD
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__
    #undef TEMPLATE__TYPE_SIZE

    #undef ENABLE_RELOAD_GUARD
    #define TEMPLATE__TYPE_SIZE 64
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Van Wijngaarden-Dekker-Brent Root Finder --------------------------------------------------------------------------------------------------------------------------------- */
/** Guaranteed to find a root to the equation given that the two initial parameters straddle a solution point (ie. one positive and one negative value) - IVT guarantees at least
    one theoretical solution.  Iterative technique will refine solution until its within the passed in tolerance value.  Implementation from Numerical Recipes.                    */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_F(tgMH_BrentZ)(VAR_T(PCU) pfT0, TgVOID_PCU pParam, VAR_T()( *pfnFunc )(TgVOID_PCU, VAR_T(C)), VAR_T() fTA, VAR_T() fTC)
{
    VAR_T()                             fValA = (*pfnFunc)(pParam, fTA);
    VAR_T()                             fValC = (*pfnFunc)(pParam, fTC);
    VAR_T()                             fTB = fTC;
    VAR_T()                             fValB, p, q, d, e;
    TgSINT_E32                          iCount;

    if (fValA*fValC > TYPE_K(0))
    {
        /* Root must be bracketed for IVT to be valid. */
        return (false);
    };

    fValB = fValC;
    fValC = fValA;
    fTC = fTA;
    e = d = fTB - fTA;

    for (iCount = 1; iCount <= 100; ++iCount)
    {
        VAR_T()                             fTol1, fTM;

        if (FCN_F(tgPM_ABS)(fValC) < FCN_F(tgPM_ABS)(fValB))
        {
            fTA = fTB;
            fTB = fTC;
            fTC = fTA;

            fValA = fValB;
            fValB = fValC;
            fValC = fValA;
        }

        /* Convergence check. */

        fTol1 = TYPE_K(2,0)*VAR_K(KTgROOT_EPS)*FCN_F(tgPM_ABS)(fTB) + TYPE_K(0,5)*VAR_K(KTgROOT_EPS);
        fTM = TYPE_K(0,5)*(fTC - fTB);

        if (FCN_F(tgPM_ABS)(fTM) <= fTol1 || fValB == TYPE_K(0))
        {
            *pfT0 = fTB;
            return (true);
        };

        if (FCN_F(tgPM_ABS)(e) >= fTol1 && FCN_F(tgPM_ABS)(fValA) > FCN_F(tgPM_ABS)(fValB))
        {
            /* Attempt inverse quadratic interpolation. */

            VAR_T(C)        fBA = fValB / fValA, fBC = fValB / fValC, fAC = fValA / fValC;

            p = FCN_F(tgPM_FSEL)(-FCN_F(tgPM_ABS)(fTA - fTC), TYPE_K(2,0)*fTM*fBA, fBA*(TYPE_K(2,0)*fTM*fAC*(fAC - fBC) - (fTB - fTA)*(fBC - TYPE_K(1))) );
            q = FCN_F(tgPM_FSEL)(-FCN_F(tgPM_ABS)(fTA - fTC), TYPE_K(1) - fBA, (fAC - TYPE_K(1))*(fBC - TYPE_K(1))*(fBA - TYPE_K(1)));

            /* Check whether in bounds. */

            q = FCN_F(tgPM_FSEL)(p, -q, q);
            p = FCN_F(tgPM_ABS)(p);

            {
                VAR_T(C)        fMin1 = TYPE_K(3,0)*fTM*q - FCN_F(tgPM_ABS)(fTol1*q);
                VAR_T(C)        fMin2 = FCN_F(tgPM_ABS)(e*q);
                VAR_T(C)        fInt = FCN_F(tgPM_FSEL)(fMin2 - fMin1, fMin1, fMin2) - TYPE_K(2,0)*p;

                e = FCN_F(tgPM_FSEL)(fInt, d, fTM);
                d = FCN_F(tgPM_FSEL)(fInt, p / q, fTM);
            }
/*          FCN_F(tgPM_FSEL)( FCN_F(tgPM_FSEL)( fMin2 - fMin1, fMin1, fMin2 ) - VAR_T()(2.0)*p, Accept interpolation, Use bisection ); */
        }
        else
        {
            /* Bounds decreasing too slowly, use bisection. */

            d = fTM;
            e = fTM;
        }

        /* Move last best guess to fTA. */

        fTA = fTB;
        fValA = fValB;

        /* Evaluate new trial root. */

        fTB += FCN_F(tgPM_FSEL)(FCN_F(tgPM_ABS)(d) - fTol1, d, FCN_F(tgPM_FSEL)(fTM, fTol1, -fTol1));
        fValB = (*pfnFunc)(pParam, fTB);

        if (fValB*fValC > TYPE_K(0))
        {
            /* Rename fTA, fTB, fTC and adjust bounding interval */

            fTC = fTA;
            fValC = fValA;
            e = d = fTB - fTA;
        }
    }

    return (false);
}


/* ---- Van Wijngaarden-Dekker-Brent Root Finder --------------------------------------------------------------------------------------------------------------------------------- */
/** Given a function fn, and given a bracketing triplet of abscissas t1, t2, t3 (such that t2 is between t1 and t3, and f(t1) is less than both f(t1) and f(t3)), this routine
    isolates the minimum to a fractional precision of about tol using Brent's method.  See Numerical Recipes in C, section 10.2                                                    */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCLANG_WARN_DISABLE_PUSH(float-equal)
TgBOOL FCN_F(tgMH_BrentD)(
    VAR_T(PCU) pfT0, VAR_T(PCU) ptyV0, TgVOID_PCU pParam,
    VAR_T()( *pfnFunc0 )(TgVOID_PCU, VAR_T(C)),
    VAR_T()( *pfnFunc1 )(TgVOID_PCU, VAR_T(C)),
    VAR_T() fT1, VAR_T() fT2, VAR_T() fT3
)
{
    VAR_T()                             fTM, fD = TYPE_K(0), fE = TYPE_K(0);
    VAR_T()                             fU, fFU, fDU;
    VAR_T()                             fV, fFV, fDV;
    VAR_T()                             fW, fFW, fDW;
    VAR_T()                             fX, fFX, fDX;
    VAR_T()                             fA = FCN_F(tgPM_FSEL)(fT3 - fT1, fT1, fT3);
    VAR_T()                             fB = FCN_F(tgPM_FSEL)(fT1 - fT3, fT1, fT3);
    VAR_T()                             fPrevE;
    TgSINT_E32                          niCount;

    //fD = TYPE_K(0,0);
    //fE = TYPE_K(0,0);
    fPrevE = TYPE_K(0,0);
    fX = fW = fV = fT2;
    fFX = fFW = fFV = (*pfnFunc0) (pParam, fX);
    fDX = fDW = fDV = (*pfnFunc1) (pParam, fX);

    for (niCount = 1; niCount <= 100; ++niCount)
    {
        VAR_T(C)        fTol1 = VAR_K(KTgROOT_EPS) * FCN_F(tgPM_ABS)(fX) + VAR_K(KTgEPS);
        VAR_T(C)        fTol2 = TYPE_K(2,0) * fTol1;

        TgDIAG( fTol1 > TYPE_K(0) );

        fTM = TYPE_K(0,5)*(fA + fB);

        if (FCN_F(tgPM_ABS)(fX - fTM) <= (fTol2 - TYPE_K(0,5)*(fB - fA)))
        {
            *pfT0 = fX;
            *ptyV0 = fFX;
            return (true);
        };

//#        fPrevD = fD;

        fD = TYPE_K(0,5) * (fE = FCN_F(tgPM_FSEL)(fDX, fA - fX, fB - fX));

        if (FCN_F(tgPM_ABS)(fPrevE) - fTol1 > TYPE_K(0))
        {
            VAR_T(C)        fK0 = fDW - fDX;
            VAR_T(C)        fK1 = fK0 <= VAR_K(KTgEPS) ? TYPE_K(0) : TYPE_K(1) / fK0;
            VAR_T(C)        fD1 = FCN_F(tgPM_FSEL)( -FCN_F(tgPM_ABS)(fK0), (fX - fW)*fDX *fK1, TYPE_K(2,0)*(fB - fA) );
            VAR_T(C)        fK2 = fDV - fDX;
            VAR_T(C)        fK3 = fK2 <= VAR_K(KTgEPS) ? TYPE_K(0,0) : TYPE_K(1) / fK0;
            VAR_T(C)        fD2 = FCN_F(tgPM_FSEL)( -FCN_F(tgPM_ABS)(fK2), (fX - fV)*fDX * fK3, fD1 );
            VAR_T(C)        fOK1 = FCN_F(tgPM_FSEL)( (fA - fX - fD1)*(fX + fD1 - fB), FCN_F(tgPM_FSEL)(-fDX*fD1, TYPE_K(1), -TYPE_K(1)), -TYPE_K(1) );
            VAR_T(C)        fOK2 = FCN_F(tgPM_FSEL)( (fA - fX - fD2)*(fX + fD2 - fB), FCN_F(tgPM_FSEL)(-fDX*fD2, TYPE_K(1), -TYPE_K(1)), -TYPE_K(1) );

            VAR_T(C) fTMP = FCN_F(tgPM_FSEL)( fOK1, FCN_F(tgPM_FSEL)(fOK2, FCN_F(tgPM_FSEL)(FCN_F(tgPM_ABS)(fD2) - FCN_F(tgPM_ABS)(fD1), fD1, fD2), fD1), fD2 );

            if ((fOK1 + fOK2 >= TYPE_K(0)) && (FCN_F(tgPM_ABS)(TYPE_K(0,5) * fPrevE) - FCN_F(tgPM_ABS)(fTMP) >= TYPE_K(0)))
            {
                VAR_T(C)        fNewD = FCN_F(tgPM_COPY_SIGN)(fTol1, fTM - fX);

                fPrevE = fE;
                //fE = fPrevD;
                fD = FCN_F(tgPM_FSEL)(fA - fX - fTMP + fTol2, fNewD, FCN_F(tgPM_FSEL)(fA - fX - fTMP + fTol2, fNewD, fTMP));
            }
        }

        fU = FCN_F(tgPM_FSEL)(FCN_F(tgPM_ABS)(fD) - fTol1, fX + fD, fX + FCN_F(tgPM_COPY_SIGN)(fTol1, fD));
        fFU = (*pfnFunc0) (pParam, fU);

        if (fFU <= fFX)
        {
            fDU = (*pfnFunc1) (pParam, fU);

            fA = FCN_F(tgPM_FSEL)(fU - fX, fX, fA);
            fB = FCN_F(tgPM_FSEL)(fU - fX, fB, fX);

            fV = fW;
            fFV = fFW;
            fDV = fDW;

            fW = fX;
            fFW = fFX;
            fDW = fDX;

            fX = fU;
            fFX = fFU;
            fDX = fDU;
        }
        else
        {
            if (FCN_F(tgPM_ABS)(fD) < fTol1)
            {
                *pfT0 = fX;
                *ptyV0 = fFX;
                return (true);
            }

            fA = FCN_F(tgPM_FSEL)(fX - fU, fU, fA);
            fB = FCN_F(tgPM_FSEL)(fX - fU, fB, fU);

            fDU = (*pfnFunc1) (pParam, fU);

            if (fFU <= fFW || fW == fX)
            {
                fV = fW;
                fFV = fFW;
                fDV = fDW;

                fW = fU;
                fFW = fFU;
                fDW = fDU;
            }
            else if (fFU < fFV || fV == fX || fV == fW)
            {
                fV = fU;
                fFV = fFU;
                fDV = fDU;
            }
        }
    }

    return (false);
}
TgCLANG_WARN_DISABLE_POP(float-equal)


/* ---- Degree 1 Algebraic Solver ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_F(tgMH_Calc_Root_1)(VAR_T(PCU) atyRoot, TgSINT_E32_PCU piCount, VAR_T() fC0, VAR_T() fC1)
{
    if (FCN_F(tgPM_ABS)(fC1) >= VAR_K(KTgROOT_EPS))
    {
        atyRoot[0] = -(fC0 / fC1);
        *piCount = 1;
        return (true);
    }
    else
    {
        *piCount = 0;
        return (false);
    };
}


/* ---- Degree 2 Algebraic Solver ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_F(tgMH_Calc_Root_2)(VAR_T(PCU) atyRoot, TgSINT_E32_PCU piCount, VAR_T() fC0, VAR_T() fC1, VAR_T() fC2)
{
    if (FCN_F(tgPM_ABS)(fC2) <= VAR_K(KTgROOT_EPS))
    {
        return (FCN_F(tgMH_Calc_Root_1)(atyRoot, piCount, fC0, fC1));
    }
    else
    {
        VAR_T()                             fDSC = fC1*fC1 - TYPE_K(4,0)*fC0*fC2;
        VAR_T()                             fTMP00;

        if (FCN_F(tgPM_ABS)(fDSC) <= VAR_K(KTgROOT_EPS))
        {
            fDSC = TYPE_K(0);
        };

        if (fDSC < TYPE_K(0))
        {
            *piCount = 0;
            return (false);
        };

        fTMP00 = TYPE_K(0,5) / fC2;

        if (fDSC > TYPE_K(0))
        {
            fDSC = FCN_F(tgPM_SQRT)(fDSC);

            atyRoot[0] = fTMP00*(-fC1 - fDSC);
            atyRoot[1] = fTMP00*(-fC1 + fDSC);

            *piCount = 2;
        }
        else
        {
            atyRoot[0] = -fTMP00*fC1;
            atyRoot[1] = -fTMP00*fC1;

            *piCount = 1;
        }

        return (true);
    };
}


/* ---- Degree 3 Algebraic Solver ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_F(tgMH_Calc_Root_3)(VAR_T(PCU) atyRoot, TgSINT_E32_PCU piCount, VAR_T() fC0, VAR_T() fC1, VAR_T() fC2, VAR_T() fC3)
{
    if (FCN_F(tgPM_ABS)(fC3) <= VAR_K(KTgEPS))
    {
        return (FCN_F(tgMH_Calc_Root_2)(atyRoot, piCount, fC0, fC1, fC2));
    };

    /* Make polynomial monic, x^3+c2*x^2+c1*x+c0 */

    if (fC3 != TYPE_K(1))
    {
        VAR_T(C)        fInvC3 = TYPE_K(1) / fC3;

        fC0 *= fInvC3;
        fC1 *= fInvC3;
        fC2 *= fInvC3;
    };

    /* Convert to y^3+a*y+b = 0 by x = y-c2/3 */

    {
        VAR_T(C)        fOffset = fC2 / TYPE_K(3,0);
        VAR_T(C)        fA = fC1 - fC2*fOffset;
        VAR_T(C)        fTMP00 = fC2*fC2;
        VAR_T(C)        fB = fC0 + fC2*(fTMP00 + fTMP00 - TYPE_K(9,0)*fC1)*(TYPE_K(1) / TYPE_K(27,0));
        VAR_T(C)        fHalfB = TYPE_K(0,5)*fB;

        VAR_T()                             fDSC = fHalfB*fHalfB + fA*fA*fA*(TYPE_K(1) / TYPE_K(27,0));

        if (FCN_F(tgPM_ABS)(fDSC) <= VAR_K(KTgROOT_EPS))
        {
            fDSC = TYPE_K(0);
        };

        if (fDSC > TYPE_K(0))
        {
            VAR_T(C)        fDSC_SQRT = FCN_F(tgPM_SQRT)(fDSC);
            VAR_T(C)        fTMP01 = -fHalfB + fDSC_SQRT;
            VAR_T(C)        fTMP02 = -fHalfB - fDSC_SQRT;

            if (fTMP01 >= TYPE_K(0))
            {
                atyRoot[0] = FCN_F(tgPM_POW)(fTMP01, TYPE_K(1) / TYPE_K(3,0));
            }
            else
            {
                atyRoot[0] = -FCN_F(tgPM_POW)(-fTMP01, TYPE_K(1) / TYPE_K(3,0));
            }

            if (fTMP02 >= TYPE_K(0))
            {
                atyRoot[0] += FCN_F(tgPM_POW)(fTMP02, TYPE_K(1) / TYPE_K(3,0));
            }
            else
            {
                atyRoot[0] -= FCN_F(tgPM_POW)(-fTMP02, TYPE_K(1) / TYPE_K(3,0));
            }

            atyRoot[0] -= fOffset;

            *piCount = 1;
        }
        else if (fDSC < TYPE_K(0))
        {

            VAR_T(C)        fDist = FCN_F(tgPM_SQRT)(-fA / TYPE_K(3,0));
            VAR_T(C)        fAngle = FCN_F(tgPM_ATAN2)(FCN_F(tgPM_SQRT)(-fDSC), -fHalfB) / TYPE_K(3,0);
            VAR_T(C)        fCos = FCN_F(tgPM_COS)(fAngle);
            VAR_T(C)        fSin = FCN_F(tgPM_SIN)(fAngle);
            VAR_T(C)        fTMP01 = fDist*fCos;

            atyRoot[0] = fTMP01 + fTMP01 - fOffset;
            atyRoot[1] = -fDist*(fCos + VAR_K(KTgSQRT3)*fSin) - fOffset;
            atyRoot[2] = -fDist*(fCos - VAR_K(KTgSQRT3)*fSin) - fOffset;

            *piCount = 3;
        }
        else
        {
            VAR_T()                             fTMP01;

            if (fHalfB >= TYPE_K(0))
            {
                fTMP01 = -FCN_F(tgPM_POW)(fHalfB, TYPE_K(1) / TYPE_K(3));
            }
            else
            {
                fTMP01 = FCN_F(tgPM_POW)(-fHalfB, TYPE_K(1) / TYPE_K(3));
            }

            atyRoot[0] = fTMP01 + fTMP01 - fOffset;
            atyRoot[1] = -fTMP01 - fOffset;
            atyRoot[2] = atyRoot[1];

            *piCount = 3;
        }
    }

    return (true);
}


/* ---- Degree 4 Algebraic Solver ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_F(tgMH_Calc_Root_4)(VAR_T(PCU) atyRoot, TgSINT_E32_PCU piCount, VAR_T() fC0, VAR_T() fC1, VAR_T() fC2, VAR_T() fC3, VAR_T() fC4)
{
    VAR_T(C)        fInvC4 = TYPE_K(1) / fC4;

    if (FCN_F(tgPM_ABS)(fC4) <= VAR_K(KTgROOT_EPS))
    {
        return (FCN_F(tgMH_Calc_Root_3)(atyRoot, piCount, fC0, fC1, fC2, fC3));
    }

    /* Make polynomial monic, x^4+c3*x^3+c2*x^2+c1*x+c0 */

    if (fInvC4 != TYPE_K(1))
    {
        fC0 *= fInvC4;
        fC1 *= fInvC4;
        fC2 *= fInvC4;
        fC3 *= fInvC4;
    };

    {
        /* Reduction to Resolvent Cubic Polynomial y^3+r2*y^2+r1*y+r0 = 0 */

        VAR_T()                             fR0 = -fC3*fC3*fC0 + TYPE_K(4,0)*fC0*fC2 - fC1*fC1;
        VAR_T()                             fR1 = fC3*fC1 - TYPE_K(4,0)*fC0;
        VAR_T()                             fR2 = -fC2;
        VAR_T()                             fDSC;

        FCN_F(tgMH_Calc_Root_3)(atyRoot, piCount, fR0, fR1, fR2, TYPE_K(1));

        fDSC = TYPE_K(0,25)*fC3*fC3 - fC2 + atyRoot[0];

        *piCount = 0;

        if (FCN_F(tgPM_ABS)(fDSC) <= VAR_K(KTgROOT_EPS))
        {
            fDSC = TYPE_K(0);
        };

        if (fDSC > TYPE_K(0))
        {
            VAR_T(C)        fTMP00 = FCN_F(tgPM_SQRT)(fDSC);
            VAR_T(C)        fTMP01 = TYPE_K(0,75)*fC3*fC3 - fTMP00*fTMP00 - fC2 - fC2;
            VAR_T(C)        fTMP02 = TYPE_K(4,0)*(fC3*fC2 - fC1 - fC1);
            VAR_T(C)        fTMP03 = TYPE_K(0,25)*(fTMP02 - fC3*fC3*fC3) / (fTMP00);

            VAR_T()                             fTMP04 = fTMP01 + fTMP03;
            VAR_T()                             fTMP05 = fTMP01 - fTMP03;

            if (FCN_F(tgPM_ABS)(fTMP04) <= VAR_K(KTgROOT_EPS))
            {
                fTMP04 = TYPE_K(0);
            }

            if (FCN_F(tgPM_ABS)(fTMP05) <= VAR_K(KTgROOT_EPS))
            {
                fTMP05 = TYPE_K(0);
            }

            if (fTMP04 >= TYPE_K(0))
            {
                VAR_T(C)        fTMP06 = FCN_F(tgPM_SQRT)(fTMP04);

                atyRoot[0] = -TYPE_K(0,25)*fC3 + TYPE_K(0,5)*(fTMP00 + fTMP06);
                atyRoot[1] = -TYPE_K(0,25)*fC3 + TYPE_K(0,5)*(fTMP00 - fTMP06);
                *piCount += 2;
            }

            if (fTMP05 >= TYPE_K(0))
            {
                VAR_T(C)        fTMP06 = FCN_F(tgPM_SQRT)(fTMP05);

                atyRoot[(*piCount)++] = -TYPE_K(0,25)*fC3 + TYPE_K(0,5)*(fTMP06 - fTMP00);
                atyRoot[(*piCount)++] = -TYPE_K(0,25)*fC3 - TYPE_K(0,5)*(fTMP06 + fTMP00);
            }

        }
        else if (fDSC < TYPE_K(0))
        {
            *piCount = 0;
        }
        else
        {
            VAR_T()                             fTMP01 = atyRoot[0] * atyRoot[0] - TYPE_K(4,0)*fC0;

            if (fTMP01 >= -VAR_K(KTgROOT_EPS))
            {
                VAR_T()                             fTMP00 = TYPE_K(0,75)*fC3*fC3 - fC2 - fC2;

                fTMP01 = fTMP01 < TYPE_K(0) ? TYPE_K(0) : TYPE_K(2)*FCN_F(tgPM_SQRT)(fTMP01);

                if (fTMP00 + fTMP01 >= VAR_K(KTgROOT_EPS))
                {
                    VAR_T(C)        fTMP02 = FCN_F(tgPM_SQRT)(fTMP00 + fTMP01);

                    atyRoot[0] = -TYPE_K(0,25)*fC3 + TYPE_K(0,5)*fTMP02;
                    atyRoot[1] = -TYPE_K(0,25)*fC3 - TYPE_K(0,5)*fTMP02;
                    *piCount += 2;
                }

                if (fTMP00 - fTMP01 >= VAR_K(KTgROOT_EPS))
                {
                    VAR_T(C)        fTMP02 = FCN_F(tgPM_SQRT)(fTMP00 - fTMP01);

                    atyRoot[(*piCount)++] = -TYPE_K(0,25)*fC3 + TYPE_K(0,5)*fTMP02;
                    atyRoot[(*piCount)++] = -TYPE_K(0,25)*fC3 - TYPE_K(0,5)*fTMP02;
                }
            }
        }
    }

    return *piCount > 0;
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
