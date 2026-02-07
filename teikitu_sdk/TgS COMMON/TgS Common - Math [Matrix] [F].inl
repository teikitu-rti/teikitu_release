/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Matrix] [F].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_MATRIX_F_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/*  TgS Common - Math API [Matrix] [F]                                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


/* ---- FCN_M(tgMH_Init_ROT) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_ROT)( MAT_T(PC) pmOUT_0, MAT_T(CPC) pmARG_1 )
{
    MAT_UN_PTR_T()                      uM0;
    MAT_UN_CONST_PTR_T()                uM1;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    VEC_UN_PTR_M_MEMBER(uM1) = pmARG_1;
    FCN_M(tgMH_Init_ROT_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_PTR_M_MEMBER(uM1) );
}


/* ---- FCN_M(tgMH_Init_T) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_T)( MAT_T(PC) pmOUT_0, VEC_T(1,C) vARG_1 )
{
    MAT_UN_PTR_T()                      uM0;
    VEC_UN_T(1)                         uV0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    VEC_UN_1_MEMBER(uV0) = vARG_1;
    FCN_M(tgMH_Init_T_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_1_MEMBER(uV0) );
}


/* ---- FCN_M(tgMH_Init_T_ELEM) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_T_ELEM)( MAT_T(PC) pmOUT_0, VAR_T(C) fARG_1, VAR_T(C) fARG_2, VAR_T(C) fARG_3 )
{
    MAT_UN_PTR_T()                      uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    FCN_M(tgMH_Init_T_ELEM_S)( VEC_S_UN_PTR_M_MEMBER(uM0), fARG_1, fARG_2, fARG_3 );
}


/* ---- FCN_M(tgMH_Init_Euler) ---------------------------------------------------------------------------------------------------------------------------------------=----------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Euler)( MAT_T(PC) pmOUT_0, VEC_T(1,C) vARG_1 )
{
    MAT_UN_PTR_T()                      uM0;
    VEC_UN_T(1)                         uV0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    VEC_UN_1_MEMBER(uV0) = vARG_1;
    FCN_M(tgMH_Init_Euler_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_1_MEMBER(uV0) );
}


/* ---- FCN_M(tgMH_Init_Euler_ELEM) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Euler_ELEM)( MAT_T(PC) pmOUT_0, VAR_T(C) fARG_1, VAR_T(C) fARG_2, VAR_T(C) fARG_3 )
{
    MAT_UN_PTR_T()                      uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    FCN_M(tgMH_Init_Euler_ELEM_S)( VEC_S_UN_PTR_M_MEMBER(uM0), fARG_1, fARG_2, fARG_3 );
}


/* ---- FCN_M(tgMH_Init_Euler_X) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Euler_X)( MAT_T(PC) pmOUT_0, VAR_T(C) fARG_1 )
{
    MAT_UN_PTR_T()                      uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    FCN_M(tgMH_Init_Euler_X_S)( VEC_S_UN_PTR_M_MEMBER(uM0), fARG_1 );
}


/* ---- FCN_M(tgMH_Init_Euler_Y) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Euler_Y)( MAT_T(PC) pmOUT_0, VAR_T(C) fARG_1 )
{
    MAT_UN_PTR_T()                      uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    FCN_M(tgMH_Init_Euler_Y_S)( VEC_S_UN_PTR_M_MEMBER(uM0), fARG_1 );
}


/* ---- FCN_M(tgMH_Init_Euler_Z) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Euler_Z)( MAT_T(PC) pmOUT_0, VAR_T(C) fARG_1 )
{
    MAT_UN_PTR_T()                      uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    FCN_M(tgMH_Init_Euler_Z_S)( VEC_S_UN_PTR_M_MEMBER(uM0), fARG_1 );
}


/* ---- FCN_M(tgMH_Init_Quat) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Quat)( MAT_T(PC) pmOUT_0, VEC_T(1,C) vARG_1 )
{
    MAT_UN_PTR_T()                      uM0;
    VEC_UN_T(1)                         uV0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    VEC_UN_1_MEMBER(uV0) = vARG_1;
    FCN_M(tgMH_Init_Quat_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_1_MEMBER(uV0) );
}


/* ---- FCN_M(tgMH_Init_Reference_Frame_From_Vector_And_Position) ---------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Reference_Frame_From_Vector_And_Position)( MAT_T(PC) pmOUT_0, VEC_T(1,C) vARG_1, VEC_T(1,C) vARG_2 )
{
    MAT_UN_PTR_T()                      uM0;
    VEC_UN_T(1)                         uV0, uV1;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    VEC_UN_1_MEMBER(uV0) = vARG_1;
    VEC_UN_1_MEMBER(uV1) = vARG_2;
    FCN_M(tgMH_Init_Quat_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_1_MEMBER(uV0) );
    FCN_M(tgMH_Set_T_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_1_MEMBER(uV1) );
}


/* ---- FCN_M(tgMH_Init_Reference_Frame_From_Basis_Axes_And_Position) ------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Reference_Frame_From_Basis_Axes_And_Position)( MAT_T(PC) TgANALYSIS_NO_NULL pmOUT_0, VEC_T(1,C) vARG_1, VEC_T(1,C) vARG_2, VEC_T(1,C) vARG_3, VEC_T(1,C) vARG_4 )
{
    MAT_UN_PTR_T()                      uM0;
    VEC_UN_T(1)                         uV0, uV1, uV2, uV3;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;

    VEC_UN_1_MEMBER(uV0) = vARG_1;
    VEC_UN_1_MEMBER(uV1) = vARG_2;
    VEC_UN_1_MEMBER(uV2) = vARG_3;
    VEC_UN_1_MEMBER(uV3) = vARG_4;

    FCN_M(tgMH_Init_Reference_Frame_From_Basis_Axes_And_Position_S)(
        VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_1_MEMBER(uV0), VEC_S_UN_1_MEMBER(uV1), VEC_S_UN_1_MEMBER(uV2), VEC_S_UN_1_MEMBER(uV3) );
}


/* ---- FCN_M(tgMH_Init_Reference_Frame_From_Quaternion_Position) ---------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Reference_Frame_From_Quaternion_Position)( MAT_T(PC) pmOUT_0, VEC_T(1,C) vARG_1, VEC_T(1,C) vARG_2 )
{
    MAT_UN_PTR_T()                      uM0;
    VEC_UN_T(1)                         uV0, uV1;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    VEC_UN_1_MEMBER(uV0) = vARG_1;
    VEC_UN_1_MEMBER(uV1) = vARG_2;
    FCN_M(tgMH_Init_Reference_Frame_From_Quaternion_Position_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_1_MEMBER(uV0), VEC_S_UN_1_MEMBER(uV1) );
}


/* ---- FCN_M(tgMH_Init_Reference_Frame_From_Scale_Quaternion_Position) ---------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Init_Reference_Frame_From_Scale_Quaternion_Position)( MAT_T(PC) pmOUT_0, VEC_T(1,C) vARG_1, VEC_T(1,C) vARG_2, VEC_T(1,C) vARG_3 )
{
    MAT_UN_PTR_T()                      uM0;
    VEC_UN_T(1)                         uV0, uV1, uV2;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    VEC_UN_1_MEMBER(uV0) = vARG_1;
    VEC_UN_1_MEMBER(uV1) = vARG_2;
    VEC_UN_1_MEMBER(uV2) = vARG_3;
    FCN_M(tgMH_Init_Reference_Frame_From_Scale_Quaternion_Position_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_1_MEMBER(uV0), VEC_S_UN_1_MEMBER(uV1), VEC_S_UN_1_MEMBER(uV2) );
}


/* ---- FCN_M(tgMH_Is_Valid_Reference_Frame) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_M(tgMH_Is_Valid_Reference_Frame)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    return (FCN_M(tgMH_Is_Valid_Reference_Frame_S)( VEC_S_UN_PTR_M_MEMBER(uM0) ));
}


/* ---- FCN_M(tgMH_CAT) ------------------------------------------------------------------------------------------------------------------------------------===------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_CAT)( MAT_T(PC) pmOUT_0, MAT_T(CPC) pmARG_1, MAT_T(CPC) pmARG_2 )
{
    MAT_UN_PTR_T()                      uM0;
    MAT_UN_CONST_PTR_T()                uM1, uM2;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    VEC_UN_PTR_M_MEMBER(uM1) = pmARG_1;
    VEC_UN_PTR_M_MEMBER(uM2) = pmARG_2;

    FCN_M(tgMH_CAT_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_PTR_M_MEMBER(uM1), VEC_S_UN_PTR_M_MEMBER(uM2) );
}


/* ---- FCN_M(tgMH_INV_DET) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_INV_DET)( VEC_T(4,PC) TgANALYSIS_NO_NULL pmOUT_0, VEC_T(1,C) vARG_1, MAT_T(CPC) pmARG_2 )
{
    VEC_UN_PTR_T(4)                     uM0;
    VEC_UN_T(1)                         uV0;
    MAT_UN_CONST_PTR_T()                uM2;

    VEC_UN_PTR_4_MEMBER(uM0) = pmOUT_0;
    VEC_UN_1_MEMBER(uV0) = vARG_1;
    VEC_UN_PTR_M_MEMBER(uM2) = pmARG_2;
    FCN_M(tgMH_INV_DET_S)( VEC_S_UN_PTR_4_MEMBER(uM0), VEC_S_UN_1_MEMBER(uV0).x, VEC_S_UN_PTR_M_MEMBER(uM2) );
}


/* ---- FCN_M(tgMH_INV) -------------------------------------------------------------------------------------------------------------------------------===------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_INV)( VEC_T(4,PC) TgANALYSIS_NO_NULL pmOUT_0, MAT_T(CPC) pmARG_1 )
{
    VEC_UN_PTR_T(4)                     uM0;
    MAT_UN_CONST_PTR_T()                uM1;

    VEC_UN_PTR_4_MEMBER(uM0) = pmOUT_0;
    VEC_UN_PTR_M_MEMBER(uM1) = pmARG_1;
    FCN_M(tgMH_INV_S)( VEC_S_UN_PTR_4_MEMBER(uM0), VEC_S_UN_PTR_M_MEMBER(uM1) );
}


/* ---- FCN_M(tgMH_DET) ---------------------------------------------------------------------------------------------------------------------------------===---------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_DET)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_T(1)                            vResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    vResult = FCN_V(tgMH_SET1)( FCN_M(tgMH_DET_S)( VEC_S_UN_PTR_M_MEMBER(uM0) ) );
    return (vResult);
}

                                                                             
/* ---- FCN_M(tgMH_TX) ----------------------------------------------------------------------------------------------------------------------------====--------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_TX)( VEC_T(1,C) vARG_0, MAT_T(CPC) pmARG_1 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uV0, uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_1;
    VEC_UN_1_MEMBER(uV0) = vARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_TX_S)( VEC_S_UN_1_MEMBER(uV0), VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_TX_P) --------------------------------------------------------------------------------------------------------------------------------------------==----------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_TX_P)( VEC_T(1,C) vARG_0, MAT_T(CPC) pmARG_1 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uV0, uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_1;
    VEC_UN_1_MEMBER(uV0) = vARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_TX_P_S)( VEC_S_UN_1_MEMBER(uV0), VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_TX_V) --------------------------------------------------------------------------------------------------------------------------------------------------==----- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_TX_V)( VEC_T(1,C) vARG_0, MAT_T(CPC) pmARG_1 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uV0, uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_1;
    VEC_UN_1_MEMBER(uV0) = vARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_TX_V_S)( VEC_S_UN_1_MEMBER(uV0), VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Row_0) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_Query_Row_0)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_Query_Row_0_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Row_1) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_Query_Row_1)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_Query_Row_1_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Row_2) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_Query_Row_2)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_Query_Row_2_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Row_3) --------------------------------------------------------------------------------------------------------------------------------------=----------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_Query_Row_3)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_Query_Row_3_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Col_0) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_Query_Col_0)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_Query_Col_0_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Col_1) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_Query_Col_1)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_Query_Col_1_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Col_2) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_Query_Col_2)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_Query_Col_2_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Col_3) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_Query_Col_3)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_Query_Col_3_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Axis_0) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_Query_Axis_0)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_Query_Axis_0_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Axis_1) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_Query_Axis_1)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_Query_Axis_1_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Axis_2) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_Query_Axis_2)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_Query_Axis_2_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Axis_3) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_M(tgMH_Query_Axis_3)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_T(1)                         uResult;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    VEC_S_UN_1_MEMBER(uResult) = FCN_M(tgMH_Query_Axis_3_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_M(tgMH_Query_Reference_Frame) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_M(tgMH_Query_Reference_Frame)( VEC_T(1,P) pvOUT_0, VEC_T(1,P) pvOUT_1, VEC_T(1,P) pvOUT_2, VEC_T(1,P) pvOUT_3, MAT_T(CPC) pmARG_4 )
{
    MAT_UN_CONST_PTR_T()                uM0;
    VEC_UN_PTR_T(1)                     uV0, uV1, uV2, uV3;

    VEC_UN_PTR_1_MEMBER(uV0) = pvOUT_0;
    VEC_UN_PTR_1_MEMBER(uV1) = pvOUT_1;
    VEC_UN_PTR_1_MEMBER(uV2) = pvOUT_2;
    VEC_UN_PTR_1_MEMBER(uV3) = pvOUT_3;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_4;

    return FCN_M(tgMH_Query_Reference_Frame_S)( VEC_S_UN_PTR_1_MEMBER(uV0), VEC_S_UN_PTR_1_MEMBER(uV1), VEC_S_UN_PTR_1_MEMBER(uV2), VEC_S_UN_PTR_1_MEMBER(uV3), VEC_S_UN_PTR_M_MEMBER(uM0) );
}


/* ---- FCN_M(tgMH_Matrix_To_Euler_ELEM) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Matrix_To_Euler_ELEM)( VAR_T(P) pfOUT_0, VAR_T(P) pfOUT_1, VAR_T(P) pfOUT_2, MAT_T(CPC) pmARG_3 )
{
    MAT_UN_CONST_PTR_T()                uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_3;

    FCN_M(tgMH_Matrix_To_Euler_ELEM_S)( pfOUT_0, pfOUT_1, pfOUT_2, VEC_S_UN_PTR_M_MEMBER(uM0) );

}


/* ---- FCN_M(tgMH_Matrix_To_Euler) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Matrix_To_Euler)( VEC_T(1,PC) pvOUT_0, MAT_T(CPC) pmARG_1 )
{
    VEC_UN_PTR_T(1)                     uV0;
    MAT_UN_CONST_PTR_T()                uM0;

    VEC_UN_PTR_1_MEMBER(uV0) = pvOUT_0;
    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_1;

    FCN_M(tgMH_Matrix_To_Euler_S)( VEC_S_UN_PTR_1_MEMBER(uV0), VEC_S_UN_PTR_M_MEMBER(uM0) );
}


/* ---- FCN_M(tgMH_Matrix_To_Quat) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Matrix_To_Quat)( VEC_T(1,PC) pvOUT_0, MAT_T(CPC) pmARG_1 )
{
    VEC_UN_PTR_T(1)                     uV0;
    MAT_UN_CONST_PTR_T()                uM0;

    VEC_UN_PTR_1_MEMBER(uV0) = pvOUT_0;
    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_1;

    FCN_M(tgMH_Matrix_To_Quat_S)( VEC_S_UN_PTR_1_MEMBER(uV0), VEC_S_UN_PTR_M_MEMBER(uM0) );
}




/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/*  Implementation: Matrix Size Specific                                                                                                                                           */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- FCN_M(tgMH_CLI) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_CLI)( MAT_T(PC) pmOUT_0 )
{
    MAT_UN_PTR_T()                      uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    FCN_M(tgMH_CLI_S)( VEC_S_UN_PTR_M_MEMBER(uM0) );
}


/* ---- FCN_M(tgMH_DIAG) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_DIAG)( MAT_T(PC) pmOUT_0, VAR_T(C) fARG_1 )
{
    MAT_UN_PTR_T()                      uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    FCN_M(tgMH_DIAG_S)( VEC_S_UN_PTR_M_MEMBER(uM0), fARG_1 );
}


/* ---- FCN_M(tgMH_Set_Rot) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Set_Rot)( MAT_T(PC) TgANALYSIS_NO_NULL pmOUT_0, MAT_T(CPC) pmARG_1 )
{
    MAT_UN_PTR_T()                      uM0;
    MAT_UN_CONST_PTR_T()                uM1;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    VEC_UN_PTR_M_MEMBER(uM1) = pmARG_1;
    FCN_M(tgMH_Set_Rot_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_PTR_M_MEMBER(uM1) );
}


/* ---- FCN_M(tgMH_Set_T) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Set_T)( MAT_T(PC) TgANALYSIS_NO_NULL pmOUT_0, VEC_T(1,C) vARG_1 )
{
    MAT_UN_PTR_T()                      uM0;
    VEC_UN_T(1)                         uV0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    VEC_UN_1_MEMBER(uV0) = vARG_1;
    FCN_M(tgMH_Set_T_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_1_MEMBER(uV0) );
}


/* ---- FCN_M(tgMH_Set_T_ELEM) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Set_T_ELEM)( MAT_T(PC) TgANALYSIS_NO_NULL pmOUT_0, VAR_T(C) fARG_1, VAR_T(C) fARG_2, VAR_T(C) fARG_3 )
{
    MAT_UN_PTR_T()                      uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    FCN_M(tgMH_Set_T_ELEM_S)( VEC_S_UN_PTR_M_MEMBER(uM0), fARG_1, fARG_2, fARG_3 );
}


/* ---- FCN_M(tgMH_Set_Euler) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Set_Euler)( MAT_T(PC) TgANALYSIS_NO_NULL pmOUT_0, VEC_T(1,C) vARG_1 )
{
    MAT_UN_PTR_T()                      uM0;
    VEC_UN_T(1)                         uV0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    VEC_UN_1_MEMBER(uV0) = vARG_1;
    FCN_M(tgMH_Set_Euler_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_1_MEMBER(uV0) );
}


/* ---- FCN_M(tgMH_Set_Euler_ELEM) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Set_Euler_ELEM)( MAT_T(PC) TgANALYSIS_NO_NULL pmOUT_0, VAR_T(C) fARG_1, VAR_T(C) fARG_2, VAR_T(C) fARG_3 )
{
    MAT_UN_PTR_T()                      uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    FCN_M(tgMH_Set_Euler_ELEM_S)( VEC_S_UN_PTR_M_MEMBER(uM0), fARG_1, fARG_2, fARG_3 );
}


/* ---- FCN_M(tgMH_Set_Euler_X) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Set_Euler_X)( MAT_T(PC) TgANALYSIS_NO_NULL pmOUT_0, VAR_T(C) fARG_1 )
{
    MAT_UN_PTR_T()                      uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    FCN_M(tgMH_Set_Euler_X_S)( VEC_S_UN_PTR_M_MEMBER(uM0), fARG_1 );
}


/* ---- FCN_M(tgMH_Set_Euler_Y) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Set_Euler_Y)( MAT_T(PC) TgANALYSIS_NO_NULL pmOUT_0, VAR_T(C) fARG_1 )
{
    MAT_UN_PTR_T()                      uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    FCN_M(tgMH_Set_Euler_Y_S)( VEC_S_UN_PTR_M_MEMBER(uM0), fARG_1 );
}


/* ---- FCN_M(tgMH_Set_Euler_Z) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Set_Euler_Z)( MAT_T(PC) TgANALYSIS_NO_NULL pmOUT_0, VAR_T(C) fARG_1 )
{
    MAT_UN_PTR_T()                      uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    FCN_M(tgMH_Set_Euler_Z_S)( VEC_S_UN_PTR_M_MEMBER(uM0), fARG_1 );
}


/* ---- FCN_M(tgMH_Set_Quat) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_Set_Quat)( MAT_T(PC) TgANALYSIS_NO_NULL pmOUT_0, VEC_T(1,C) vARG_1 )
{
    MAT_UN_PTR_T()                      uM0;
    VEC_UN_T(1)                         uV0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmOUT_0;
    VEC_UN_1_MEMBER(uV0) = vARG_1;
    FCN_M(tgMH_Set_Quat_S)( VEC_S_UN_PTR_M_MEMBER(uM0), VEC_S_UN_1_MEMBER(uV0) );
}


/* ---- FCN_M(tgMH_ADD) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_ADD)( MAT_T(PC) pmOUT_0, MAT_T(CPC) pmARG_1, MAT_T(CPC) TgANALYSIS_NO_NULL pmARG_2 )
{
    #define EQN(A) FCN_V(tgMH_ADD)( pmARG_1->m_avCol[A], pmARG_2->m_avCol[A] )
    GENERATE__MAT_ASSIGN
    #undef EQN
}


/* ---- FCN_M(tgMH_MUL) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_MUL)( MAT_T(PC) pmOUT_0, MAT_T(CPC) pmARG_1, MAT_T(CPC) TgANALYSIS_NO_NULL pmARG_2 )
{
    #define EQN(A) FCN_V(tgMH_MUL)( pmARG_1->m_avCol[A], pmARG_2->m_avCol[A] )
    GENERATE__MAT_ASSIGN
    #undef EQN
}


/* ---- FCN_M(tgMH_DIV) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_DIV)( MAT_T(PC) pmOUT_0, MAT_T(CPC) pmARG_1, MAT_T(CPC) TgANALYSIS_NO_NULL pmARG_2 )
{
    #define EQN(A) FCN_V(tgMH_DIV)( pmARG_1->m_avCol[A], pmARG_2->m_avCol[A] )
    GENERATE__MAT_ASSIGN
    #undef EQN
}


/* ---- FCN_M(tgMH_SUB) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_SUB)( MAT_T(PC) pmOUT_0, MAT_T(CPC) pmARG_1, MAT_T(CPC) TgANALYSIS_NO_NULL pmARG_2 )
{
    #define EQN(A) FCN_V(tgMH_SUB)( pmARG_1->m_avCol[A], pmARG_2->m_avCol[A] )
    GENERATE__MAT_ASSIGN
    #undef EQN
}


/* ---- FCN_M(tgMH_NEG) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_M(tgMH_NEG)( MAT_T(PC) pmOUT_0, MAT_T(CPC) pmARG_1 )
{
    #define EQN(A) FCN_V(tgMH_NEG)( pmARG_1->m_avCol[A] )
    GENERATE__MAT_ASSIGN
    #undef EQN
}


/* ---- FCN_M(tgMH_NAN) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_M(tgMH_NAN)( MAT_T(CPC) pmARG_0 )
{
    MAT_UN_CONST_PTR_T()                uM0;

    VEC_UN_PTR_M_MEMBER(uM0) = pmARG_0;
    return (FCN_M(tgMH_NAN_S)( VEC_S_UN_PTR_M_MEMBER(uM0) ));
}


/* =============================================================================================================================================================================== */
#endif
