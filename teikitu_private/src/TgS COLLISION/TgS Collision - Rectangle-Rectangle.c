/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Rectangle-Rectangle.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

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

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_RT_ClosestSq_PM_RT) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_RT_ClosestSq_PM_RT)( VEC_T(1,PC) pvRT00, VEC_T(1,PC) pvRT01, VEC_T(1,PC) pvRT10, VEC_T(1,PC) pvRT11, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0,
                                          VEC_OBJ_T(TgRECTANGLE,CPC) psRT1 )
{
    VEC_T(1)                            vRT00, vRT01, vRT10, vRT11, vDistSq, vTestSq;
    VEC_T(1)                            vT0, vT1, vG1;
    VEC_T(1,C)                          vZero = FCN_V(tgMH_SET1)( TYPE_K(0) );
    VEC_T(1,C)                          vOne = FCN_V(tgMH_SET1)( TYPE_K(1) );

    vRT00 = vRT01 = vRT10 = vRT11 = vZero;

    /* == Test Rectangle 0 Edges against Rectangle 1 == */

    vDistSq = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vRT10, &vRT11, &vRT00, psRT1, psRT0->m_vOrigin, psRT0->m_avEdge[0] );

    vT0 = FCN_VO(tgGM_RT_Query_Point_2)(psRT0);
    vTestSq = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psRT1, vT0, psRT0->m_avEdge[0] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vRT00 = vG1;
        vRT01 = vOne;
        vRT10 = vT0;
        vRT11 = vT1;
    };

    vTestSq = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psRT1, psRT0->m_vOrigin, psRT0->m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vRT00 = vZero;
        vRT01 = vG1;
        vRT10 = vT0;
        vRT11 = vT1;
    };

    vT0 = FCN_VO(tgGM_RT_Query_Point_1)(psRT0);
    vTestSq = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psRT1, vT0, psRT0->m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vRT00 = vOne;
        vRT01 = vG1;
        vRT10 = vT0;
        vRT11 = vT1;
    };

    /* == Test Rectangle 1 Edges against Rectangle 0 =========== */

    vTestSq = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psRT0, psRT1->m_vOrigin, psRT1->m_avEdge[0] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vRT00 = vT0;
        vRT01 = vT1;
        vRT10 = vG1;
        vRT11 = vZero;
    };

    vT0 = FCN_VO(tgGM_RT_Query_Point_2)(psRT1);
    vTestSq = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psRT0, vT0, psRT1->m_avEdge[0] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vRT00 = vT0;
        vRT01 = vT1;
        vRT10 = vG1;
        vRT11 = vOne;
    };

    vTestSq = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psRT0, psRT1->m_vOrigin, psRT1->m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vRT00 = vT0;
        vRT01 = vT1;
        vRT10 = vZero;
        vRT11 = vG1;
    };

    vT0 = FCN_VO(tgGM_RT_Query_Point_1)(psRT1);
    vTestSq = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psRT0, vT0, psRT1->m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTestSq, vDistSq ) ))
    {
        vDistSq = vTestSq;
        vRT00 = vT0;
        vRT01 = vT1;
        vRT10 = vOne;
        vRT11 = vG1;
    };

    /* == Return Values == */

    *pvRT00 = vRT00;
    *pvRT01 = vRT01;
    *pvRT10 = vRT10;
    *pvRT11 = vRT11;

    return (vDistSq);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
