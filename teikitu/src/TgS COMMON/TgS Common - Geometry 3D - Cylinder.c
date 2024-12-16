/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Cylinder.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined (TGS_COMMON_GEOMETRY_H)

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

/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_CY_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgGM_CY_Support_Point)( VEC_OBJ_T(TgTUBE,CPCU) psCY0, VEC_T(1,C) vDN )
{
    VEC_T(1,C)                          vN0 = FCN_V(tgMH_Query_Axis_1,3)( &psCY0->m_mReference_Frame );
    VEC_UN_T(1,C)                       uDN_N0 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( vDN, vN0 ) };
    VEC_T(1,C)                          vC0 = FCN_V(tgMH_Query_Axis_3,3)( &psCY0->m_mReference_Frame );
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( VEC_UN_1_MEMBER(uDN_N0), vN0 );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vDN, vX0 );
    VEC_UN_T(1,C)                       uU0 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_LEN)( vX1 ) };
    VEC_T(1)                            vResult;

    TgERROR(FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    if (VEC_S_UN_1_MEMBER(uDN_N0).x > VAR_K(KTgEPS))
    {
        vResult = FCN_V(tgMH_ADD)( vC0, psCY0->m_vHAX );
    }
    else if (VEC_S_UN_1_MEMBER(uDN_N0).x < -VAR_K(KTgEPS))
    {
        vResult = FCN_V(tgMH_SUB)( vC0, psCY0->m_vHAX );
    }
    else
    {
        vResult = vC0;
    }

    if (VEC_S_UN_1_MEMBER(uU0).x > VAR_K(KTgEPS))
    {
        VEC_T(1,C)                          vRadial = FCN_V(tgMH_NORM)( vX1 );

        vResult = FCN_V(tgMH_MAD)( psCY0->m_vRadius, vRadial, vResult );
    };

    return (vResult);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/*# defined (TGS_COMMON_GEOMETRY_H) */
#endif
