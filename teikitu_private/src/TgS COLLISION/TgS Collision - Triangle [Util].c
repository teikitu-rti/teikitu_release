/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Triangle [Util].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
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

/* ---- FCN_VO(tgCO_PT_Is_Seperating_Axis_PT) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgCO_PT_Is_Seperating_Axis_PT)( VEC_T(1,C) vAxis, VEC_OBJ_T(TgPTRI,CPC) psPT0, VEC_OBJ_T(TgPTRI,CPC) psPT1 )
{
    VEC_T(1,C)      vAX_PT00 = FCN_V(tgMH_DOT)( vAxis, psPT0->m_avPoint[0] );
    VEC_T(1,C)      vAX_PT01 = FCN_V(tgMH_DOT)( vAxis, psPT0->m_avPoint[1] );
    VEC_T(1,C)      vAX_PT02 = FCN_V(tgMH_DOT)( vAxis, psPT0->m_avPoint[2] );

    VEC_T(1,C)      vAX_PT10 = FCN_V(tgMH_DOT)( vAxis, psPT1->m_avPoint[0] );
    VEC_T(1,C)      vAX_PT11 = FCN_V(tgMH_DOT)( vAxis, psPT1->m_avPoint[1] );
    VEC_T(1,C)      vAX_PT12 = FCN_V(tgMH_DOT)( vAxis, psPT1->m_avPoint[2] );

    VEC_T(1,C)      vMin0 = FCN_V(tgMH_MIN)( vAX_PT00, FCN_V(tgMH_MIN)( vAX_PT01, vAX_PT02 ) );
    VEC_T(1,C)      vMax0 = FCN_V(tgMH_MAX)( vAX_PT00, FCN_V(tgMH_MAX)( vAX_PT01, vAX_PT02 ) );
    VEC_T(1,C)      vMin1 = FCN_V(tgMH_MIN)( vAX_PT10, FCN_V(tgMH_MIN)( vAX_PT11, vAX_PT12 ) );
    VEC_T(1,C)      vMax1 = FCN_V(tgMH_MAX)( vAX_PT10, FCN_V(tgMH_MAX)( vAX_PT11, vAX_PT12 ) );

    return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vMin0, vMax1 ) ) || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vMin1, vMax0 ) ));
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
