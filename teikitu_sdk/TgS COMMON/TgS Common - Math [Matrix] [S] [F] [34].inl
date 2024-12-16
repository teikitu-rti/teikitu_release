/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Matrix] [S] [F] [34].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_MATRIX_S_F_34_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/*  TgS Common - Math API [Matrix] [S] [F]                                                                                                                                         */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- FCN_M(tgMH_Init_ROT_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_ROT_S)( MAT_S_T(PCU) pmM0, MAT_S_T(CPCU) pmM1 )
{
    pmM0->_11 = pmM1->_11; pmM0->_21 = pmM1->_21; pmM0->_31 = pmM1->_31; pmM0->_41 = TYPE_K(0);
    pmM0->_12 = pmM1->_12; pmM0->_22 = pmM1->_22; pmM0->_32 = pmM1->_32; pmM0->_42 = TYPE_K(0);
    pmM0->_13 = pmM1->_13; pmM0->_23 = pmM1->_23; pmM0->_33 = pmM1->_33; pmM0->_43 = TYPE_K(0);
}

/* ---- FCN_M(tgMH_Init_T_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_T_S)( MAT_S_T(PCU) pmM0, VEC_S_T(1,C) vS0 )
{
    pmM0->_11 = TYPE_K(1); pmM0->_21 = TYPE_K(0); pmM0->_31 = TYPE_K(0); pmM0->_41 = vS0.m_aData[0];
    pmM0->_12 = TYPE_K(0); pmM0->_22 = TYPE_K(1); pmM0->_32 = TYPE_K(0); pmM0->_42 = vS0.m_aData[1];
    pmM0->_13 = TYPE_K(0); pmM0->_23 = TYPE_K(0); pmM0->_33 = TYPE_K(1); pmM0->_43 = vS0.m_aData[2];
}


/* ---- FCN_M(tgMH_Init_T_ELEM_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_T_ELEM_S)( MAT_S_T(PCU) pmM0, VAR_T(C) fX, VAR_T(C) fY, VAR_T(C) fZ )
{
    pmM0->_11 = TYPE_K(1); pmM0->_21 = TYPE_K(0); pmM0->_31 = TYPE_K(0); pmM0->_41 = fX;
    pmM0->_12 = TYPE_K(0); pmM0->_22 = TYPE_K(1); pmM0->_32 = TYPE_K(0); pmM0->_42 = fY;
    pmM0->_13 = TYPE_K(0); pmM0->_23 = TYPE_K(0); pmM0->_33 = TYPE_K(1); pmM0->_43 = fZ;
}


/* ---- FCN_M(tgMH_Init_Euler_S) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Euler_S)( MAT_S_T(PCU) pmOut, VEC_S_T(1,C) vEul )
{
    FCN_M(tgMH_Set_Euler_ELEM_S)( pmOut, vEul.x, vEul.y, vEul.z );
    pmOut->_41 = TYPE_K(0);
    pmOut->_42 = TYPE_K(0);
    pmOut->_43 = TYPE_K(0);
}


/* ---- FCN_M(tgMH_Init_Euler_ELEM_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Euler_ELEM_S)( MAT_S_T(PCU) pmOut, VAR_T(C) fX, VAR_T(C) fY, VAR_T(C) fZ )
{
    FCN_M(tgMH_Set_Euler_ELEM_S)( pmOut, fX, fY, fZ );
    pmOut->_41 = TYPE_K(0);
    pmOut->_42 = TYPE_K(0);
    pmOut->_43 = TYPE_K(0);
}


/* ---- FCN_M(tgMH_Init_Euler_X_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Euler_X_S)( MAT_S_T(PCU) pmOut, VAR_T(C) fX )
{
    FCN_M(tgMH_Set_Euler_X_S)( pmOut, fX );
    pmOut->_41 = TYPE_K(0);
    pmOut->_42 = TYPE_K(0);
    pmOut->_43 = TYPE_K(0);
}


/* ---- FCN_M(tgMH_Init_Euler_Y_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Euler_Y_S)( MAT_S_T(PCU) pmOut, VAR_T(C) fY )
{
    FCN_M(tgMH_Set_Euler_Y_S)( pmOut, fY );
    pmOut->_41 = TYPE_K(0);
    pmOut->_42 = TYPE_K(0);
    pmOut->_43 = TYPE_K(0);
}


/* ---- FCN_M(tgMH_Init_Euler_Z_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Euler_Z_S)( MAT_S_T(PCU) pmOut, VAR_T(C) fZ )
{
    FCN_M(tgMH_Set_Euler_Z_S)( pmOut, fZ );
    pmOut->_41 = TYPE_K(0);
    pmOut->_42 = TYPE_K(0);
    pmOut->_43 = TYPE_K(0);
}


/* ---- FCN_M(tgMH_Init_Quat_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Quat_S)( MAT_S_T(PCU) pmOut, VEC_S_T(1,C) pqR0 )
{
    FCN_M(tgMH_Set_Quat_S)( pmOut, pqR0 );
    pmOut->_41 = TYPE_K(0);
    pmOut->_42 = TYPE_K(0);
    pmOut->_43 = TYPE_K(0);
}


/* ---- FCN_M(tgMH_Init_Reference_Frame_From_Vector_And_Position_S) -------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Reference_Frame_From_Vector_And_Position_S)( MAT_S_T(PCU) pmOut, VEC_S_T(1,C) vAxis, VEC_S_T(1,C) vS0 )
{
    VEC_S_T(1)                              vB0, vB1;

    FCN_V(tgMH_Init_Basis_From_Vector_S)( &vB0, &vB1, vAxis );
    
    pmOut->_11 = vB0.x;
    pmOut->_21 = vAxis.x;
    pmOut->_31 = vB1.x;
    pmOut->_41 = vS0.x;

    pmOut->_12 = vB0.y;
    pmOut->_22 = vAxis.y;
    pmOut->_32 = vB1.y;
    pmOut->_42 = vS0.y;

    pmOut->_13 = vB0.z;
    pmOut->_23 = vAxis.z;
    pmOut->_33 = vB1.z;
    pmOut->_43 = vS0.z;
}


/* ---- FCN_M(tgMH_Init_Reference_Frame_From_Basis_Axes_And_Position_S) ---------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Reference_Frame_From_Basis_Axes_And_Position_S)( MAT_S_T(PCU) pmOut, VEC_S_T(1,C) vA0, VEC_S_T(1,C) vA1, VEC_S_T(1,C) vA2, VEC_S_T(1,C) vC0 )
{
    VEC_S_T(4) mM1 = {.m_avCol = { vA0, vA1, vA2, vC0 } };
    VEC_S_T(4) mM2;
    
    FCN_V(tgMH_TR_S,4)( &mM2, &mM1 );

    pmOut->m_avCol[0] = mM2.m_avCol[0];
    pmOut->m_avCol[1] = mM2.m_avCol[1];
    pmOut->m_avCol[2] = mM2.m_avCol[2];
}


/* ---- FCN_M(tgMH_Init_Reference_Frame_From_Quaternion_Position_S) -------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Reference_Frame_From_Quaternion_Position_S)( MAT_S_T(PC) pmOut, VEC_S_T(1,C) qR0, VEC_S_T(1,C) vS0 )
{
    FCN_M(tgMH_Init_Quat_S)( pmOut, qR0 );
    pmOut->_41 = vS0.m_aData[0];
    pmOut->_42 = vS0.m_aData[1];
    pmOut->_43 = vS0.m_aData[2];
}


/* ---- FCN_M(tgMH_Init_Reference_Frame_From_Scale_Quaternion_Position_S) ---------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Reference_Frame_From_Scale_Quaternion_Position_S)( MAT_S_T(PC) pmOut, VEC_S_T(1,C) vX0, VEC_S_T(1,C) qR0, VEC_S_T(1,C) vS0 )
{
    FCN_M(tgMH_Init_Quat_S)( pmOut, qR0 );
    pmOut->_11 *= vX0.m_aData[0];
    pmOut->_12 *= vX0.m_aData[0];
    pmOut->_13 *= vX0.m_aData[0];
    pmOut->_21 *= vX0.m_aData[1];
    pmOut->_22 *= vX0.m_aData[1];
    pmOut->_23 *= vX0.m_aData[1];
    pmOut->_31 *= vX0.m_aData[2];
    pmOut->_32 *= vX0.m_aData[2];
    pmOut->_33 *= vX0.m_aData[2];
    pmOut->_41 = vS0.m_aData[0];
    pmOut->_42 = vS0.m_aData[1];
    pmOut->_43 = vS0.m_aData[2];
}


/* ---- FCN_M(tgMH_Is_Valid_Reference_Frame_S) ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_M(tgMH_Is_Valid_Reference_Frame_S)( MAT_S_T(CPCU) pmM0 )
{
    if (!FCN_V(tgMH_Is_Valid_Unit_Vector_S)( FCN_M(tgMH_Query_Axis_0_S)( pmM0 ) ))
        return (false);
    if (!FCN_V(tgMH_Is_Valid_Unit_Vector_S)( FCN_M(tgMH_Query_Axis_1_S)( pmM0 ) ))
        return (false);
    if (!FCN_V(tgMH_Is_Valid_Unit_Vector_S)( FCN_M(tgMH_Query_Axis_2_S)( pmM0 ) ))
        return (false);
    if (!FCN_V(tgMH_Is_Valid_Point_S)( FCN_M(tgMH_Query_Axis_3_S)( pmM0 ) ))
        return (false);

    return (true);
}


/* ---- FCN_M(tgMH_CAT_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_CAT_S)( MAT_S_T(PCU) pmOut, MAT_S_T(CPCU) pmM0, MAT_S_T(CPCU) pmM1 )
{
    pmOut->_11 = pmM0->_11 * pmM1->_11 + pmM0->_12 * pmM1->_21 + pmM0->_13 * pmM1->_31;
    pmOut->_12 = pmM0->_11 * pmM1->_12 + pmM0->_12 * pmM1->_22 + pmM0->_13 * pmM1->_32;
    pmOut->_13 = pmM0->_11 * pmM1->_13 + pmM0->_12 * pmM1->_23 + pmM0->_13 * pmM1->_33;

    pmOut->_21 = pmM0->_21 * pmM1->_11 + pmM0->_22 * pmM1->_21 + pmM0->_23 * pmM1->_31;
    pmOut->_22 = pmM0->_21 * pmM1->_12 + pmM0->_22 * pmM1->_22 + pmM0->_23 * pmM1->_32;
    pmOut->_23 = pmM0->_21 * pmM1->_13 + pmM0->_22 * pmM1->_23 + pmM0->_23 * pmM1->_33;

    pmOut->_31 = pmM0->_31 * pmM1->_11 + pmM0->_32 * pmM1->_21 + pmM0->_33 * pmM1->_31;
    pmOut->_32 = pmM0->_31 * pmM1->_12 + pmM0->_32 * pmM1->_22 + pmM0->_33 * pmM1->_32;
    pmOut->_33 = pmM0->_31 * pmM1->_13 + pmM0->_32 * pmM1->_23 + pmM0->_33 * pmM1->_33;

    pmOut->_41 = pmM0->_41 * pmM1->_11 + pmM0->_42 * pmM1->_21 + pmM0->_43 * pmM1->_31 + pmM1->_41;
    pmOut->_42 = pmM0->_41 * pmM1->_12 + pmM0->_42 * pmM1->_22 + pmM0->_43 * pmM1->_32 + pmM1->_42;
    pmOut->_43 = pmM0->_41 * pmM1->_13 + pmM0->_42 * pmM1->_23 + pmM0->_43 * pmM1->_33 + pmM1->_43;
}


/* ---- FCN_M(tgMH_INV_DET_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_INV_DET_S)( VEC_S_T(4,PCU) pmOut, VAR_T(C) fDet, MAT_S_T(CPCU) pmM1 )
{
    if (FCN_F(tgCM_NR0)(fDet*TYPE_K(10) ))
    {
        TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Matrix is Singular - Zero Matrix returned." );
        FCN_V(tgMH_CLI_S,4)( pmOut );
    }
    else
    {
        VAR_T(C)        fInvDet = TYPE_K(1) / fDet;

        VAR_T(C)        fA2334 = pmM1->_32 * pmM1->_43 - pmM1->_33 * pmM1->_42;
        VAR_T(C)        fA1334 = pmM1->_31 * pmM1->_43 - pmM1->_33 * pmM1->_41;
        VAR_T(C)        fA1234 = pmM1->_31 * pmM1->_42 - pmM1->_32 * pmM1->_41;
        VAR_T(C)        fA2324 = pmM1->_22 * pmM1->_43 - pmM1->_23 * pmM1->_42;
        VAR_T(C)        fA2323 = pmM1->_22 * pmM1->_33 - pmM1->_23 * pmM1->_32;
        VAR_T(C)        fA1324 = pmM1->_21 * pmM1->_43 - pmM1->_23 * pmM1->_41;
        VAR_T(C)        fA1323 = pmM1->_21 * pmM1->_33 - pmM1->_23 * pmM1->_31;
        VAR_T(C)        fA1224 = pmM1->_21 * pmM1->_42 - pmM1->_22 * pmM1->_41;
        VAR_T(C)        fA1223 = pmM1->_21 * pmM1->_32 - pmM1->_22 * pmM1->_31;

        pmOut->_11 = fInvDet *   ( pmM1->_22 * pmM1->_33 - pmM1->_23 * pmM1->_32 );
        pmOut->_12 = fInvDet * - ( pmM1->_12 * pmM1->_33 - pmM1->_13 * pmM1->_32 );
        pmOut->_13 = fInvDet *   ( pmM1->_12 * pmM1->_23 - pmM1->_13 * pmM1->_22 );
        pmOut->_14 = 0;
        pmOut->_21 = fInvDet * - ( pmM1->_21 * pmM1->_33 - pmM1->_23 * pmM1->_31 );
        pmOut->_22 = fInvDet *   ( pmM1->_11 * pmM1->_33 - pmM1->_13 * pmM1->_31 );
        pmOut->_23 = fInvDet * - ( pmM1->_11 * pmM1->_23 - pmM1->_13 * pmM1->_21 );
        pmOut->_24 = 0;
        pmOut->_31 = fInvDet *   ( pmM1->_21 * pmM1->_32 - pmM1->_22 * pmM1->_31 );
        pmOut->_32 = fInvDet * - ( pmM1->_11 * pmM1->_32 - pmM1->_12 * pmM1->_31 );
        pmOut->_33 = fInvDet *   ( pmM1->_11 * pmM1->_22 - pmM1->_12 * pmM1->_21 );
        pmOut->_34 = 0;
        pmOut->_41 = fInvDet * - ( pmM1->_21 * fA2334 - pmM1->_22 * fA1334 + pmM1->_23 * fA1234 );
        pmOut->_42 = fInvDet *   ( pmM1->_11 * fA2334 - pmM1->_12 * fA1334 + pmM1->_13 * fA1234 );
        pmOut->_43 = fInvDet * - ( pmM1->_11 * fA2324 - pmM1->_12 * fA1324 + pmM1->_13 * fA1224 );
        pmOut->_44 = fInvDet *   ( pmM1->_11 * fA2323 - pmM1->_12 * fA1323 + pmM1->_13 * fA1223 );
    };
}


/* ---- FCN_M(tgMH_INV_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_INV_S)( VEC_S_T(4,PCU) pmOut, MAT_S_T(CPCU) pmM1 )
{
    VAR_T(C) fDet = pmM1->_11 * ( pmM1->_22 * pmM1->_33 - pmM1->_23 * pmM1->_32 )
                  - pmM1->_12 * ( pmM1->_21 * pmM1->_33 - pmM1->_23 * pmM1->_31 )
                  + pmM1->_13 * ( pmM1->_21 * pmM1->_32 - pmM1->_22 * pmM1->_31 );

    if (FCN_F(tgCM_NR0)(fDet*TYPE_K(10) ))
    {
        TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Matrix is Singular - Zero Matrix returned." );
        FCN_V(tgMH_CLI_S,4)( pmOut );
    }
    else
    {
        VAR_T(C)        fA2334 = pmM1->_32 * pmM1->_43 - pmM1->_33 * pmM1->_42;
        VAR_T(C)        fA1334 = pmM1->_31 * pmM1->_43 - pmM1->_33 * pmM1->_41;
        VAR_T(C)        fA1234 = pmM1->_31 * pmM1->_42 - pmM1->_32 * pmM1->_41;
        VAR_T(C)        fA2324 = pmM1->_22 * pmM1->_43 - pmM1->_23 * pmM1->_42;
        VAR_T(C)        fA2323 = pmM1->_22 * pmM1->_33 - pmM1->_23 * pmM1->_32;
        VAR_T(C)        fA1324 = pmM1->_21 * pmM1->_43 - pmM1->_23 * pmM1->_41;
        VAR_T(C)        fA1323 = pmM1->_21 * pmM1->_33 - pmM1->_23 * pmM1->_31;
        VAR_T(C)        fA1224 = pmM1->_21 * pmM1->_42 - pmM1->_22 * pmM1->_41;
        VAR_T(C)        fA1223 = pmM1->_21 * pmM1->_32 - pmM1->_22 * pmM1->_31;
    
        VAR_T(C)        fInvDet = TYPE_K(1) / fDet;

        pmOut->_11 = fInvDet *   ( pmM1->_22 * pmM1->_33 - pmM1->_23 * pmM1->_32 );
        pmOut->_12 = fInvDet * - ( pmM1->_12 * pmM1->_33 - pmM1->_13 * pmM1->_32 );
        pmOut->_13 = fInvDet *   ( pmM1->_12 * pmM1->_23 - pmM1->_13 * pmM1->_22 );
        pmOut->_14 = 0;
        pmOut->_21 = fInvDet * - ( pmM1->_21 * pmM1->_33 - pmM1->_23 * pmM1->_31 );
        pmOut->_22 = fInvDet *   ( pmM1->_11 * pmM1->_33 - pmM1->_13 * pmM1->_31 );
        pmOut->_23 = fInvDet * - ( pmM1->_11 * pmM1->_23 - pmM1->_13 * pmM1->_21 );
        pmOut->_24 = 0;
        pmOut->_31 = fInvDet *   ( pmM1->_21 * pmM1->_32 - pmM1->_22 * pmM1->_31 );
        pmOut->_32 = fInvDet * - ( pmM1->_11 * pmM1->_32 - pmM1->_12 * pmM1->_31 );
        pmOut->_33 = fInvDet *   ( pmM1->_11 * pmM1->_22 - pmM1->_12 * pmM1->_21 );
        pmOut->_34 = 0;
        pmOut->_41 = fInvDet * - ( pmM1->_21 * fA2334 - pmM1->_22 * fA1334 + pmM1->_23 * fA1234 );
        pmOut->_42 = fInvDet *   ( pmM1->_11 * fA2334 - pmM1->_12 * fA1334 + pmM1->_13 * fA1234 );
        pmOut->_43 = fInvDet * - ( pmM1->_11 * fA2324 - pmM1->_12 * fA1324 + pmM1->_13 * fA1224 );
        pmOut->_44 = fInvDet *   ( pmM1->_11 * fA2323 - pmM1->_12 * fA1323 + pmM1->_13 * fA1223 );
    };
}


/* ---- FCN_M(tgMH_DET_S) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCN_M(tgMH_DET_S)( MAT_S_T(CPCU) pmM1 )
{
    VAR_T(C) fDet = pmM1->_11 * ( pmM1->_22 * pmM1->_33 - pmM1->_23 * pmM1->_32 )
                  - pmM1->_12 * ( pmM1->_21 * pmM1->_33 - pmM1->_23 * pmM1->_31 )
                  + pmM1->_13 * ( pmM1->_21 * pmM1->_32 - pmM1->_22 * pmM1->_31 );

    return (fDet);
}


/* ---- FCN_M(tgMH_TX_S) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_TX_S)( VEC_S_T(1,C) vARG_0, MAT_S_T(CPCU) ptxM0 )
{
    VEC_S_T(1)                          vRet;

    vRet.x = FCN_V(tgMH_DOT_S)( ptxM0->m_avCol[0], vARG_0 );
    vRet.y = FCN_V(tgMH_DOT_S)( ptxM0->m_avCol[1], vARG_0 );
    vRet.z = FCN_V(tgMH_DOT_S)( ptxM0->m_avCol[2], vARG_0 );
    vRet.w = vARG_0.w;

    return (vRet);
}


/* ---- FCN_M(tgMH_TX_P_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_TX_P_S)( VEC_S_T(1,C) vARG_0, MAT_S_T(CPCU) pmTX )
{
    VEC_S_T(1)                          vRet;

    vRet.x = FCN_V(tgMH_DOT3_S)( pmTX->m_avCol[0], vARG_0 ) + pmTX->_41;
    vRet.y = FCN_V(tgMH_DOT3_S)( pmTX->m_avCol[1], vARG_0 ) + pmTX->_42;
    vRet.z = FCN_V(tgMH_DOT3_S)( pmTX->m_avCol[2], vARG_0 ) + pmTX->_43;
    vRet.w = TYPE_K(1);

    return (vRet);
}


/* ---- FCN_M(tgMH_TX_V_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_TX_V_S)( VEC_S_T(1,C) vARG_0, MAT_S_T(CPCU) pmTX )
{
    VEC_S_T(1)                          vRet;

    vRet.x = FCN_V(tgMH_DOT3_S)( pmTX->m_avCol[0], vARG_0 );
    vRet.y = FCN_V(tgMH_DOT3_S)( pmTX->m_avCol[1], vARG_0 );
    vRet.z = FCN_V(tgMH_DOT3_S)( pmTX->m_avCol[2], vARG_0 );
    vRet.w = TYPE_K(0);

    return (vRet);
}


/* ---- FCN_M(tgMH_Query_Row_0_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_Query_Row_0_S)( MAT_S_T(CPCU) pmM0 )
{
    return (FCN_V(tgMH_Init_ELEM_S)(pmM0->_11, pmM0->_12, pmM0->_13, TYPE_K(0)));
}


/* ---- FCN_M(tgMH_Query_Row_1_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_Query_Row_1_S)( MAT_S_T(CPCU) pmM0 )
{
    return (FCN_V(tgMH_Init_ELEM_S)(pmM0->_21, pmM0->_22, pmM0->_23, TYPE_K(0)));
}


/* ---- FCN_M(tgMH_Query_Row_2_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_Query_Row_2_S)( MAT_S_T(CPCU) pmM0 )
{
    return (FCN_V(tgMH_Init_ELEM_S)(pmM0->_31, pmM0->_32, pmM0->_33, TYPE_K(0)));
}


/* ---- FCN_M(tgMH_Query_Row_3_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_Query_Row_3_S)( MAT_S_T(CPCU) pmM0 )
{
    return (FCN_V(tgMH_Init_ELEM_S)(pmM0->_41, pmM0->_42, pmM0->_43, TYPE_K(1)));
}


/* ---- FCN_M(tgMH_Query_Col_0_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_Query_Col_0_S)( MAT_S_T(CPCU) pmM0 )
{
    return (pmM0->m_avCol[0]);
}


/* ---- FCN_M(tgMH_Query_Col_1_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_Query_Col_1_S)( MAT_S_T(CPCU) pmM0 )
{
    return (pmM0->m_avCol[1]);
}


/* ---- FCN_M(tgMH_Query_Col_2_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_Query_Col_2_S)( MAT_S_T(CPCU) pmM0 )
{
    return (pmM0->m_avCol[2]);
}


/* ---- FCN_M(tgMH_Query_Col_3_S) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_Query_Col_3_S)( TgATTRIBUTE_UNUSED MAT_S_T(CPCU) pmM0 )
{
    return (VEC_K(KTgUNIT_W_S));
}


/* ---- FCN_M(tgMH_Query_Axis_0_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_Query_Axis_0_S)( MAT_S_T(CPCU) pmM0 )
{
    return (FCN_V(tgMH_Init_ELEM_S)(pmM0->_11, pmM0->_12, pmM0->_13, TYPE_K(0) ));
}


/* ---- FCN_M(tgMH_Query_Axis_1_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_Query_Axis_1_S)( MAT_S_T(CPCU) pmM0 )
{
    return (FCN_V(tgMH_Init_ELEM_S)(pmM0->_21, pmM0->_22, pmM0->_23, TYPE_K(0) ));
}


/* ---- FCN_M(tgMH_Query_Axis_2_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_Query_Axis_2_S)( MAT_S_T(CPCU) pmM0 )
{
    return (FCN_V(tgMH_Init_ELEM_S)(pmM0->_31, pmM0->_32, pmM0->_33, TYPE_K(0) ));
}


/* ---- FCN_M(tgMH_Query_Axis_3_S) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_S_T(1) FCN_M(tgMH_Query_Axis_3_S)( MAT_S_T(CPCU) pmM0 )
{
    return (FCN_V(tgMH_Init_ELEM_S)(pmM0->_41, pmM0->_42, pmM0->_43, TYPE_K(1) ));
}


/* ---- FCN_M(tgMH_Query_Reference_Frame_S) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_M(tgMH_Query_Reference_Frame_S)( VEC_S_T(1,PCU) pvA0, VEC_S_T(1,PCU) pvA1, VEC_S_T(1,PCU) pvA2, VEC_S_T(1,PCU) pvC0, MAT_S_T(CPCU) pmM0 )
{
    VEC_S_T(4) mM1 = {.m_avCol = { pmM0->m_avCol[0], pmM0->m_avCol[1], pmM0->m_avCol[2], VEC_K(KTgUNIT_W_S) } };
    VEC_S_T(4) mM2;
    
    FCN_V(tgMH_TR_S,4)( &mM2, &mM1 );

    *pvA0 = mM2.m_avCol[0];
    *pvA1 = mM2.m_avCol[1];
    *pvA2 = mM2.m_avCol[2];
    *pvC0 = mM2.m_avCol[3];

    return KTgS_OK;
}


/* ---- FCN_M(tgMH_Matrix_To_Euler_ELEM_S) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Matrix_To_Euler_ELEM_S)( VAR_T(P) pfX, VAR_T(P) pfY, VAR_T(P) pfZ, MAT_S_T(CPC) pxR0 )
{
    if (TYPE_K(1) - pxR0->_13 <= VAR_K(KTgEPS))
    {
        *pfX = FCN_F(tgPM_ATAN2)( pxR0->_21, pxR0->_31 );
        *pfY = -VAR_K(KTgHALF_PI);
        *pfZ = TYPE_K(0);
    }
    else if (VAR_K(KTgEPS) >= TYPE_K(1) + pxR0->_13)
    {
        *pfX = FCN_F(tgPM_ATAN2)( pxR0->_21, pxR0->_31 );
        *pfY = VAR_K(KTgHALF_PI);
        *pfZ = TYPE_K(0);
    }
    else
    {
        *pfX = FCN_F(tgPM_ATAN2)( pxR0->_23, pxR0->_33 );
        *pfY = FCN_F(tgPM_ASIN)( -pxR0->_13 );
        *pfZ = FCN_F(tgPM_ATAN2)( pxR0->_12, pxR0->_11 );
    };
}


/* ---- FCN_M(tgMH_Matrix_To_Euler_S) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Matrix_To_Euler_S)( VEC_S_T(1,PCU) pvEul, MAT_S_T(CPC) pxR0 )
{
    pvEul->w = TYPE_K(0);
    FCN_M(tgMH_Matrix_To_Euler_ELEM_S)( &pvEul->x, &pvEul->y, &pvEul->z, pxR0 );
}


/* ---- FCN_M(tgMH_Matrix_To_Quat_S) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Matrix_To_Quat_S)( VEC_S_T(1,PCU) pqR0, MAT_S_T(CPC) pxR0 )
{
    VAR_T(C)        fTrace = pxR0->_11 + pxR0->_22 + pxR0->_33;

    if (fTrace > VAR_K(KTgEPS))
    {
        VAR_T(C)        fSqrt = FCN_F(tgPM_SQRT)( fTrace + TYPE_K(1) );
        VAR_T(C)        fScale = TYPE_K(0,5) / fSqrt;

        pqR0->x = (pxR0->_32 - pxR0->_23)*fScale;
        pqR0->y = (pxR0->_13 - pxR0->_31)*fScale;
        pqR0->z = (pxR0->_21 - pxR0->_12)*fScale;
        pqR0->w = TYPE_K(0,5)*fSqrt;
    }
    else
    {
        if (pxR0->_11 > pxR0->_22 && pxR0->_11 > pxR0->_33)
        {
            VAR_T(C)        fDiag = TYPE_K(1) + pxR0->_11 - pxR0->_22 - pxR0->_33;
            VAR_T(C)        fSqrt = FCN_F(tgPM_SQRT)( fDiag );
            VAR_T(C)        fScale = TYPE_K(0,5) / fSqrt;

            pqR0->x = TYPE_K(0,5)*fSqrt;
            pqR0->y = (pxR0->_12 + pxR0->_21)*fScale;
            pqR0->z = (pxR0->_13 + pxR0->_31)*fScale;
            pqR0->w = (pxR0->_23 - pxR0->_32)*fScale;
        }
        else if (pxR0->_22 > pxR0->_33)
        {
            VAR_T(C)        fDiag = TYPE_K(1) + pxR0->_22 - pxR0->_11 - pxR0->_33;
            VAR_T(C)        fSqrt = FCN_F(tgPM_SQRT)( fDiag );
            VAR_T(C)        fScale = TYPE_K(0,5) / fSqrt;

            pqR0->x = (pxR0->_12 + pxR0->_21)*fScale;
            pqR0->y = TYPE_K(0,5)*fSqrt;
            pqR0->z = (pxR0->_23 + pxR0->_32)*fScale;
            pqR0->w = (pxR0->_13 - pxR0->_31)*fScale;
        }
        else
        {
            VAR_T(C)        fDiag = TYPE_K(1) + pxR0->_33 - pxR0->_11 - pxR0->_22;
            VAR_T(C)        fSqrt = FCN_F(tgPM_SQRT)( fDiag );
            VAR_T(C)        fScale = TYPE_K(0,5) / fSqrt;

            pqR0->x = (pxR0->_13 + pxR0->_31)*fScale;
            pqR0->y = (pxR0->_23 + pxR0->_32)*fScale;
            pqR0->z = TYPE_K(0,5)*fSqrt;
            pqR0->w = (pxR0->_12 - pxR0->_21)*fScale;
        };
    };
}




/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/*  TgS Common - Math API [Matrix] [S] [F] [34]                                                                                                                                    */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- FCN_M(tgMH_TR_S) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_TR_S)( VEC_S_T(4,PCU) pmTX, MAT_S_T(CPCU) pmM0 )
{
    pmTX->m_aColRow[0][0] = pmM0->m_aColRow[0][0];
    pmTX->m_aColRow[0][1] = pmM0->m_aColRow[1][0];
    pmTX->m_aColRow[0][2] = pmM0->m_aColRow[2][0];
    pmTX->m_aColRow[0][3] = TYPE_K(0);

    pmTX->m_aColRow[1][0] = pmM0->m_aColRow[0][1];
    pmTX->m_aColRow[1][1] = pmM0->m_aColRow[1][1];
    pmTX->m_aColRow[1][2] = pmM0->m_aColRow[2][1];
    pmTX->m_aColRow[1][3] = TYPE_K(0);

    pmTX->m_aColRow[2][0] = pmM0->m_aColRow[0][2];
    pmTX->m_aColRow[2][1] = pmM0->m_aColRow[1][2];
    pmTX->m_aColRow[2][2] = pmM0->m_aColRow[2][2];
    pmTX->m_aColRow[2][3] = TYPE_K(0);

    pmTX->m_aColRow[3][0] = pmM0->m_aColRow[0][3];
    pmTX->m_aColRow[3][1] = pmM0->m_aColRow[1][3];
    pmTX->m_aColRow[3][2] = pmM0->m_aColRow[2][3];
    pmTX->m_aColRow[3][3] = TYPE_K(1);
}


/* ---- FCN_M(tgMH_LookLH_V4_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_LookLH_S)( MAT_S_T(PCU) pmOut, VEC_S_T(1,C) vFrom, VEC_S_T(1,C) vTo, VEC_S_T(1,C) vUp )
{
    VEC_S_T(1)                          vLook, vRight, vCamUp;
    VAR_T()                             fLength, fX0, fX1, fX2;

    /* VectorNorm and Build Orthonormal Camera Axis */
    vLook = FCN_V(tgMH_SUB_S)( vTo, vFrom );
    vLook = FCN_V(tgMH_NORM_LEN_S)( &fLength, vLook );
    if (FCN_F(tgCM_NR0)(fLength))
    {
        FCN_M(tgMH_CLI_S)(pmOut);
        return;
    };

    vRight = FCN_V(tgMH_UCX_LEN_S)( &fLength, vUp, vLook );
    if (FCN_F(tgCM_NR0)(fLength))
    {
        FCN_M(tgMH_CLI_S)(pmOut);
        return;
    };

    vCamUp = FCN_V(tgMH_CX_S)( vLook, vRight );

    fX0 = -FCN_V(tgMH_DOT_S)( vRight, vFrom );
    fX1 = -FCN_V(tgMH_DOT_S)( vCamUp, vFrom );
    fX2 = -FCN_V(tgMH_DOT_S)( vLook, vFrom );

    pmOut->_11 = vRight.x;  pmOut->_12 = vRight.y;  pmOut->_13 = vRight.z;
    pmOut->_21 = vCamUp.x;  pmOut->_22 = vCamUp.y;  pmOut->_23 = vCamUp.z;
    pmOut->_31 = vLook.x;   pmOut->_32 = vLook.y;   pmOut->_33 = vLook.z;
    pmOut->_41 = fX0;       pmOut->_42 = fX1;       pmOut->_43 = fX2;
}


/* ---- FCN_M(tgMH_LookRH_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_LookRH_S)( MAT_S_T(PCU) pmOut, VEC_S_T(1,C) vFrom, VEC_S_T(1,C) vTo, VEC_S_T(1,C) vUp )
{
    VEC_S_T(1)                          vLook, vRight, vCamUp;
    VAR_T()                             fLength, fX0, fX1, fX2;

    /* VectorNorm and Build Orthonormal Camera Axis */
    vLook = FCN_V(tgMH_SUB_S)( vFrom, vTo );
    vLook = FCN_V(tgMH_NORM_LEN_S)( &fLength, vLook );
    if (FCN_F(tgCM_NR0)(fLength))
    {
        FCN_M(tgMH_CLI_S)(pmOut);
        return;
    };

    vRight = FCN_V(tgMH_UCX_LEN_S)( &fLength, vUp, vLook );
    if (FCN_F(tgCM_NR0)(fLength))
    {
        FCN_M(tgMH_CLI_S)(pmOut);
        return;
    };

    vCamUp = FCN_V(tgMH_CX_S)( vLook, vRight );

    fX0 = FCN_V(tgMH_DOT_S)( vRight, vFrom );
    fX1 = FCN_V(tgMH_DOT_S)( vCamUp, vFrom );
    fX2 = FCN_V(tgMH_DOT_S)( vLook, vFrom );

    pmOut->_11 = vRight.x;  pmOut->_12 = vRight.y;  pmOut->_13 = vRight.z;
    pmOut->_21 = vCamUp.x;  pmOut->_22 = vCamUp.y;  pmOut->_23 = vCamUp.z;
    pmOut->_31 = vLook.x;   pmOut->_32 = vLook.y;   pmOut->_33 = vLook.z;
    pmOut->_41 = fX0;       pmOut->_42 = fX1;       pmOut->_43 = fX2;
}


/* ---- FCN_M(tgMH_Look_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Look_S)( MAT_S_T(PCU) pmOut, VEC_S_T(1,C) vFrom, VEC_S_T(1,C) vTo, VEC_S_T(1,C) vUp )
{
    FCN_M(tgMH_LookLH_S)( pmOut, vFrom, vTo, vUp );
}


/* =============================================================================================================================================================================== */
#endif
