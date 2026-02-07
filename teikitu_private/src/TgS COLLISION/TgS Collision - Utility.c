/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Utility.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCN_V(tgMH_Internal_Intersect) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE FCN_VO(tgCO_LN_Internal_Intersect_LN)( VEC_T(1,PC) pvRN0, VEC_T(1,PC) pvRN1, VEC_T(1,C) vS0, VEC_T(1,C) vD0, VEC_T(1,C) vS1, VEC_T(1,C) vD1 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS1, vS0 );

    VEC_T(1,C)                          vD0_D0 = FCN_V(tgMH_LSQ)( vD0 );
    VEC_T(1,C)                          vD1_D1 = FCN_V(tgMH_LSQ)( vD1 );
    VEC_T(1,C)                          vD0_D1 = FCN_V(tgMH_DOT)( vD0, vD1 );
    VEC_T(1,C)                          vDS_D0 = FCN_V(tgMH_DOT)( vDS, vD0 );
    VEC_T(1,C)                          vDS_D1 = FCN_V(tgMH_NEG)( FCN_V(tgMH_DOT)( vDS, vD1 ) );
    VEC_T(1,C)                          vDet_X0 = FCN_V(tgMH_MUL)( vD0_D0, vD1_D1 );
    VEC_T(1,C)                          vDet_X1 = FCN_V(tgMH_MUL)( vD0_D1, vD0_D1 );
    VEC_T(1,C)                          vDet = FCN_V(tgMH_SUB)( vDet_X0, vDet_X1 );
    VEC_T(1,C)                          vOrgSum = FCN_V(tgMH_ADD)( vS0, vS1 );

    VEC_T(1,C)                          vZero = FCN_V(tgMH_SET1)( TYPE_K(0) );
    VEC_T(1,C)                          vOne = FCN_V(tgMH_SET1)( TYPE_K(1) );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDet, FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)(VAR_K(KTgEPS)), vDet_X0 ) ) ))
    {
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_MUL)( vDS_D0, vD1_D1 );
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_MUL)( vDS_D1, vD0_D1 );
        VEC_T(1,C)                          vX4 = FCN_V(tgMH_ADD)( vX2, vX3 );
        VEC_T(1,C)                          vX5 = FCN_V(tgMH_MUL)( vDS_D0, vD0_D1 );
        VEC_T(1,C)                          vX6 = FCN_V(tgMH_MUL)( vDS_D1, vD0_D0 );
        VEC_T(1,C)                          vX7 = FCN_V(tgMH_ADD)( vX5, vX6 );
        VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( vX4, vDet );
        VEC_T(1,C)                          vT1 = FCN_V(tgMH_DIV)( vX7, vDet );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vT1, vD1 );
        VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vT0, vD0 );
        VEC_T(1,C)                          vK3 = FCN_V(tgMH_ADD)( vOrgSum, vK2 );
        VEC_T(1,C)                          vK4 = FCN_V(tgMH_ADD)( vK3, vK1 );

        if (FCN_V(tgMH_Is_Contained_In_Interval)( vT0, vZero, vOne ) || FCN_V(tgMH_Is_Contained_In_Interval)( vT1, vZero, vOne ))
        {
            TgERROR_CO( u8"Edge-Edge outside of range.\n" );
        };

        *pvRN0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( TYPE_K(0,5) ), vK4 );

        return (1);
    }
    else
    {
        /* Linears are parallel */

        VEC_T(1,C)                          vDE_D0 = FCN_V(tgMH_ADD)( vDS_D0, vD0_D1 ); /* vDE = vS1+pvD1, fDE_D1 = (vS1+pvD1 - vS0)•vD0 */
        VEC_T(1,C)                          vDF_D1 = FCN_V(tgMH_SUB)( vD0_D1, vDS_D1 ); /* vDF = vS0+vD0, fDF_D1 = (vS0+vD0 - vS1)•pvD1 */

        VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vD0_D1, vZero );
        VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GE)( vDS_D1, vZero );
        VEC_T(1,C)                          vCMP_2 = FCN_V(tgMH_CMP_GE)( vD1_D1, vDS_D1 );
        VEC_T(1,C)                          vCMP_3 = FCN_V(tgMH_CMP_GE)( vDF_D1, vZero );
        VEC_T(1,C)                          vCMP_4 = FCN_V(tgMH_CMP_GE)( vD1_D1, vDF_D1 );

        VEC_T(1,C)                          vTA = FCN_V(tgMH_DIV)( vDS_D0, vD0_D0 );
        VEC_T(1,C)                          vTC = FCN_V(tgMH_DIV)( vDE_D0, vD0_D0 );

        /* Point 0 of segment 0 if contained in segment 1, otherwise if segments are mutually directed point 0 of segment 1, else point 1 of segment 1. */
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SEL)( vOne, vZero, vCMP_0 );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_AND)( vCMP_1, vCMP_2 );
        VEC_T(1,C)                          vT0 = FCN_V(tgMH_SEL)( vX0, vZero, vX1 );
        VEC_T(1,C)                          vT1 = FCN_V(tgMH_SEL)( vX0, FCN_V(tgMH_DIV)( vDS_D1, vD1_D1 ), vX1 );

        /* Point 1 of segment 0 if contained in segment 1, otherwise if segments are mutually directed point 1 of segment 1, else point 0 of segment 1. */
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_SEL)( vTA, vTC, vCMP_3 );
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_AND)( vCMP_3, vCMP_4 );
        VEC_T(1,C)                          vT2 = FCN_V(tgMH_SEL)( vX2, vOne, vX3 );
        VEC_T(1,C)                          vT3 = FCN_V(tgMH_SEL)( FCN_V(tgMH_SUB)( vOne, vX0 ), FCN_V(tgMH_DIV)( vDF_D1, vD1_D1 ), vX3 );

        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, vD0 );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vT1, vD1 );
        VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vT2, vD0 );
        VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vT3, vD1 );
        VEC_T(1,C)                          vK4 = FCN_V(tgMH_ADD)( vOrgSum, vK0 );
        VEC_T(1,C)                          vK5 = FCN_V(tgMH_ADD)( vOrgSum, vK2 );
        VEC_T(1,C)                          vK6 = FCN_V(tgMH_ADD)( vK4, vK1 );
        VEC_T(1,C)                          vK7 = FCN_V(tgMH_ADD)( vK5, vK3 );

        VEC_T(1,C)                          vCMP_5 = FCN_V(tgMH_CMP_LT)( vDE_D0, vZero );
        VEC_T(1,C)                          vCMP_6 = FCN_V(tgMH_CMP_GT)( vDS_D0, vOne );
        VEC_T(1,C)                          vCMP_7 = FCN_V(tgMH_OR)( vCMP_5, vCMP_6 );
        VEC_T(1,C)                          vCMP_8 = FCN_V(tgMH_AND)( vCMP_0, vCMP_7 );

        VEC_T(1,C)                          vCMP_A = FCN_V(tgMH_CMP_LT)( vDS_D0, vZero );
        VEC_T(1,C)                          vCMP_B = FCN_V(tgMH_CMP_GT)( vDE_D0, vOne );
        VEC_T(1,C)                          vCMP_C = FCN_V(tgMH_OR)( vCMP_A, vCMP_B );
        VEC_T(1,C)                          vCMP_D = FCN_V(tgMH_CMP_LE)( vD0_D1, vZero );
        VEC_T(1,C)                          vCMP_E = FCN_V(tgMH_AND)( vCMP_D, vCMP_C );

        VEC_T(1,C)                          vCMP_F = FCN_V(tgMH_OR)( vCMP_8, vCMP_E );

        *pvRN0 = FCN_V(tgMH_MUL)(FCN_V(tgMH_SET1)(TYPE_K(0, 5)), vK6);
        *pvRN1 = FCN_V(tgMH_MUL)(FCN_V(tgMH_SET1)(TYPE_K(0, 5)), vK7);

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_F ))
        {
            return (0);
        };

        return (2);
    };
}


/* ---- FCN_V(tgMH_Internal_Parallel) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE FCN_VO(tgCO_LN_Internal_Parallel_LN)( VEC_T(1,PC) pvRN0, VEC_T(1,PC) pvRN1, VEC_T(1,C) vS0, VEC_T(1,C) vD0, VEC_T(1,C) vS1, VEC_T(1,C) vD1 )
{
    VEC_T(1,C)                          vD0_D0 = FCN_V(tgMH_LSQ)( vD0 );
    VEC_T(1,C)                          vD1_D1 = FCN_V(tgMH_LSQ)( vD1 );
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS1, vS0 );

    /*                                  Projection Values */
    VEC_T(1,C)                          vD0_D1 = FCN_V(tgMH_DOT)( vD0, vD1 );
    VEC_T(1,C)                          vDS_D0 = FCN_V(tgMH_DOT)( vDS, vD0 );
    VEC_T(1,C)                          vDS_D1 = FCN_V(tgMH_NEG)( FCN_V(tgMH_DOT)( vDS, vD1 ) );

    VEC_T(1,C)                          vDE_D0 = FCN_V(tgMH_ADD)( vDS_D0, vD0_D1 ); /* vDE = vS1+pvD1, fDE_D1 = (vS1+pvD1 - vS0)•vD0 */
    VEC_T(1,C)                          vDF_D1 = FCN_V(tgMH_SUB)( vD0_D1, vDS_D1 ); /* vDF = vS0+vD0, fDF_D1 = (vS0+vD0 - vS1)•pvD1 */

    VEC_T(1,C)                          vTA = FCN_V(tgMH_DIV)( vDS_D0, vD0_D0 );
    VEC_T(1,C)                          vTC = FCN_V(tgMH_DIV)( vDE_D0, vD0_D0 );
    VEC_T(1,C)                          vZero = FCN_V(tgMH_SET1)( TYPE_K(0) );
    VEC_T(1,C)                          vOne = FCN_V(tgMH_SET1)( TYPE_K(1) );

    VEC_T(1,C)                          vCMP_0 = FCN_V(tgMH_CMP_GE)( vD0_D1, vZero );
    VEC_T(1,C)                          vCMP_1 = FCN_V(tgMH_CMP_GE)( vDS_D1, vZero );
    VEC_T(1,C)                          vCMP_2 = FCN_V(tgMH_CMP_GE)( vD1_D1, vDS_D1 );
    VEC_T(1,C)                          vCMP_3 = FCN_V(tgMH_CMP_GE)( vDF_D1, vZero );
    VEC_T(1,C)                          vCMP_4 = FCN_V(tgMH_CMP_GE)( vD1_D1, vDF_D1 );

    /* Point 0 of segment 0 if contained in segment 1, otherwise if segments are mutually directed point 0 of segment 1, else point 1 of segment 1. */
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SEL)( vTC, vTA, vCMP_0 );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SEL)( vZero, vOne, vCMP_0 );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_AND)( vCMP_1, vCMP_2 );
    VEC_T(1,C)                          vT0 = FCN_V(tgMH_SEL)( vX0, vZero, vX2 );
    VEC_T(1,C)                          vT1 = FCN_V(tgMH_SEL)( vX1, FCN_V(tgMH_DIV)( vDS_D1, vD1_D1 ), vX2 );

    /* Point 1 of segment 0 if contained in segment 1, otherwise if segments are mutually directed point 1 of segment 1, else point 0 of segment 1. */
    VEC_T(1,C)                          vX3 = FCN_V(tgMH_SEL)( vTA, vTC, vCMP_0 );
    VEC_T(1,C)                          vX4 = FCN_V(tgMH_SEL)( vZero, vOne, vCMP_0 );
    VEC_T(1,C)                          vX5 = FCN_V(tgMH_AND)( vCMP_3, vCMP_4 );
    VEC_T(1,C)                          vT2 = FCN_V(tgMH_SEL)( vX3, vOne, vX5 );
    VEC_T(1,C)                          vT3 = FCN_V(tgMH_SEL)( vX4, FCN_V(tgMH_DIV)( vDF_D1, vD1_D1 ), vX5 );

    VEC_T(1,C)                          vOrgSum = FCN_V(tgMH_ADD)( vS0, vS1 );
    VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT0, vD0 );
    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vT1, vD1 );
    VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vT2, vD0 );
    VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vT3, vD1 );
    VEC_T(1,C)                          vK4 = FCN_V(tgMH_ADD)( vOrgSum, vK0 );
    VEC_T(1,C)                          vK5 = FCN_V(tgMH_ADD)( vOrgSum, vK2 );
    VEC_T(1,C)                          vK6 = FCN_V(tgMH_ADD)( vK4, vK1 );
    VEC_T(1,C)                          vK7 = FCN_V(tgMH_ADD)( vK5, vK3 );

    VEC_T(1,C)                          vCMP_5 = FCN_V(tgMH_CMP_LT)( vDE_D0, vZero );
    VEC_T(1,C)                          vCMP_6 = FCN_V(tgMH_CMP_GT)( vDS_D0, vOne );
    VEC_T(1,C)                          vCMP_7 = FCN_V(tgMH_OR)( vCMP_5, vCMP_6 );
    VEC_T(1,C)                          vCMP_8 = FCN_V(tgMH_AND)( vCMP_0, vCMP_7 );

    VEC_T(1,C)                          vCMP_A = FCN_V(tgMH_CMP_LT)( vDS_D0, vZero );
    VEC_T(1,C)                          vCMP_B = FCN_V(tgMH_CMP_GT)( vDE_D0, vOne );
    VEC_T(1,C)                          vCMP_C = FCN_V(tgMH_OR)( vCMP_A, vCMP_B );
    VEC_T(1,C)                          vCMP_D = FCN_V(tgMH_CMP_LE)( vD0_D1, vZero );
    VEC_T(1,C)                          vCMP_E = FCN_V(tgMH_AND)( vCMP_D, vCMP_C );

    VEC_T(1,C)                          vCMP_F = FCN_V(tgMH_OR)( vCMP_8, vCMP_E );

    *pvRN0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( TYPE_K(0,5) ), vK6 );
    *pvRN1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( TYPE_K(0,5) ), vK7 );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_F ))
    {
        return (0);
    };

    return (2);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
