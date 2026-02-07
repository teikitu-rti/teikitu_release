/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Axis Projection.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD)
    #define TEMPLATE__VECTOR_DIM 4

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define ENABLE_RELOAD_GUARD
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
        #undef TEMPLATE__TYPE_SIZE
        #undef ENABLE_RELOAD_GUARD
    #endif

    #define TEMPLATE__TYPE_SIZE 32
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_Test_Seperating_Axis) ---------------------------------------------------------------------------------------------------------------------------------------- */
/*  Contact occurs between the two primitives when they overlap along all possible axis of separation.  Thus, contact will occur at the maximum contact start time untilililililil */
/* the minimal contact end time.                                                                                                                                                   */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSINT_E32 FCN_VO(tgCO_Test_Seperating_Axis)(VEC_OBJ_T(STg2_CO_Axis_Test,PC) psAxTest )
{
    TgSINT_E32                          iRet = 0;

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( psAxTest->m_vMax1, psAxTest->m_vMin0 ) ))
    {
        /* Primitive 1's projection is in the negative direction of the projection of primitive 0. */

        /* Primitive 1 is moving away from primitive 0, no possible contact. */
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( psAxTest->m_vSpeed, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (-1);
        }
        else
        {
            /* Compute first, and last time of contact - current maximum and minimum */
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( psAxTest->m_vMin0, psAxTest->m_vMax1 );
            VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( vK0, psAxTest->m_vSpeed );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( psAxTest->m_vMax0, psAxTest->m_vMin1 );
            VEC_T(1,C)                          vT1 = FCN_V(tgMH_DIV)( vK1, psAxTest->m_vSpeed );
            VEC_T(1,C)                          vMinT = FCN_V(tgMH_MAX)( psAxTest->m_vMinT, vT0 );
            VEC_T(1,C)                          vMaxT = FCN_V(tgMH_MIN)( psAxTest->m_vMaxT, vT1 );

            /* No contact occurs if t-value exceeds the imposed limit or the current min and max pass each other. */
            TgBOOL_C                            bTST_0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vMinT, psAxTest->m_vLimitT ) );
            TgBOOL_C                            bTST_1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vMinT, vMaxT ) );

            if (bTST_0 || bTST_1)
            {
                return (-1);
            };

            psAxTest->m_vMinT = vMinT;
            psAxTest->m_vMaxT = vMaxT;
            iRet = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LE)(vT0, psAxTest->m_vMinT)) ? iRet : 1;

            return (iRet);
        };
    };

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( psAxTest->m_vMax0, psAxTest->m_vMin1 ) ))
    {
        /* Primitive 1's projection is in the positive direction of the projection of primitive 0. */

        /* Primitive 1 is moving away from primitive 0, no possible contact. */
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( psAxTest->m_vSpeed, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (-1);
        }
        else
        {
            /* Compute first, and last time of contact - current maximum and minimum */
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( psAxTest->m_vMax0, psAxTest->m_vMin1 );
            VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( vK0, psAxTest->m_vSpeed );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( psAxTest->m_vMin0, psAxTest->m_vMax1 );
            VEC_T(1,C)                          vT1 = FCN_V(tgMH_DIV)( vK1, psAxTest->m_vSpeed );
            VEC_T(1,C)                          vMinT = FCN_V(tgMH_MAX)( psAxTest->m_vMinT, vT0 );
            VEC_T(1,C)                          vMaxT = FCN_V(tgMH_MIN)( psAxTest->m_vMaxT, vT1 );

            /* No contact occurs on this axis if it now exceeds the limit imposed on the t-value. */
            TgBOOL_C                            bTST_0 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vMinT, psAxTest->m_vLimitT ) );
            TgBOOL_C                            bTST_1 = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vMinT, vMaxT ) );

            if (bTST_0 || bTST_1)
            {
                return (-1);
            };

            psAxTest->m_vMinT = vMinT;
            psAxTest->m_vMaxT = vMaxT;
            iRet = FCN_V(tgMH_CMP_ALL_TO_BOOL)(FCN_V(tgMH_CMP_LE)(vT0, psAxTest->m_vMinT)) ? iRet : 1;

            return (iRet);
        };
    };

    if (!FCN_V(tgMH_Is_NR0)(psAxTest->m_vSpeed)) /* V and U on overlapping interval */
    {
        VEC_T(1,C)      vK0 = FCN_V(tgMH_SUB)( psAxTest->m_vMax0, psAxTest->m_vMin1 );
        VEC_T(1,C)      vK1 = FCN_V(tgMH_SUB)( psAxTest->m_vMin0, psAxTest->m_vMax1 );
        VEC_T(1,C)      vK2 = FCN_V(tgMH_CMP_GT)( psAxTest->m_vSpeed, FCN_V(tgMH_SET1)( TYPE_K(0) ) );
        VEC_T(1,C)      vK3 = FCN_V(tgMH_SEL)( vK1, vK0, vK2 );
        VEC_T(1,C)      vT1 = FCN_V(tgMH_DIV)( vK3, psAxTest->m_vSpeed ); /* Compute first time of contact. */
        VEC_T(1,C)      vMaxT = FCN_V(tgMH_MIN)( psAxTest->m_vMaxT, vT1 );

        psAxTest->m_vMaxT = vMaxT;

        /* No contact occurs on this axis if the current if the min and max pass each other. */
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( psAxTest->m_vMinT, vMaxT ) ))
        {
            return (-1);
        };
    };

    return (iRet);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
