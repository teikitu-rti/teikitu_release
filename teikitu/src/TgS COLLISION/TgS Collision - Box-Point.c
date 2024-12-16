/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box-Point.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
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

/* ---- FCN_VO(tgCO_BX_ClosestSq_PM_PT) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  psBX0: Box primitive                                                                                                                                                    */
/* Input:  vS0: Point                                                                                                                                                              */
/* Output: tyB0,tyB1,tyB2: Parametric parameters to generate the point of closest proximity on the box (one for each axis)                                                         */
/* Return: Minimal distance between the two primitives or negative type max if they intersect or are invalid.                                                                      */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_BX_ClosestSq_PM_PT)( VEC_T(1,PC) pvB0, VEC_T(1,PC) pvB1, VEC_T(1,PC) pvB2, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vBX0_UX[3], vBX0_OG, vDS, vT0, vT0_CLP, vT1, vT1_CLP, vT2, vT2_CLP, vDist, vDistSq;

    TgPARAM_CHECK(FCN_VO(tgGM_BX_Is_Valid)( psBX0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    FCN_V(tgMH_Query_Reference_Frame,3)( vBX0_UX + 0, vBX0_UX + 1, vBX0_UX + 2, &vBX0_OG, &psBX0->m_mReference_Frame );

    vDS = FCN_V(tgMH_SUB)( vS0, vBX0_OG );

    vT0 = FCN_V(tgMH_DOT)( vDS, vBX0_UX[0] );
    vT0_CLP = FCN_V(tgMH_CLP)( vT0, FCN_V(tgMH_NEG)( FCN_V(tgMH_SPX)( psBX0->m_vExtent ) ), FCN_V(tgMH_SPX)( psBX0->m_vExtent ) );
    vT1 = FCN_V(tgMH_DOT)( vDS, vBX0_UX[1] );
    vT1_CLP = FCN_V(tgMH_CLP)( vT1, FCN_V(tgMH_NEG)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ) ), FCN_V(tgMH_SPY)( psBX0->m_vExtent ) );
    vT2 = FCN_V(tgMH_DOT)( vDS, vBX0_UX[2] );
    vT2_CLP = FCN_V(tgMH_CLP)( vT2, FCN_V(tgMH_NEG)( FCN_V(tgMH_SPZ)( psBX0->m_vExtent ) ), FCN_V(tgMH_SPZ)( psBX0->m_vExtent ) );

    *pvB0 = vT0_CLP;
    vDist = FCN_V(tgMH_SUB)( vT0, vT0_CLP );
    vDistSq = FCN_V(tgMH_MUL)( vDist, vDist );

    *pvB1 = vT1_CLP;
    vDist = FCN_V(tgMH_SUB)( vT1, vT1_CLP );
    vDistSq = FCN_V(tgMH_MAD)( vDist, vDist, vDistSq );

    *pvB2 = vT2_CLP;
    vDist = FCN_V(tgMH_SUB)( vT2, vT2_CLP );
    vDistSq = FCN_V(tgMH_MAD)( vDist, vDist, vDistSq );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vDistSq, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ) ? FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ) : vDistSq);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
