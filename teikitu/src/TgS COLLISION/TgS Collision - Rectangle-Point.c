/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Rectangle-Point.c
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

/* ---- FCN_VO(tgCO_RT_ClosestSq_PM_PT) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_RT_ClosestSq_PM_PT)( VEC_T(1,PC) pvRT0, VEC_T(1,PC) pvRT1, VEC_OBJ_T(TgRECTANGLE,CPC) psRT0, VEC_T(1,C) vS0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, psRT0->m_vOrigin );
    VEC_T(1,C)                          vDS_DS = FCN_V(tgMH_LSQ)( vDS );
    VEC_T(1,C)                          vZero = FCN_V(tgMH_SET1)( TYPE_K(0) );

    TgERROR( FCN_VO(tgGM_RT_Is_Valid)(psRT0) && FCN_V(tgMH_Is_Valid_Point)(vS0) );

    if (FCN_V(tgMH_Is_NR0)( vDS_DS ))
    {
        /* Quick Out - the point is within tolerance of rectangle origin. */
        *pvRT0 = vZero;
        *pvRT1 = vZero;
        return (vZero);
    }
    else
    {
        VEC_T(1,C)                          vE0_E0 = FCN_V(tgMH_LSQ)( psRT0->m_avEdge[0] );
        VEC_T(1,C)                          vE1_E1 = FCN_V(tgMH_LSQ)( psRT0->m_avEdge[1] );

        if (FCN_V(tgMH_Is_NR0)( vE0_E0 ) || FCN_V(tgMH_Is_NR0)( vE1_E1 ))
        {
            /* Degenerate rectangle - One or both of the edges has a near-zero length */
            return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
        }
        else
        {
            VEC_T(1,C)                          vDS_E0 = FCN_V(tgMH_DOT)( vDS, psRT0->m_avEdge[0] );
            VEC_T(1,C)                          vDS_E1 = FCN_V(tgMH_DOT)( vDS, psRT0->m_avEdge[1] );
            VEC_T(1,C)                          vRT0 = FCN_V(tgMH_LRP)( vZero, FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_DIV)( vDS_E0, vE0_E0 ) );
            VEC_T(1,C)                          vRT1 = FCN_V(tgMH_LRP)( vZero, FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_DIV)( vDS_E1, vE1_E1 ) );

            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vRT0, psRT0->m_avEdge[0] );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vRT1, psRT0->m_avEdge[1] );
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)( vS0, psRT0->m_vOrigin );
            VEC_T(1,C)                          vK3 = FCN_V(tgMH_SUB)( vK2, vK0 );
            VEC_T(1,C)                          vK4 = FCN_V(tgMH_SUB)( vK3, vK1 );

            *pvRT0 = vRT0;
            *pvRT1 = vRT1;

            return (FCN_V(tgMH_LSQ)( vK4 ));
        };
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
