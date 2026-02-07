/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Ellipse.c
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

/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_EL_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgGM_EL_Is_Valid)( VEC_OBJ_T(TgELLIPSE,CPCU) psEL0 )
{
    if (!FCN_V(tgMH_Is_Valid_Reference_Frame,3)( &psEL0->m_mReference_Frame ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( psEL0->m_vMajor ) || !FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( psEL0->m_vMinor ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_EL_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgGM_EL_Support_Point)( VEC_OBJ_T(TgELLIPSE,CPCU) psEL0, VEC_T(1,C) vDN )
{
    VEC_T(1)                            vA0, vA1, vA2, vC0;
    VEC_T(1)                            vResult;

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_EL_Is_Valid)( psEL0 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psEL0->m_mReference_Frame );

    {
        VEC_UN_T(1,C)                       uDN_A0 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( vDN, vA0 ) };
        VEC_UN_T(1,C)                       uDN_A2 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( vDN, vA2 ) };

        if (FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uDN_A0).x ) && FCN_F(tgCM_NR0)( VEC_S_UN_1_MEMBER(uDN_A2).x ))
        {
            vResult = vC0;
        }
        else
        {
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( psEL0->m_vMajor, psEL0->m_vMajor );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( psEL0->m_vMinor, psEL0->m_vMinor );

            VEC_T(1,C)                          vInvMajorSq = FCN_V(tgMH_DIV)( VEC_UN_1_MEMBER(uDN_A0), vK0 );
            VEC_T(1,C)                          vInvMinorSq = FCN_V(tgMH_DIV)( VEC_UN_1_MEMBER(uDN_A2), vK1 );
            VEC_T(1,C)                          vRHS = FCN_V(tgMH_RCP)( FCN_V(tgMH_ADD)( vInvMajorSq, vInvMinorSq ) );
            VEC_T(1,C)                          vPoint = FCN_V(tgMH_SQRT)( FCN_V(tgMH_ABS)( vRHS ) );

            VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( vPoint, psEL0->m_vMajor );
            VEC_T(1,C)                          vX1 = FCN_V(tgMH_CP_SGN)( vX0, VEC_UN_1_MEMBER(uDN_A0) );
            VEC_T(1,C)                          vX2 = FCN_V(tgMH_MUL)( vX1, vA0 );

            VEC_T(1,C)                          vX3 = FCN_V(tgMH_MUL)( vPoint, psEL0->m_vMinor );
            VEC_T(1,C)                          vX4 = FCN_V(tgMH_CP_SGN)( vX3, VEC_UN_1_MEMBER(uDN_A2) );
            VEC_T(1,C)                          vX5 = FCN_V(tgMH_MUL)( vX4, vA2 );

            VEC_T(1,C)                          vX6 = FCN_V(tgMH_ADD)( vX2, vX5 );

            vResult = FCN_V(tgMH_ADD)( vC0, vX6 );
        };
    }

    return (vResult);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
