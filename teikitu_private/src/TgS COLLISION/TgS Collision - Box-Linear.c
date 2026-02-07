/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box-Linear.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined (ENABLE_RELOAD_GUARD_LINEAR)
    #define ENABLE_RELOAD_GUARD_LINEAR

    #define LN_CAP_0 0
    #define LN_CAP_1 0
        #define VI(A) FCN_VO(A##00)
        #include __FILE__
        #undef VI
    #undef LN_CAP_0
    #undef LN_CAP_1

    #define LN_CAP_0 1
    #define LN_CAP_1 0
        #define VI(A) FCN_VO(A##10)
        #include __FILE__
        #undef VI
    #undef LN_CAP_0
    #undef LN_CAP_1

    #define LN_CAP_0 1
    #define LN_CAP_1 1
        #define VI(A) FCN_VO(A##11)
        #include __FILE__
        #undef VI
    #undef LN_CAP_0
    #undef LN_CAP_1

    #undef ENABLE_RELOAD_GUARD_LINEAR

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#else

#if !defined (ENABLE_RELOAD_GUARD)
    #define TEMPLATE__VECTOR_DIM 4
    #define ENABLE_RELOAD_GUARD
    #if !defined(TEMPLATE__TYPE_SIZE)
        #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
            #define TEMPLATE__TYPE_SIZE 64
            #include __FILE__
            #undef TEMPLATE__TYPE_SIZE
        #endif
        #define TEMPLATE__TYPE_SIZE 32
    #endif
    #undef ENABLE_RELOAD_GUARD
#endif

#define TEMPLATE__VECTOR_COL 3
#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

//static VAR_T()
//VI(tgCO_BX_Box_DoF3_LR)(
//    VEC_T(1,P), VEC_T(1,C), VEC_T(1,C), VEC_OBJ_T(TgBOX,CPC) );
//
//static VAR_T()
//VI(tgCO_BX_Box_DoF2_LR)(
//    VEC_T(1,P), VEC_T(1,C), VEC_T(1,C), TgSINT_E32_C , TgSINT_E32_C , TgSINT_E32_C , VEC_OBJ_T(TgBOX,CPC) );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- VI(tgCO_BX_ClosestSq_PM_LR) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) VI(tgCO_BX_ClosestSq_PM_LR)( TgATTRIBUTE_UNUSED VEC_T(1,PC) pvBX0, TgATTRIBUTE_UNUSED VEC_T(1,PC) pvBX1, TgATTRIBUTE_UNUSED VEC_T(1,PC) pvBX2,
                                      TgATTRIBUTE_UNUSED VEC_T(1,PC) pvLN0, TgATTRIBUTE_UNUSED VEC_OBJ_T(TgBOX,CPC) psBX0, TgATTRIBUTE_UNUSED VEC_T(1,C) vS0,
                                      TgATTRIBUTE_UNUSED VEC_T(1,C) vD0 )
{
#if (defined(LN_CAP_0) && LN_CAP_0) || (defined(LN_CAP_1) && LN_CAP_1)
    return (FCN_V(tgMH_SET1)(0));
#else
    return (FCN_V(tgMH_SET1)(0));
#endif
    //VEC_T(3)                            mBX0_UX;
    //VEC_T(1)                            vBX0_OG;
    //TgSINT_E32                          iIndex;
    ////VEC_T(1)                            vDS, vDN, vD1_X0, vD1_X1, vD1_X2, vDS_X0, vDS_X1, vDS_X2;

    ///* Compute coordinates of line in box coordinate system */

    //FCN_V(tgMH_Init_Basis_And_Origin,3)( &mBX0_UX, &vBX0_OG, &psBX0->m_mReference_Frame );

    //{
    //    VEC_T(1,C)                          vD0__BX0 = FCN_V(tgMH_TX,3)( vD0, &mBX0_UX );
    //    VEC_T(1,C)                          vDS0 = FCN_V(tgMH_SUB)( vS0, vBX0_OG );
    //    VEC_T(1,C)                          vDS__BX0 = FCN_V(tgMH_TX,3)( vDS0, &mBX0_UX );
    //    VEC_T(1,C)                          vSGN_D0__BX0 = FCN_V(tgMH_SGN)( vD0__BX0 );
    //    VEC_T(1,C)                          vDS = FCN_V(tgMH_MUL)( vSGN_D0__BX0, vDS__BX0 );
    //    VEC_T(1,C)                          vDN = FCN_V(tgMH_ABS)( vD0__BX0 );
    //    VAR_T()                             fDistSq = TYPE_K(0,0);

    //    /* Calculate the distance and place of closest contact. */

    //    iIndex  = FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_SPX)( vD0 ) ) ? 0 : 1;
    //    iIndex += FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_SPY)( vD0 ) ) ? 0 : 2;
    //    iIndex += FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_SPZ)( vD0 ) ) ? 0 : 4;
    //    switch (iIndex)
    //    {
    //        case 7:
    //        { /* (+,+,+) */

    //            fDistSq += VI(tgCO_BX_Box_DoF3_LR)( pvLN0, vDS, vDN, psBX0 );
    //            *pvBX0 = FCN_V(tgMH_MUL)( vSGN_D0__BX0, vDS );
    //            break;
    //        }

    //        case 6:
    //        { /* (+,+,0) */

    //            fDistSq += VI(tgCO_BX_Box_DoF2_LR)( pvLN0, vDS, vDN, 0, 1, 2, psBX0 );

    //            {
    //                VAR_T(C)                            fT2 = FCN_F(tgPM_ABS)(vDS.z) - psBX0->m_vExtent.z;
    //                VAR_T(C)                            fK0 = FCN_F(tgPM_COPY_SIGN)(psBX0->m_vExtent.z, vDS.z);
    //                VAR_T(C)                            fZ = FCN_F(tgPM_FSEL)(fT2, fK0, vDS.z);

    //                fDistSq += FCN_F(tgPM_FSEL)(fT2, fT2*fT2, TYPE_K(0));

    //                *pfB0 = FCN_F(tgPM_FSEL)(fD1_X0, vDS.x, -vDS.x);
    //                *pfB1 = FCN_F(tgPM_FSEL)(fD1_X1, vDS.y, -vDS.y);
    //                *pfB2 = FCN_F(tgPM_FSEL)(fD1_X2, fZ, -fZ);
    //            }

    //            break;
    //        }

    //        case 5:
    //        { /* (+,0,+) */

    //            fDistSq += VI(tgCO_BX_Box_DoF2_LR)( pvLN0, vDS, vDN, 0, 2, 1, psBX0 );

    //            {
    //                VAR_T(C)                            fT1 = FCN_F(tgPM_ABS)(vDS.y) - psBX0->m_vExtent.y;
    //                VAR_T(C)                            fK0 = FCN_F(tgPM_COPY_SIGN)(psBX0->m_vExtent.y, vDS.y);
    //                VAR_T(C)                            fY = FCN_F(tgPM_FSEL)(fT1, fK0, vDS.y);

    //                fDistSq += FCN_F(tgPM_FSEL)(fT1, fT1*fT1, TYPE_K(0));

    //                *pfB0 = FCN_F(tgPM_FSEL)(fD1_X0, vDS.x, -vDS.x);
    //                *pfB1 = FCN_F(tgPM_FSEL)(fD1_X1, fY, -fY);
    //                *pfB2 = FCN_F(tgPM_FSEL)(fD1_X2, vDS.z, -vDS.z);
    //            }

    //            break;
    //        }

    //        case 3:
    //        { /* (0,+,+) */

    //            fDistSq += VI(tgCO_BX_Box_DoF2_LR)( pvLN0, vDS, vDN, 1, 2, 0, psBX0 );

    //            {
    //                VAR_T(C)                            fT0 = FCN_F(tgPM_ABS)(vDS.x) - psBX0->m_vExtent.x;
    //                VAR_T(C)                            fK0 = FCN_F(tgPM_COPY_SIGN)(psBX0->m_vExtent.x, vDS.x);
    //                VAR_T(C)                            fX = FCN_F(tgPM_FSEL)(fT0, fK0, vDS.x);

    //                fDistSq += FCN_F(tgPM_FSEL)(fT0, fT0*fT0, TYPE_K(0));

    //                *pfB0 = FCN_F(tgPM_FSEL)(fD1_X0, fX, -fX);
    //                *pfB1 = FCN_F(tgPM_FSEL)(fD1_X1, vDS.y, -vDS.y);
    //                *pfB2 = FCN_F(tgPM_FSEL)(fD1_X2, vDS.z, -vDS.z);
    //            }

    //            break;
    //        }

    //        case 4:
    //        { /* (+,0,0) */

    //            VAR_T(C)                            fT1 = FCN_F(tgPM_ABS)(vDS.y) - psBX0->m_vExtent.y;
    //            VAR_T(C)                            fT2 = FCN_F(tgPM_ABS)(vDS.z) - psBX0->m_vExtent.z;
    //            VAR_T(C)                            fK0 = FCN_F(tgPM_COPY_SIGN)(psBX0->m_vExtent.y, vDS.y);
    //            VAR_T(C)                            fY = FCN_F(tgPM_FSEL)(fT1, fK0, vDS.y);
    //            VAR_T(C)                            fK1 = FCN_F(tgPM_COPY_SIGN)(psBX0->m_vExtent.z, vDS.z);
    //            VAR_T(C)                            fZ = FCN_F(tgPM_FSEL)(fT2, fK1, vDS.z);

    //            fDistSq += FCN_F(tgPM_FSEL)(fT1, fT1*fT1, TYPE_K(0)) + FCN_F(tgPM_FSEL)(fT2, fT2*fT2, TYPE_K(0));

    //            *pfB0 = TYPE_K(0);
    //            *pfB1 = FCN_F(tgPM_FSEL)(fD1_X1, fY, -fY);
    //            *pfB2 = FCN_F(tgPM_FSEL)(fD1_X2, fZ, -fZ);
    //            *pfLN0 = -(vDS.x / vDN.x);

    //            break;
    //        }

    //        case 2:
    //        { /* (0,+,0) */

    //            VAR_T(C)                            fT0 = FCN_F(tgPM_ABS)(vDS.x) - psBX0->m_vExtent.x;
    //            VAR_T(C)                            fT2 = FCN_F(tgPM_ABS)(vDS.z) - psBX0->m_vExtent.z;
    //            VAR_T(C)                            fK0 = FCN_F(tgPM_COPY_SIGN)(psBX0->m_vExtent.x, vDS.x);
    //            VAR_T(C)                            fX = FCN_F(tgPM_FSEL)(fT0, fK0, vDS.x);
    //            VAR_T(C)                            fK1 = FCN_F(tgPM_COPY_SIGN)(psBX0->m_vExtent.z, vDS.z);
    //            VAR_T(C)                            fZ = FCN_F(tgPM_FSEL)(fT2, fK1, vDS.z);

    //            fDistSq += FCN_F(tgPM_FSEL)(fT0, fT0*fT0, TYPE_K(0)) + FCN_F(tgPM_FSEL)(fT2, fT2*fT2, TYPE_K(0));

    //            *pfB0 = FCN_F(tgPM_FSEL)(fD1_X0, fX, -fX);
    //            *pfB1 = TYPE_K(0);
    //            *pfB2 = FCN_F(tgPM_FSEL)(fD1_X2, fZ, -fZ);
    //            *pfLN0 = -(vDS.y / vDN.y);

    //            break;
    //        }

    //        case 1:
    //        { /* (0,0,+) */

    //            VAR_T(C)                            fT0 = FCN_F(tgPM_ABS)(vDS.x) - psBX0->m_vExtent.x;
    //            VAR_T(C)                            fT1 = FCN_F(tgPM_ABS)(vDS.y) - psBX0->m_vExtent.y;
    //            VAR_T(C)                            fK0 = FCN_F(tgPM_COPY_SIGN)(psBX0->m_vExtent.x, vDS.x);
    //            VAR_T(C)                            fX = FCN_F(tgPM_FSEL)(fT0, fK0, vDS.x);
    //            VAR_T(C)                            fK1 = FCN_F(tgPM_COPY_SIGN)(psBX0->m_vExtent.y, vDS.y);
    //            VAR_T(C)                            fY = FCN_F(tgPM_FSEL)(fT1, fK1, vDS.y);

    //            fDistSq += FCN_F(tgPM_FSEL)(fT0, fT0*fT0, TYPE_K(0)) + FCN_F(tgPM_FSEL)(fT1, fT1*fT1, TYPE_K(0));

    //            *pfB0 = FCN_F(tgPM_FSEL)(fD1_X0, fX, -fX);
    //            *pfB1 = FCN_F(tgPM_FSEL)(fD1_X1, fY, -fY);
    //            *pfB2 = TYPE_K(0);
    //            *pfLN0 = -(vDS.z / vDN.z);

    //            break;
    //        }

    //        case 0:
    //        { /* (0,0,0) */
    //            VAR_T(C)                            fT0 = FCN_F(tgPM_ABS)(vDS.x) - psBX0->m_vExtent.x;
    //            VAR_T(C)                            fT1 = FCN_F(tgPM_ABS)(vDS.y) - psBX0->m_vExtent.y;
    //            VAR_T(C)                            fT2 = FCN_F(tgPM_ABS)(vDS.z) - psBX0->m_vExtent.z;
    //            VAR_T(C)                            fK0 = FCN_F(tgPM_COPY_SIGN)(psBX0->m_vExtent.x, vDS.x);
    //            VAR_T(C)                            fX = FCN_F(tgPM_FSEL)(fT0, fK0, vDS.x);
    //            VAR_T(C)                            fK1 = FCN_F(tgPM_COPY_SIGN)(psBX0->m_vExtent.y, vDS.y);
    //            VAR_T(C)                            fY = FCN_F(tgPM_FSEL)(fT1, fK1, vDS.y);
    //            VAR_T(C)                            fK2 = FCN_F(tgPM_COPY_SIGN)(psBX0->m_vExtent.z, vDS.z);
    //            VAR_T(C)                            fZ = FCN_F(tgPM_FSEL)(fT2, fK2, vDS.z);

    //            fDistSq += FCN_F(tgPM_FSEL)(fT0, fT0*fT0, TYPE_K(0)) + FCN_F(tgPM_FSEL)(fT1, fT1*fT1, TYPE_K(0)) + FCN_F(tgPM_FSEL)(fT2, fT2*fT2, TYPE_K(0));

    //            *pfB0 = FCN_F(tgPM_FSEL)(fD1_X0, fX, -fX);
    //            *pfB1 = FCN_F(tgPM_FSEL)(fD1_X1, fY, -fY);
    //            *pfB2 = FCN_F(tgPM_FSEL)(fD1_X2, fZ, -fZ);
    //            *pfLN0 = TYPE_K(0);

    //            break;
    //        }
    //    };

    //    if (LN_CAP_0 && *pfLN0 < TYPE_K(0))
    //    {
    //        *pfLN0 = TYPE_K(0);
    //        return (FCN_VO(tgCO_BX_ClosestSq_PM_PT)(pfB0, pfB1, pfB2, psBX0, pvS0));
    //    };

    //    if (LN_CAP_1 && *pfLN0 > TYPE_K(1))
    //    {
    //        VEC_T(1,C)      vK0 = FCN_V(tgMH_ADD)(pvS0, vD0);

    //        *pfLN0 = TYPE_K(1);
    //        return (FCN_VO(tgCO_BX_ClosestSq_PM_PT)(pfB0, pfB1, pfB2, psBX0, vK0 ));
    //    };

    //    return (fDistSq);
    //};
}


/* ---- VI(tgCO_BX_Clip_PM_LR) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  tgBX0: Box primitive                                                                                                                                                    */
/* Input:  vS0,vD0: Origin and Direction for the Linear                                                                                                                            */
/* Output: fLN0,fLN1: Parametric parameter to generate the two points of the linear contained inside the clip space.                                                               */
/* Return: Result Code.                                                                                                                                                            */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT VI(tgCO_BX_Clip_PM_LR)( TgATTRIBUTE_UNUSED VEC_T(1,P) pfLN0, TgATTRIBUTE_UNUSED VEC_T(1,P) pfLN1, TgATTRIBUTE_UNUSED VEC_OBJ_T(TgBOX,CPC) psBX0,
                                 TgATTRIBUTE_UNUSED VEC_T(1,C) vS0, TgATTRIBUTE_UNUSED VEC_T(1,C) vD0 )
{
    return (KTgE_FAIL);
    //VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)(pvS0, &psBX0->m_vOrigin);
    //VAR_T()                             fDS_N, fD1_N;
    //VAR_T()                             fMin = -VAR_K(KTgMAX);
    //VAR_T()                             fMax = VAR_K(KTgMAX);

    ///* Quick out - Does the linear exist outside of the clip region. */

    //TgPARAM_CHECK( FCN_VO(tgGM_BX_Is_Valid)(psBX0) );

    //fDS_N = FCN_V(tgMH_DOT)(psBX0->m_avAxis + 0, vDS );
    //fD1_N = FCN_V(tgMH_DOT)(psBX0->m_avAxis + 0, vD0);

    //if (LN_CAP_0 && fDS_N < -psBX0->m_vExtent.x)
    //{
    //    if (fD1_N < TYPE_K(0) || (LN_CAP_1 && (fDS_N + fD1_N < -psBX0->m_vExtent.x)))
    //    {
    //        return (KTgE_NO_INTERSECT);
    //    };
    //}
    //else if (LN_CAP_0 && fDS_N > psBX0->m_vExtent.x)
    //{
    //    if (fD1_N > TYPE_K(0) || (LN_CAP_1 && (fDS_N + fD1_N > psBX0->m_vExtent.x)))
    //    {
    //        return (KTgE_NO_INTERSECT);
    //    };
    //};

    ///* Find the non-capped intersections of this linear with the two enclosing planes. */

    //if (fD1_N < -VAR_K(KTgEPS))
    //{
    //    fMin = FCN_F(tgPM_FSEL)(fDS_N + fD1_N*fMin - psBX0->m_vExtent.x, (psBX0->m_vExtent.x - fDS_N) / fD1_N, fMin);
    //    fMax = FCN_F(tgPM_FSEL)(fDS_N + fD1_N*fMax + psBX0->m_vExtent.x, fMax, -(psBX0->m_vExtent.x + fDS_N) / fD1_N);
    //}
    //else if (fD1_N > VAR_K(KTgEPS))
    //{
    //    fMin = FCN_F(tgPM_FSEL)(fDS_N + fD1_N*fMin + psBX0->m_vExtent.x, fMin, -(psBX0->m_vExtent.x + fDS_N) / fD1_N);
    //    fMax = FCN_F(tgPM_FSEL)(fDS_N + fD1_N*fMax - psBX0->m_vExtent.x, (psBX0->m_vExtent.x - fDS_N) / fD1_N, fMax);
    //};

    ///* Quick out - Does the linear exist outside of the clip region. */

    //fDS_N = FCN_V(tgMH_DOT)(psBX0->m_avAxis + 1, vDS );
    //fD1_N = FCN_V(tgMH_DOT)(psBX0->m_avAxis + 1, vD0);

    //if (LN_CAP_0 && fDS_N < -psBX0->m_vExtent.y)
    //{
    //    if (fD1_N < TYPE_K(0) || (LN_CAP_1 && (fDS_N + fD1_N < -psBX0->m_vExtent.y)))
    //    {
    //        return (KTgE_NO_INTERSECT);
    //    };
    //}
    //else if (LN_CAP_0 && fDS_N > psBX0->m_vExtent.y)
    //{
    //    if (fD1_N > TYPE_K(0) || (LN_CAP_1 && (fDS_N + fD1_N > psBX0->m_vExtent.y)))
    //    {
    //        return (KTgE_NO_INTERSECT);
    //    };
    //};

    ///* Find the non-capped intersections of this linear with the two enclosing planes. */

    //if (fD1_N < -VAR_K(KTgEPS))
    //{
    //    fMin = FCN_F(tgPM_FSEL)(fDS_N + fD1_N*fMin - psBX0->m_vExtent.y, (psBX0->m_vExtent.y - fDS_N) / fD1_N, fMin);
    //    fMax = FCN_F(tgPM_FSEL)(fDS_N + fD1_N*fMax + psBX0->m_vExtent.y, fMax, -(psBX0->m_vExtent.y + fDS_N) / fD1_N);
    //}
    //else if (fD1_N > VAR_K(KTgEPS))
    //{
    //    fMin = FCN_F(tgPM_FSEL)(fDS_N + fD1_N*fMin + psBX0->m_vExtent.y, fMin, -(psBX0->m_vExtent.y + fDS_N) / fD1_N);
    //    fMax = FCN_F(tgPM_FSEL)(fDS_N + fD1_N*fMax - psBX0->m_vExtent.y, (psBX0->m_vExtent.y - fDS_N) / fD1_N, fMax);
    //};

    ///* Quick out - Does the linear exist outside of the clip region. */

    //fDS_N = FCN_V(tgMH_DOT)(psBX0->m_avAxis + 2, vDS );
    //fD1_N = FCN_V(tgMH_DOT)(psBX0->m_avAxis + 2, vD0);

    //if (LN_CAP_0 && fDS_N < -psBX0->m_vExtent.z)
    //{
    //    if (fD1_N < TYPE_K(0) || (LN_CAP_1 && (fDS_N + fD1_N < -psBX0->m_vExtent.z)))
    //    {
    //        return (KTgE_NO_INTERSECT);
    //    };
    //}
    //else if (LN_CAP_0 && fDS_N > psBX0->m_vExtent.z)
    //{
    //    if (fD1_N > TYPE_K(0) || (LN_CAP_1 && (fDS_N + fD1_N > psBX0->m_vExtent.z)))
    //    {
    //        return (KTgE_NO_INTERSECT);
    //    };
    //};

    ///* Find the non-capped intersections of this linear with the two enclosing planes. */

    //if (fD1_N < -VAR_K(KTgEPS))
    //{
    //    fMin = FCN_F(tgPM_FSEL)(fDS_N + fMin*fD1_N - psBX0->m_vExtent.z, (psBX0->m_vExtent.z - fDS_N) / fD1_N, fMin);
    //    fMax = FCN_F(tgPM_FSEL)(fDS_N + fMax*fD1_N + psBX0->m_vExtent.z, fMax, -(psBX0->m_vExtent.z + fDS_N) / fD1_N);
    //}
    //else if (fD1_N > VAR_K(KTgEPS))
    //{
    //    fMin = FCN_F(tgPM_FSEL)(fDS_N + fMin*fD1_N + psBX0->m_vExtent.z, fMin, -(psBX0->m_vExtent.z + fDS_N) / fD1_N);
    //    fMax = FCN_F(tgPM_FSEL)(fDS_N + fMax*fD1_N - psBX0->m_vExtent.z, (psBX0->m_vExtent.z - fDS_N) / fD1_N, fMax);
    //};

    ///* Return the results - capped to the linear legal region. */

    //if (fMin > fMax || fMin <= -VAR_K(KTgMAX) || fMax >= VAR_K(KTgMAX))
    //{
    //    return (KTgE_FAIL);
    //};

    //if (LN_CAP_0)
    //{
    //    *pfLN0 = FCN_F(tgPM_FSEL)(*pfLN0, *pfLN0, TYPE_K(0));
    //    *pfLN1 = FCN_F(tgPM_FSEL)(*pfLN1, *pfLN1, TYPE_K(0));
    //};

    //if (LN_CAP_1)
    //{
    //    *pfLN0 = FCN_F(tgPM_FSEL)(*pfLN0 - TYPE_K(1), *pfLN0, TYPE_K(1));
    //    *pfLN1 = FCN_F(tgPM_FSEL)(*pfLN1 - TYPE_K(1), *pfLN1, TYPE_K(1));
    //};

    //return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- VI(tgCO_BX_Box_DoF3_LR) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/*  -- Internal Function -- (Helper to create contact points the box and linear - three degrees of freedom)                                                                        */
/* Input:  vDS: The difference vector between the origin of the two primitives (absolute value)                                                                                    */
/* Input:  vD0: Direction of the Linear                                                                                                                                            */
/* Input:  tgBX0: Box primitive                                                                                                                                                    */
/* Output: fLN0: Parametric parameter to generate the point of proximity on the linear                                                                                             */
/* Output: vDS: The difference vector between the two points of closest proximity                                                                                                  */
/* Return: Result Code                                                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//VAR_T() VI(tgCO_BX_Box_DoF3_LR)( VAR_T(P) pfLN0, VEC_T(1,PC) pvDS, VEC_T(1,C) vD0, VEC_OBJ_T(TgBOX,CPC) psBX0 )
//{
//    VEC_T(1,C)                          vD1_D1, vD1_MN, vD1_MX, vMN_MN, vMX_MX;
//    VEC_T(1,C)                          vMN = FCN_V(tgMH_SUB)(pvDS, &psBX0->m_vExtent);
//    VEC_T(1,C)                          vMX = FCN_V(tgMH_ADD)(pvDS, &psBX0->m_vExtent);
//    VEC_T(1,C)                          vD1xMN = FCN_V(tgMH_CX)(vD0, vMN );
//    VAR_T(C)        fD1_D1 = FCN_V(tgMH_LSQ)(vD0);
//    TgUINT_E32                          i0, i1, i2;
//
//    vD1_D1 = FCN_V(tgMH_MUL)(vD0, vD0);
//    vD1_MN = FCN_V(tgMH_MUL)(vD0, vMN );
//    vD1_MX = FCN_V(tgMH_MUL)(vD0, vMX );
//    vMN_MN = FCN_V(tgMH_MUL)( vMN, vMN );
//    vMX_MX = FCN_V(tgMH_MUL)( vMX, vMX );
//
//    if (vD1xMN.z >= TYPE_K(0))
//    {
//        i0 = vD1xMN.x >= TYPE_K(0) ? 2 : 1;
//        i1 = vD1xMN.x >= TYPE_K(0) ? 0 : 2;
//        i2 = vD1xMN.x >= TYPE_K(0) ? 1 : 0;
//    }
//    else
//    {
//        i0 = vD1xMN.y >= TYPE_K(0) ? 0 : 2;
//        i1 = vD1xMN.y >= TYPE_K(0) ? 1 : 0;
//        i2 = vD1xMN.y >= TYPE_K(0) ? 2 : 1;
//    }
//
//    pvDS->m_aData[i0] = psBX0->m_vExtent.m_aData[i0];
//
//    if (vD0->m_aData[i0] * vMX.m_aData[i2] >= vD0->m_aData[i2] * vMN.m_aData[i0] &&
//        vD0->m_aData[i0] * vMX.m_aData[i1] >= vD0->m_aData[i1] * vMN.m_aData[i0])
//    {
//        VAR_T(C)        fINV = TYPE_K(1) / vD0->m_aData[i0];
//
//        pvDS->m_aData[i1] -= vD0->m_aData[i1] * vMN.m_aData[i0] * fINV;
//        pvDS->m_aData[i2] -= vD0->m_aData[i2] * vMN.m_aData[i0] * fINV;
//
//        *pfLN0 = -vMN.m_aData[i0] * fINV;
//
//        return (TYPE_K(0));
//    }
//    else
//    {
//        VAR_T(C)        fK1 = vD1_MN.m_aData[i0] + vD1_MX.m_aData[i2];
//        VAR_T(C)        fK2 = vD1_D1.m_aData[i0] + vD1_D1.m_aData[i2];
//        VAR_T(C)        fK0 = vMX.m_aData[i1] - vD0->m_aData[i1] * (fK1 / fK2);
//
//        if (vD0->m_aData[i0] * vMX.m_aData[i1] >= vD0->m_aData[i1] * vMN.m_aData[i0] ||
//            (fK0 >= TYPE_K(0) && vD0->m_aData[i0] * vMX.m_aData[i2] < vD0->m_aData[i2] * vMN.m_aData[i0]))
//        {
//            VAR_T(C)        fLength = TYPE_K(2,0)*psBX0->m_vExtent.m_aData[i1];
//            VAR_T(C)        fT = FCN_F(tgPM_FSEL)(fLength - fK0, FCN_F(tgPM_FSEL)(fK0, fK0, TYPE_K(0)), fLength);
//            VAR_T(C)        fTB = vMX.m_aData[i1] - fT;
//            VAR_T(C)        fDT = vD1_MN.m_aData[i0] + vD1_MX.m_aData[i2] + vD0->m_aData[i1] * fTB;
//            VAR_T(C)        fPM = -fDT / fD1_D1;
//
//            pvDS->m_aData[i1] = -psBX0->m_vExtent.m_aData[i1] + fT;
//            pvDS->m_aData[i2] = -psBX0->m_vExtent.m_aData[i2];
//            *pfLN0 = fPM;
//
//            return (vMN_MN.m_aData[i0] + vMX_MX.m_aData[i2] + fDT*fPM + fTB*fTB);
//        }
//        else
//        {
//            VAR_T(C)        fK4 = vD1_D1.m_aData[i0] + vD1_D1.m_aData[i1];
//            VAR_T(C)        fK5 = vD1_MN.m_aData[i0] + vD1_MX.m_aData[i1];
//            VAR_T(C)        fK3 = vMX.m_aData[i2] - vD0->m_aData[i2] * (fK5 / fK4);
//
//            VAR_T(C)        fLength = TYPE_K(2,0)*psBX0->m_vExtent.m_aData[i2];
//            VAR_T(C)        fT = FCN_F(tgPM_FSEL)(fLength - fK3, FCN_F(tgPM_FSEL)(fK3, fK3, TYPE_K(0)), fLength);
//            VAR_T(C)        fTB = vMX.m_aData[i2] - fT;
//            VAR_T(C)        fDT = vD1_MN.m_aData[i0] + vD1_MX.m_aData[i1] + vD0->m_aData[i2] * fTB;
//            VAR_T(C)        fPM = -fDT / fD1_D1;
//
//            pvDS->m_aData[i1] = -psBX0->m_vExtent.m_aData[i1];
//            pvDS->m_aData[i2] = -psBX0->m_vExtent.m_aData[i2] + fT;
//            *pfLN0 = fPM;
//
//            return (vMN_MN.m_aData[i0] + vMX_MX.m_aData[i1] + fDT*fPM + fTB*fTB);
//        };
//    };
//}


/* ---- VI(tgCO_BX_Box_DoF2_LR) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/*  -- Internal Function -- (Helper to create contact points the box and linear - two degrees of freedom)                                                                          */
/* Input:  vDS: The difference vector between the origin of the two primitives                                                                                                     */
/* Input:  vD0: Direction of the Linear                                                                                                                                            */
/* Input:  i0,i1,i2: Used to give the face order for the test                                                                                                                      */
/* Input:  tgBX0: Box primitive                                                                                                                                                    */
/* Output: tyLN0: Parametric parameter to generate the point of proximity on the linear                                                                                            */
/* Output: vDS: The difference vector between the two points of closest proximity                                                                                                  */
/* Return: Result Code                                                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//VAR_T() VI(tgCO_BX_Box_DoF2_LR)( VAR_T(P) pfLN0, VEC_T(1,PC) pvDS, VEC_T(1,C) vD0, TgSINT_E32_C i0, TgSINT_E32_C i1, TgATTRIBUTE_UNUSED TgSINT_E32_C i2, VEC_OBJ_T(TgBOX,CPC) psBX0 )
//{
//    /* Construct the direction vector from the box corner at the positive extents to the line origin. */
//
//    VAR_T(C)        fMinDT0 = pvDS->m_aData[i0] - psBX0->m_vExtent.m_aData[i0];
//    VAR_T(C)        fMinDT1 = pvDS->m_aData[i1] - psBX0->m_vExtent.m_aData[i1];
//    VAR_T(C)        fMinDT1_DN0 = vD0->m_aData[i0] * fMinDT1;
//    VAR_T(C)        fMinDT0_DN1 = vD0->m_aData[i1] * fMinDT0;
//
//    VEC_T(1,C)        vD1_D1;
//
//    vD1_D1 = FCN_V(tgMH_MUL)(vD0, vD0);
//
//    /*VAR_T(C)        fD1_D1 = FCN_V(tgMH_LSQ)( vD0 ); */
//
//    if (fMinDT0_DN1 >= fMinDT1_DN0)
//    {
//        VAR_T(C)        fMaxDT1 = pvDS->m_aData[i1] + psBX0->m_vExtent.m_aData[i1];
//        VAR_T(C)        fDT = fMinDT0_DN1 - vD0->m_aData[i0] * fMaxDT1;
//
//        pvDS->m_aData[i0] = psBX0->m_vExtent.m_aData[i0];
//
//        if (fDT >= TYPE_K(0)) /* Line is outside of the box. */
//        {
//            VAR_T(C)        fK0 = TYPE_K(1) / (vD1_D1.m_aData[i0] + vD1_D1.m_aData[i1]);
//
//            pvDS->m_aData[i1] = -psBX0->m_vExtent.m_aData[i1];
//            *pfLN0 = -(vD0->m_aData[i0] * fMinDT0 + vD0->m_aData[i1] * fMaxDT1)*fK0;
//
//            return (fDT*fDT*fK0);
//        }
//        else /* Line intersects the box. */
//        {
//            VAR_T(C)        fK0 = TYPE_K(1) / vD0->m_aData[i0];
//
//            pvDS->m_aData[i1] -= fMinDT0_DN1*fK0;
//            *pfLN0 = -fMinDT0*fK0;
//
//            return (TYPE_K(0));
//        }
//    }
//    else
//    {
//        VAR_T(C)        fMaxDT0 = pvDS->m_aData[i0] + psBX0->m_vExtent.m_aData[i0];
//        VAR_T(C)        fDT = fMinDT1_DN0 - vD0->m_aData[i1] * fMaxDT0;
//
//        pvDS->m_aData[i1] = psBX0->m_vExtent.m_aData[i1];
//
//        if (fDT >= TYPE_K(0)) /* Line is outside of the box. */
//        {
//            VAR_T(C)        fK0 = TYPE_K(1) / (vD1_D1.m_aData[i0] + vD1_D1.m_aData[i1]);
//
//            pvDS->m_aData[i0] = -psBX0->m_vExtent.m_aData[i0];
//            *pfLN0 = -(vD0->m_aData[i0] * fMaxDT0 + vD0->m_aData[i1] * fMinDT1)*fK0;
//
//            return (fDT*fDT*fK0);
//        }
//        else /* Line intersects the box. */
//        {
//            VAR_T(C)        fK0 = TYPE_K(1) / vD0->m_aData[i1];
//
//            pvDS->m_aData[i0] -= fMinDT1_DN0*fK0;
//            *pfLN0 = -fMinDT1*fK0;
//
//            return (TYPE_K(0));
//        }
//    }
//}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#endif
