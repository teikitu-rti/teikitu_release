/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Rectangle-Triangle.c
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

/* ---- FCN_VO(tgCO_RT_ClosestSq_PM_ST) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  psRT0: Rectangle primitive                                                                                                                                              */
/* Input:  psST0: Space Triangle primitive                                                                                                                                         */
/* Output: _fRT0, _fRT1: Parametric parameters to generate point of minimal distance on the rectangle                                                                              */
/* Output: _fST0, _fST1: Parametric parameters to generate point of minimal distance on the triangle                                                                               */
/* Return: Minimal distance between the two primitives or negative type max if they intersect or are invalid.                                                                      */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_RT_ClosestSq_PM_ST)( VEC_T(1,P) pvRT0, VEC_T(1,P) pvRT1, VEC_T(1,P) pvST0, VEC_T(1,P) pvST1, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_OBJ_T(TgSTRI,CPC) psST0 )
{
    VEC_T(1)                            vDistSq, vRT0, vRT1, vET0, vET1, vTest, vT0, vT1, vG1;

    /* == Test Rectangle 0 Edges against Triangle 1 == */

    vDistSq = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vET0, &vET1, &vRT0, psST0, psRT0->m_vOrigin, psRT0->m_avEdge[0] );
    vRT1 = FCN_V(tgMH_SET1)( TYPE_K(0) );

    vT0 = FCN_VO(tgGM_RT_Query_Point_2)(psRT0);
    vTest = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psST0, vT0, psRT0->m_avEdge[0] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDistSq ) ))
    {
        vDistSq = vTest;
        vRT0 = vG1;
        vRT1 = FCN_V(tgMH_SET1)( TYPE_K(1) );
        vET0 = vT0;
        vET1 = vT1;
    };

    vTest = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psST0, psRT0->m_vOrigin, psRT0->m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDistSq ) ))
    {
        vDistSq = vTest;
        vRT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        vRT1 = vG1;
        vET0 = vT0;
        vET1 = vT1;
    };

    vT0 = FCN_VO(tgGM_RT_Query_Point_1)(psRT0);
    vTest = FCN_VO(tgCO_ST_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psST0, vT0, psRT0->m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDistSq ) ))
    {
        vDistSq = vTest;
        vRT0 = FCN_V(tgMH_SET1)( TYPE_K(1) );
        vRT1 = vG1;
        vET0 = vT0;
        vET1 = vT1;
    };

    /* == Test Triangle 1 Edges against Rectangle 0 == */

    vTest = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psRT0, psST0->m_sCT.m_sET.m_sPT.m_avPoint[0], psST0->m_sCT.m_sET.m_avEdge[0] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDistSq ) ))
    {
        vDistSq = vTest;
        vRT0 = vT0;
        vRT1 = vT1;
        vET0 = vG1;
        vET1 = FCN_V(tgMH_SET1)( TYPE_K(0) );
    };

    vTest = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psRT0, psST0->m_sCT.m_sET.m_sPT.m_avPoint[1], psST0->m_sCT.m_sET.m_avEdge[1] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDistSq ) ))
    {
        vDistSq = vTest;
        vRT0 = vT0;
        vRT1 = vT1;
        vET0 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), vG1 );
        vET1 = vG1;
    };

    vTest = FCN_VO(tgCO_RT_ClosestSq_PM_LR11)( &vT0, &vT1, &vG1, psRT0, psST0->m_sCT.m_sET.m_sPT.m_avPoint[2], psST0->m_sCT.m_sET.m_avEdge[2] );
    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vDistSq ) ))
    {
        vDistSq = vTest;
        vRT0 = vT0;
        vRT1 = vT1;
        vET0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        vET1 = FCN_V(tgMH_SUB)( FCN_V(tgMH_SET1)( TYPE_K(1) ), vG1 );
    };

    /* == Return Values == */

    *pvRT0 = vRT0;
    *pvRT1 = vRT1;
    *pvST0 = vET0;
    *pvST1 = vET1;

    return (vDistSq);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
