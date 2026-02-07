/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Vector] [S] [FXX_04].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_VECTOR_S_FXX_04_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(tgMH_Init_ELEM_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_Init_ELEM_S)( VAR_T(C) fX, VAR_T(C) fy, VAR_T(C) fZ, VAR_T(C) fW )
{
    VEC_S_T(1)                          vResult;

    vResult.m_aData[0] = fX;
    vResult.m_aData[1] = fy;
    vResult.m_aData[2] = fZ;
    vResult.m_aData[3] = fW;

    return (vResult);
}


/* ---- FCN_V(tgMH_Init_Point_ELEM_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_Init_Point_ELEM_S)( VAR_T(C) fX, VAR_T(C) fy, VAR_T(C) fZ )
{
    VEC_S_T(1)                          vResult;

    vResult.m_aData[0] = fX;
    vResult.m_aData[1] = fy;
    vResult.m_aData[2] = fZ;
    vResult.m_aData[3] = TYPE_K(1);

    return (vResult);
}


/* ---- FCN_V(tgMH_Init_Vector_ELEM_S) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_Init_Vector_ELEM_S)( VAR_T(C) fX, VAR_T(C) fy, VAR_T(C) fZ )
{
    VEC_S_T(1)                          vResult;

    vResult.m_aData[0] = fX;
    vResult.m_aData[1] = fy;
    vResult.m_aData[2] = fZ;
    vResult.m_aData[3] = TYPE_K(0);

    return (vResult);
}


/* ---- FCN_V(tgMH_SETP_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_Init_Point_S)( VEC_S_T(1,C) vARG_0 )
{
    VEC_S_T(1)                          vResult;

    vResult.m_aData[0] = vARG_0.m_aData[0];
    vResult.m_aData[1] = vARG_0.m_aData[1];
    vResult.m_aData[2] = vARG_0.m_aData[2];
    vResult.m_aData[3] = TYPE_K(1);

    return (vResult);
}


/* ---- FCN_V(tgMH_SETV_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_Init_Vector_S)( VEC_S_T(1,C) vARG_0 )
{
    VEC_S_T(1)                          vResult;

    vResult.m_aData[0] = vARG_0.m_aData[0];
    vResult.m_aData[1] = vARG_0.m_aData[1];
    vResult.m_aData[2] = vARG_0.m_aData[2];
    vResult.m_aData[3] = TYPE_K(0);

    return (vResult);
}


/* ---- FCN_V(tgMH_Init_Ortho_S) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_Init_Ortho_S)( VEC_S_T(1,C) vARG_0 )
{
    VAR_T(C)        fX = FCN_F(tgPM_ABS)( vARG_0.m_aData[0] );
    VAR_T(C)        fY = FCN_F(tgPM_ABS)( vARG_0.m_aData[1] );
    VAR_T(C)        fZ = FCN_F(tgPM_ABS)( vARG_0.m_aData[2] );

    if (fX < fY && fX < fZ)
    {
        return (FCN_V(tgMH_Init_Vector_ELEM_S)( TYPE_K(0), vARG_0.m_aData[2], -vARG_0.m_aData[1] ));
    }
    else if (fY < fZ)
    {
        return (FCN_V(tgMH_Init_Vector_ELEM_S)( vARG_0.m_aData[2], TYPE_K(0), -vARG_0.m_aData[0] ));
    }
    else
    {
        return (FCN_V(tgMH_Init_Vector_ELEM_S)( vARG_0.m_aData[1], -vARG_0.m_aData[0], TYPE_K(0) ));
    };
}


/* ---- FCN_V(tgMH_Init_Basis_From_Vector_S) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_V(tgMH_Init_Basis_From_Vector_S)( VEC_S_T(1,PCU) pvB0, VEC_S_T(1,PCU) pvB1, VEC_S_T(1,C) vARG_0 )
{
    VAR_T(C)        fXX_ZZ = vARG_0.m_aData[0] * vARG_0.m_aData[0] + vARG_0.m_aData[2] * vARG_0.m_aData[2];
    VAR_T(C)        fXZ = FCN_F(tgPM_SQRT)( fXX_ZZ );

    TgERROR(FCN_V(tgMH_Is_Valid_Vector_S)( vARG_0 ) && FCN_F(tgCM_NR1)( FCN_V(tgMH_LSQ_S)( vARG_0 ) ));

    if (FCN_F(tgCM_NR0)( fXZ ))
    {
        *pvB0 = VEC_K(KTgUNIT_X_S);
        *pvB1 = VEC_K(KTgUNIT_Z_S);
    }
    else
    {
        VAR_T(C)        fXY = vARG_0.m_aData[0] * vARG_0.m_aData[1];
        VAR_T(C)        fYZ = vARG_0.m_aData[1] * vARG_0.m_aData[2];
        VAR_T(C)        fInvXZ = TYPE_K(1) / fXZ;

        *pvB0 = FCN_V(tgMH_Init_Vector_ELEM_S)( -vARG_0.m_aData[2] * fInvXZ, TYPE_K(0), vARG_0.m_aData[0] * fInvXZ );
        *pvB1 = FCN_V(tgMH_Init_Vector_ELEM_S)( -fXY, fXX_ZZ, -fYZ );
    };
}


/* ---- FCN_V(tgMH_Is_Valid_Point_S) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_Is_Valid_Point_S)( VEC_S_T(1,C) vARG_0 )
{
    return (!FCN_F(tgPM_NAN)(vARG_0.x) && !FCN_F(tgPM_NAN)( vARG_0.y) && !FCN_F(tgPM_NAN)(vARG_0.z) && (TYPE_K(1) == vARG_0.w));
}


/* ---- FCN_V(tgMH_Is_Valid_Vector_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_Is_Valid_Vector_S)( VEC_S_T(1,C) vARG_0 )
{
    return (!FCN_F(tgPM_NAN)(vARG_0.x) && !FCN_F(tgPM_NAN)( vARG_0.y) && !FCN_F(tgPM_NAN)(vARG_0.z) && (TYPE_K(0) == vARG_0.w));
}


/* ---- FCN_V(tgMH_Is_Valid_Unit_Vector_S) --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_Is_Valid_Unit_Vector_S)( VEC_S_T(1,C) vARG_0 )
{
    return (!FCN_F(tgPM_NAN)(vARG_0.x) && !FCN_F(tgPM_NAN)( vARG_0.y) && !FCN_F(tgPM_NAN)(vARG_0.z) && (TYPE_K(0) == vARG_0.w) && FCN_F(tgCM_NR1)( FCN_V(tgMH_LSQ_S)( vARG_0 )));
}


/* ---- FCN_V(tgMH_DOT3_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCN_V(tgMH_DOT3_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    return (vARG_0.m_aData[0] * vARG_1.m_aData[0] + vARG_0.m_aData[1] * vARG_1.m_aData[1] + vARG_0.m_aData[2] * vARG_1.m_aData[2]);
}


/* ---- FCN_V(tgMH_CX_S) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_CX_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    return (FCN_V(tgMH_Init_Vector_ELEM_S)(
        vARG_0.m_aData[1] * vARG_1.m_aData[2] - vARG_0.m_aData[2] * vARG_1.m_aData[1],
        vARG_0.m_aData[2] * vARG_1.m_aData[0] - vARG_0.m_aData[0] * vARG_1.m_aData[2],
        vARG_0.m_aData[0] * vARG_1.m_aData[1] - vARG_0.m_aData[1] * vARG_1.m_aData[0]
    ));
}


/* ---- FCN_V(tgMH_UCX_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_UCX_S)( VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    VEC_S_T(1)                          vRet;
    VAR_T()                             fLength;

    vRet = FCN_V(tgMH_CX_S)( vARG_0, vARG_1 );
    return (FCN_V(tgMH_NORM_LEN_S)( &fLength, vRet ));
}


/* ---- FCN_V(tgMH_UCX_LEN_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_UCX_LEN_S)( VAR_T(PCU) ptyLength, VEC_S_T(1,C) vARG_0, VEC_S_T(1,C) vARG_1 )
{
    VEC_S_T(1)                          vRet;

    vRet = FCN_V(tgMH_CX_S)( vARG_0, vARG_1 );
    return (FCN_V(tgMH_NORM_LEN_S)( ptyLength, vRet ));
}


/* ---- FCN_V(tgMH_NORM3_LEN_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_NORM3_LEN_S)( VAR_T(P)  __restrict const pfLength, VEC_S_T(1,C) vARG_0 )
{
    VAR_T(C)        fa0 = FCN_F(tgPM_ABS)( vARG_0.m_aData[0] );
    VAR_T(C)        fa1 = FCN_F(tgPM_ABS)( vARG_0.m_aData[1] );
    VAR_T(C)        fa2 = FCN_F(tgPM_ABS)( vARG_0.m_aData[2] );
    VAR_T(C)        fM0 = FCN_F(tgCM_MAX)( fa0, fa1 );
    VAR_T(C)        fM1 = FCN_F(tgCM_MAX)( fa1, fa2 );
    VAR_T(C)        fMX = FCN_F(tgCM_MAX)( fM0, fM1 );
    VAR_T(C)        f0 = vARG_0.m_aData[0] / fMX;
    VAR_T(C)        f1 = vARG_0.m_aData[1] / fMX;
    VAR_T(C)        f2 = vARG_0.m_aData[2] / fMX;
    VAR_T(C)        fLength = FCN_F(tgPM_SQRT)( f0*f0 + f1*f1 + f2*f2 );
    VAR_T(C)        fInvLength = fLength > VAR_K(KTgEPS) ? TYPE_K(1) / fLength : TYPE_K(0);

    *pfLength = fLength*fMX;

    return (FCN_V(tgMH_Init_ELEM_S)( f0*fInvLength, f1*fInvLength, f2*fInvLength, vARG_0.m_aData[3] ) );
}


/* ---- FCN_V(tgMH_NORM3_S)------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_NORM3_S)( VEC_S_T(1,C) vARG_0 )
{
    VAR_T()                             fLength;

    return (FCN_V(tgMH_NORM3_LEN_S)( &fLength, vARG_0) );
}


/* ---- FCN_V(tgMH_PRX3_CMP_EQ_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_PRX3_CMP_EQ_S)( VEC_S_T(1,C) pV0, VEC_S_T(1,C) pV1 )
{
    VEC_S_T(1)                          vDiff;

    vDiff = FCN_V(tgMH_SUB_S)( pV0, pV1 );
    if (!FCN_F(tgCM_NR0)( vDiff.x ))
        return (false);
    if (!FCN_F(tgCM_NR0)( vDiff.y ))
        return (false);
    if (!FCN_F(tgCM_NR0)( vDiff.z ))
        return (false);

    return (true);
}


/* ---- FCN_V(tgMH_QT_Init_Axis_Angle_ELEM_S) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_Init_Axis_Angle_ELEM_S)( VAR_T(C) fX, VAR_T(C) fY, VAR_T(C) fZ, VAR_T(C) fAngle )
{
    VAR_T()                             fSinA, fCosA;
    VEC_S_T(1)                          vRet;

#if TgCOMPILE_ASSERT
    vRet = FCN_V(tgMH_Init_Vector_ELEM_S)( fX, fY, fZ );
    TgERROR( FCN_F(tgCM_NR1)( FCN_V(tgMH_LEN_S)( vRet ) ));
    TgERROR( !FCN_F(tgPM_NAN)( fAngle ) );
#endif

    FCN_F(tgPM_SINCOS)( &fSinA, &fCosA, TYPE_K(0,5)*fAngle );
    vRet.x = fX * fSinA;
    vRet.y = fY * fSinA;
    vRet.z = fZ * fSinA;
    vRet.w = fCosA;

    return (vRet);
}


/* ---- FCN_V(tgMH_QT_Init_Axis_Angle_S) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_Init_Axis_Angle_S)( VEC_S_T(1,C) vAA )
{
    return (FCN_V(tgMH_QT_Init_Axis_Angle_ELEM_S)( vAA.x, vAA.y, vAA.z, vAA.w ));
}


/* ---- FCN_V(tgMH_QT_Init_Euler_ELEM_S) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_Init_Euler_ELEM_S)( VAR_T(C) fX, VAR_T(C) fy, VAR_T(C) fZ )
{
    VAR_T()                             fSinZ, fCosZ, fSinX, fCosX, fSinY, fCosY; /* [ROLL, PITCH, YAW] */
    VEC_S_T(1)                          vRet;

    FCN_F(tgPM_SINCOS)( &fSinX, &fCosX, TYPE_K(0,5)*fX ); /**< Roll */
    FCN_F(tgPM_SINCOS)( &fSinY, &fCosY, TYPE_K(0,5)*fy ); /**< Pitch */
    FCN_F(tgPM_SINCOS)( &fSinZ, &fCosZ, TYPE_K(0,5)*fZ ); /**< Yaw */

    {
        VAR_T(C)        fTA = fSinX*fCosY;
        VAR_T(C)        fTB = fCosX*fSinY;
        VAR_T(C)        fTC = fCosX*fCosY;
        VAR_T(C)        fTD = fSinX*fSinY;

        vRet.x = fTA*fCosZ - fTB*fSinZ;
        vRet.y = fTB*fCosZ + fTA*fSinZ;
        vRet.z = fTC*fSinZ - fTD*fCosZ;
        vRet.w = fTC*fCosZ + fTD*fSinZ;
    }

    return (vRet);
}


/* ---- FCN_V(tgMH_QT_Init_Euler_S) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_Init_Euler_S)( VEC_S_T(1,C) vEul )
{
    return (FCN_V(tgMH_QT_Init_Euler_ELEM_S)( vEul.x, vEul.y, vEul.z ));
}


/* ---- FCN_V(tgMH_QT_Init_Euler_X_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_Init_Euler_X_S)( VAR_T(C) fX )
{
    VAR_T()                             fSinX, fCosA;
    VEC_S_T(1)                          vRet;

    FCN_F(tgPM_SINCOS)( &fSinX, &fCosA, TYPE_K(0,5)*fX);
    vRet.x = fSinX;
    vRet.y = TYPE_K(0);
    vRet.z = TYPE_K(0);
    vRet.w = fCosA;

    return (vRet);
}


/* ---- FCN_V(tgMH_QT_Init_Euler_Y_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_Init_Euler_Y_S)( VAR_T(C) fY )
{
    VAR_T()                             fSinY, fCosA;
    VEC_S_T(1)                          vRet;

    FCN_F(tgPM_SINCOS)( &fSinY, &fCosA, TYPE_K(0,5)*fY);
    vRet.x = TYPE_K(0);
    vRet.y = fSinY;
    vRet.z = TYPE_K(0);
    vRet.w = fCosA;

    return (vRet);
}


/* ---- FCN_V(tgMH_QT_Init_Euler_Z_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_Init_Euler_Z_S)( VAR_T(C) fZ )
{
    VAR_T()                             fSinZ, fCosA;
    VEC_S_T(1)                          vRet;

    FCN_F(tgPM_SINCOS)( &fSinZ, &fCosA, TYPE_K(0,5)*fZ );
    vRet.x = TYPE_K(0);
    vRet.y = TYPE_K(0);
    vRet.z = fSinZ;
    vRet.w = fCosA;

    return (vRet);
}


/* ---- FCN_V(tgMH_Quat_To_Euler_ELEM_S) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_V(tgMH_Quat_To_Euler_ELEM_S)( VAR_T(PCU) ptyX, VAR_T(PCU) ptyY, VAR_T(PCU) ptyZ, VEC_S_T(1,C) qR0 )
{
    VAR_T(C)        fSinY = TYPE_K(2) * (qR0.m_aData[1] * qR0.m_aData[3] - qR0.m_aData[0] * qR0.m_aData[2]);

    if (TYPE_K(1) + fSinY <= VAR_K(KTgEPS))
    {
        *ptyX = TYPE_K(2) * FCN_F(tgPM_ATAN2)( qR0.m_aData[2], qR0.m_aData[3] );
        *ptyY = -VAR_K(KTgHALF_PI);
        *ptyZ = TYPE_K(0);
    }
    else if (fSinY >= TYPE_K(1) - VAR_K(KTgEPS))
    {
        *ptyX = TYPE_K(2) * FCN_F(tgPM_ATAN2)( qR0.m_aData[0], qR0.m_aData[3] );
        *ptyY = VAR_K(KTgHALF_PI);
        *ptyZ = TYPE_K(0);
    }
    else
    {
        VAR_T(C) fTMPA = TYPE_K(2)*(qR0.m_aData[1] * qR0.m_aData[2] + qR0.m_aData[3] * qR0.m_aData[0]);
        VAR_T(C) fTMPB = TYPE_K(2)*(qR0.m_aData[0] * qR0.m_aData[0] + qR0.m_aData[1] * qR0.m_aData[1]);
        VAR_T(C) fTMPC = TYPE_K(2)*(qR0.m_aData[0] * qR0.m_aData[1] + qR0.m_aData[2] * qR0.m_aData[3]);
        VAR_T(C) fTMPD = TYPE_K(2)*(qR0.m_aData[1] * qR0.m_aData[1] + qR0.m_aData[2] * qR0.m_aData[2]);

        *ptyX = FCN_F(tgPM_ATAN2)( fTMPA, TYPE_K(1) - fTMPB );
        *ptyY = FCN_F(tgPM_ASIN)( fSinY );
        *ptyZ = FCN_F(tgPM_ATAN2)( fTMPC, TYPE_K(1) - fTMPD );
    };
}


/* ---- FCN_V(tgMH_Quat_To_Euler_S) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_Quat_To_Euler_S)( VEC_S_T(1,C) qR0 )
{
    VEC_S_T(1)                          vRet;

    FCN_V(tgMH_Quat_To_Euler_ELEM_S)( &vRet.x, &vRet.y, &vRet.z, qR0 );
    vRet.w = TYPE_K(0);
    return (vRet);
}


/* ---- FCN_V(tgMH_QT_INV_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_INV_S)( VEC_S_T(1,C) qR1 )
{
    VEC_S_T(1)                          vR0;

    vR0.x = -qR1.x;
    vR0.y = -qR1.y;
    vR0.z = -qR1.z;
    vR0.w = qR1.w;

    return (vR0);
}


/* ---- FCN_V(tgMH_QT_MUL_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_MUL_S)( VEC_S_T(1,C) qR1, VEC_S_T(1,C) qR2 )
{
    VEC_S_T(1)                          vR0;

    vR0.x =  qR1.x * qR2.w + qR1.y * qR2.z - qR1.z * qR2.y + qR1.w * qR2.x;
    vR0.y = -qR1.x * qR2.z + qR1.y * qR2.w + qR1.z * qR2.x + qR1.w * qR2.y;
    vR0.z =  qR1.x * qR2.y - qR1.y * qR2.x + qR1.z * qR2.w + qR1.w * qR2.z;
    vR0.w = -qR1.x * qR2.x - qR1.y * qR2.y - qR1.z * qR2.z + qR1.w * qR2.w;
    return (vR0);
}

/* ---- FCN_V(tgMH_QT_Slerp_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_Slerp_S)( VAR_T(C) fdT, VEC_S_T(1,C) vR1, VEC_S_T(1,C) vR2 )
{
    VAR_T()                             fCosA;
    VEC_S_T(1)                          vX0, vX1, vX2;
    VAR_T()                             fF0, fF1;

    if (fdT <= TYPE_K(0))
    {
        return (vR1);
    }
    else if (fdT >= TYPE_K(1))
    {
        return (vR2);
    }

    fCosA = FCN_V(tgMH_DOT_S)( vR1, vR2 );

    if (fCosA < TYPE_K(0))
    {
        fCosA = -fCosA;
        vX0 = FCN_V(tgMH_NEG_S)( vR2 );
    }
    else
    {
        vX0 = vR2;
    };

    if ((TYPE_K(1) - fCosA) > VAR_K(KTgEPS))
    {
        VAR_T(C)        fAngle = FCN_F(tgPM_ACOS)( fCosA );
        VAR_T(C)        fInvSinA = TYPE_K(1) / FCN_F(tgPM_SIN)( fAngle );

        fF0 = FCN_F(tgPM_SIN)((TYPE_K(1) - fdT) * fAngle) * fInvSinA;
        fF1 = FCN_F(tgPM_SIN)(fdT * fAngle) * fInvSinA;
    }
    else
    {
        fF0 = TYPE_K(1) - fdT;
        fF1 = fdT;
    }

    vX1 = FCN_V(tgMH_MUL_VS_S)( vR1, fF0 );
    vX2 = FCN_V(tgMH_MUL_VS_S)( vX0, fF1 );

    return (FCN_V(tgMH_ADD_S)( vX1, vX2 ));
}


/* ---- FCN_V(tgMH_QT_Vector_To_Vector_S) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_Vector_To_Vector_S)( VEC_S_T(1,C) vFrom, VEC_S_T(1,C) vTo )
{
    /* If either the scale or the dot product are invalid this will cause a return of the zero quaternion. */

    VEC_S_T(1)                          qRet;

    VAR_T(C)        fFm_To = FCN_V(tgMH_DOT_S)( vFrom, vTo ); /**< cos(θ) = A*B/|A||B| */
    VAR_T(C)        fScale = FCN_V(tgMH_LEN_S)( vFrom )*FCN_V(tgMH_LEN_S)( vTo );
    VAR_T(C)        fCosA = FCN_F(tgPM_FSEL)( fScale - VAR_K(KTgEPS), fFm_To / fScale, TYPE_K(1) );
    VEC_S_T(1,C)    vAxis = FCN_V(tgMH_UCX_S)( vFrom, vTo );
    VAR_T(C)        fSinHA = FCN_F(tgPM_SQRT)( (TYPE_K(1) - fCosA)*TYPE_K(0,5) );
    VAR_T(C)        fLimit = FCN_F(tgCM_CLP)( fCosA, TYPE_K(-1), TYPE_K(1) );

    /* Ensure that the result is within function range (floating point error) */
    /* Axis of rotation would be the vector perpendicular to both inputs, normalized if necessary */
    /* For an axis-angle, need to generate cos(θ/2) and sin(θ/2) */
    /*  Trig Identity: cos(2θ) = cos²(θ) - sin²(θ) = 2*cos²(θ) - 1 = 1 - 2*sin²(θ) */
    /*                 cos(θ/2) = √((1 + cos(θ))/2) */

    qRet.x = vAxis.m_aData[0] * fSinHA;
    qRet.y = vAxis.m_aData[1] * fSinHA;
    qRet.z = vAxis.m_aData[2] * fSinHA;
    qRet.w = FCN_F(tgPM_SQRT)( (TYPE_K(1) + fLimit)*TYPE_K(0,5) );

    return (qRet);
}


/* ---- FCN_V(tgMH_QT_TX_S) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_TX_S)( VEC_S_T(1,C) vV0, VEC_S_T(1,C) qR0 )
{
    return (FCN_V(tgMH_QT_MUL_S)( FCN_V(tgMH_QT_MUL_S)( qR0, vV0 ), FCN_V(tgMH_QT_INV_S)( qR0 ) ));
}


/* ---- FCN_V(tgMH_QT_INV_TX_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_QT_INV_TX_S)( VEC_S_T(1,C) vV0, VEC_S_T(1,C) qR0 )
{
    return (FCN_V(tgMH_QT_MUL_S)( FCN_V(tgMH_QT_MUL_S)( FCN_V(tgMH_QT_INV_S)( qR0 ), vV0 ), qR0 ));
}


/* ---- FCN_V(tgMH_Rotate_Vector_Euler_X_S) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_Rotate_Vector_Euler_X_S)( VEC_S_T(1,C) vV0, VAR_T(C) fX )
{
    VAR_T()                             fSinX, fCosX;
    VEC_S_T(1)                          qRet;

    FCN_F(tgPM_SINCOS)( &fSinX, &fCosX, fX );
    qRet.x = vV0.x;
    qRet.y = vV0.y*fCosX - vV0.z*fSinX;
    qRet.z = vV0.y*fSinX + vV0.z*fCosX;
    qRet.w = vV0.w;

    return (qRet);
}


/* ---- FCN_V(tgMH_Rotate_Vector_Euler_Y_S) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_Rotate_Vector_Euler_Y_S)( VEC_S_T(1,C) vV0, VAR_T(C) fy )
{
    VAR_T()                             fSinY, fCosY;
    VEC_S_T(1)                          qRet;

    FCN_F(tgPM_SINCOS)( &fSinY, &fCosY, fy );
    qRet.x = vV0.z*fSinY + vV0.x*fCosY;
    qRet.y = vV0.y;
    qRet.z = vV0.z*fCosY - vV0.x*fSinY;
    qRet.w = vV0.w;

    return (qRet);
}


/* ---- FCN_V(tgMH_Rotate_Vector_Euler_Z_S) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_V(tgMH_Rotate_Vector_Euler_Z_S)( VEC_S_T(1,C) vV0, VAR_T(C) fZ )
{
    VAR_T()                             fSinZ, fCosZ;
    VEC_S_T(1)                          qRet;

    FCN_F(tgPM_SINCOS)( &fSinZ, &fCosZ, fZ );
    qRet.x = vV0.x*fCosZ - vV0.y*fSinZ;
    qRet.y = vV0.x*fSinZ + vV0.y*fCosZ;
    qRet.z = vV0.z;
    qRet.w = vV0.w;

    return (qRet);
}


/* =============================================================================================================================================================================== */
#endif
